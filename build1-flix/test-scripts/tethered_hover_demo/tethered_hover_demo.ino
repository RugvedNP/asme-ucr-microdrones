// ASME @ UCR Microdrones — Build 1 (flix platform) — Tethered Hover Demo
//
// !! PROPS ON. DRONE MUST BE TETHERED OR HAND-RESTRAINED. !!
//
// This is NOT the flix flight controller — there is no attitude PID loop
// here. It's a simple open-loop throttle ramp with safety guards, meant to
// confirm the hardware produces thrust and the safety systems work before
// ever flashing/flying the real flix firmware.
//
// Setup: same as smoke_test.ino (ESP32 core 3.3.10, board "WEMOS D1 MINI
// ESP32", FlixPeriph library, Serial Monitor at 115200 baud).
//
// Flow:
//   1. IMU + battery health check on boot. Halts if either fails.
//   2. Waits for "ARM" typed into Serial Monitor.
//   3. Ramps all 4 motors 0% -> 35% over 2s, holds 4s, ramps back down 2s.
//   4. Type "STOP" at any time to cut motors immediately.
//   5. If tilt exceeds 45 degrees on any axis, motors are cut immediately.

#include <SPI.h>
#include <FlixPeriph.h>

// ---- Hardware config (same wiring as smoke_test.ino) ----
const int IMU_SCK_PIN = 18, IMU_MISO_PIN = 19, IMU_MOSI_PIN = 23, IMU_CS_PIN = 5;
const int IMU_MODEL = 1; // 1 = MPU9250 (GY-91)

const int MOTOR_PINS[4] = {12, 13, 14, 15};
const int PWM_FREQUENCY = 78000;
const int PWM_RESOLUTION = 10;

const int BATTERY_PIN = 32;
const float BATTERY_DIVIDER_SCALE = 2.0;
const float BATTERY_MIN_VOLTS = 3.4;

const float ONE_G = 9.80665;
const float TILT_LIMIT_DEG = 45.0;
const float HOVER_THROTTLE = 0.35;
const unsigned long RAMP_UP_MS = 2000;
const unsigned long HOLD_MS = 4000;
const unsigned long RAMP_DOWN_MS = 2000;
const unsigned long STEP_MS = 10; // 100Hz control/safety loop

IMU *imu = nullptr;

float peakTiltDeg = 0;
double voltageSum = 0;
unsigned long voltageSamples = 0;
bool tiltCut = false;
bool userStopped = false;

int dutyForFraction(float fraction) {
	fraction = constrain(fraction, 0.0, 1.0);
	return round(fraction * ((1 << PWM_RESOLUTION) - 1));
}

void setAllMotors(float fraction) {
	int duty = dutyForFraction(fraction);
	for (int i = 0; i < 4; i++) ledcWrite(MOTOR_PINS[i], duty);
}

void setup() {
	Serial.begin(115200);
	delay(500);
	Serial.println("\n=== ASME Microdrones — Tethered Hover Demo ===");

	if (!checkIMU()) {
		Serial.println("IMU FAILED — DO NOT FLY");
		while (true) delay(1000);
	}

	float voltage = readBatteryVoltage();
	Serial.printf("Battery: %.2f V\n", voltage);
	if (voltage < BATTERY_MIN_VOLTS) {
		Serial.println("BATTERY TOO LOW — DO NOT FLY");
		while (true) delay(1000);
	}

	for (int i = 0; i < 4; i++) ledcAttach(MOTOR_PINS[i], PWM_FREQUENCY, PWM_RESOLUTION);

	Serial.println("Type ARM to begin hover test. ENSURE TETHER IS ATTACHED.");
	waitForArm();

	runHoverSequence();

	Serial.println("\n=== Report ===");
	Serial.printf("Peak tilt observed: %.1f deg\n", peakTiltDeg);
	if (voltageSamples > 0) {
		Serial.printf("Average battery voltage during test: %.2f V\n", voltageSum / voltageSamples);
	}
}

void loop() {
	// Nothing to do — sequence runs once on boot.
}

bool checkIMU() {
	SPI.begin(IMU_SCK_PIN, IMU_MISO_PIN, IMU_MOSI_PIN);
	imu = IMU::create(IMU_MODEL, SPI, IMU_CS_PIN, -1);
	imu->begin();
	if (imu->status() != 0) return false;

	imu->setAccelRange(IMU::ACCEL_RANGE_4G);
	imu->setGyroRange(IMU::GYRO_RANGE_2000DPS);
	imu->setDLPF(IMU::DLPF_MAX);
	imu->setRate(IMU::RATE_1KHZ_APPROX);

	imu->waitForData();
	float gx, gy, gz, ax, ay, az;
	imu->getGyro(gx, gy, gz);
	imu->getAccel(ax, ay, az);
	bool allZero = (gx == 0 && gy == 0 && gz == 0 && ax == 0 && ay == 0 && az == 0);
	return !allZero;
}

float readBatteryVoltage() {
	return analogReadMilliVolts(BATTERY_PIN) * BATTERY_DIVIDER_SCALE / 1000.0;
}

void waitForArm() {
	while (true) {
		if (Serial.available()) {
			String line = Serial.readStringUntil('\n');
			line.trim();
			if (line.equalsIgnoreCase("ARM")) return;
			if (line.equalsIgnoreCase("STOP")) {
				Serial.println("Stopped before arming.");
				while (true) delay(1000);
			}
		}
		delay(20);
	}
}

// Reads IMU, updates peak tilt, returns true if a safety cut is needed.
bool updateSafety() {
	imu->waitForData();
	float gx, gy, gz, ax, ay, az;
	imu->getGyro(gx, gy, gz);
	imu->getAccel(ax, ay, az);

	// Tilt from vertical, estimated from raw accelerometer only (no fusion —
	// this is a bench safety guard, not the real attitude estimator).
	float accelMag = sqrt(ax * ax + ay * ay + az * az);
	float tiltDeg = 0;
	if (accelMag > 0.1) {
		float cosTilt = constrain(az / accelMag, -1.0, 1.0);
		tiltDeg = acos(cosTilt) * RAD_TO_DEG;
	}
	if (tiltDeg > peakTiltDeg) peakTiltDeg = tiltDeg;

	voltageSum += readBatteryVoltage();
	voltageSamples++;

	if (Serial.available()) {
		String line = Serial.readStringUntil('\n');
		line.trim();
		if (line.equalsIgnoreCase("STOP")) {
			userStopped = true;
			return true;
		}
	}

	if (tiltDeg > TILT_LIMIT_DEG) {
		tiltCut = true;
		return true;
	}

	return false;
}

// Runs one phase of the sequence, updating throttle linearly from `from` to
// `to` over `durationMs`, checking safety at ~100Hz. Returns false if the
// sequence was aborted (tilt cut or STOP).
bool runPhase(float from, float to, unsigned long durationMs) {
	unsigned long start = millis();
	while (true) {
		unsigned long elapsed = millis() - start;
		if (elapsed >= durationMs) {
			setAllMotors(to);
			break;
		}
		float fraction = (float)elapsed / durationMs;
		setAllMotors(from + (to - from) * fraction);

		if (updateSafety()) {
			setAllMotors(0);
			if (tiltCut) Serial.println("TILT SAFETY CUT — motors killed.");
			if (userStopped) Serial.println("STOP received — motors killed.");
			return false;
		}
		delay(STEP_MS);
	}
	return true;
}

void runHoverSequence() {
	Serial.println("Arming. Ramping up...");
	if (!runPhase(0.0, HOVER_THROTTLE, RAMP_UP_MS)) return;

	Serial.println("Holding hover throttle...");
	if (!runPhase(HOVER_THROTTLE, HOVER_THROTTLE, HOLD_MS)) return;

	Serial.println("Ramping down...");
	if (!runPhase(HOVER_THROTTLE, 0.0, RAMP_DOWN_MS)) return;

	Serial.println("Test complete. Motors disarmed.");
}
