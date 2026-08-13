// ASME @ UCR Microdrones — Build 1 (flix platform) — Hardware Smoke Test
//
// !! REMOVE PROPELLERS BEFORE RUNNING THIS SKETCH !!
//
// Bench test run once after soldering, before the drone ever flies. It checks
// the IMU, spins each motor briefly so you can visually confirm position/
// direction, reads the battery, and verifies the failsafe cuts power fast.
//
// Setup (matches the main flix firmware, see github.com/okalachev/flix):
//   - Arduino IDE, ESP32 core 3.3.10 (Boards Manager)
//   - Board: "WEMOS D1 MINI ESP32"
//   - Library: FlixPeriph (Library Manager) — provides the IMU driver
//   - Serial Monitor at 115200 baud
//
// Wiring assumed (Build 1 default, see project CLAUDE.md):
//   IMU (GY-91/MPU-9250) on VSPI: SCK=18, MOSI=23, MISO=19, CS=5
//   Motors: rear-left=12, rear-right=13, front-right=14, front-left=15
//   Battery divider (two 10k resistors): GPIO32

#include <SPI.h>
#include <FlixPeriph.h>

// ---- Hardware config ----
const int IMU_SCK_PIN = 18, IMU_MISO_PIN = 19, IMU_MOSI_PIN = 23, IMU_CS_PIN = 5;
const int IMU_MODEL = 1; // 1 = MPU9250 (GY-91), see FlixPeriph IMU::create()

const int MOTOR_PINS[4] = {12, 13, 14, 15};
const char *MOTOR_NAMES[4] = {"Rear Left", "Rear Right", "Front Right", "Front Left"};
const int PWM_FREQUENCY = 78000; // Hz, matches flix's motors.ino
const int PWM_RESOLUTION = 10;   // bits, matches flix's motors.ino

const int BATTERY_PIN = 32;
const float BATTERY_DIVIDER_SCALE = 2.0; // two equal 10k resistors halve the voltage

const float GYRO_STATIONARY_LIMIT = 500.0; // deg/s, board must be still on the bench
const float ONE_G = 9.80665;               // m/s^2

enum Result { RESULT_PASS, RESULT_FAIL, RESULT_WARN };

IMU *imu = nullptr;
Result imuResult = RESULT_FAIL;
Result motorResult = RESULT_PASS; // visual confirmation, can't be auto-verified
Result batteryResult = RESULT_FAIL;
Result failsafeResult = RESULT_FAIL;
float lastVoltage = NAN;

const char *resultName(Result r) {
	if (r == RESULT_PASS) return "PASS";
	if (r == RESULT_WARN) return "WARN";
	return "FAIL";
}

int dutyForFraction(float fraction) {
	fraction = constrain(fraction, 0.0, 1.0);
	return round(fraction * ((1 << PWM_RESOLUTION) - 1));
}

void setup() {
	Serial.begin(115200);
	delay(500);
	Serial.println("\n=== ASME Microdrones — Smoke Test ===");
	Serial.println("Make sure propellers are REMOVED before continuing.\n");

	testIMU();
	testMotors();
	testBattery();
	testFailsafe();

	printSummary();
}

void loop() {
	// Nothing to do — smoke test runs once on boot.
}

// ---- Test 1: IMU ----
void testIMU() {
	Serial.println("--- Test 1: IMU ---");

	SPI.begin(IMU_SCK_PIN, IMU_MISO_PIN, IMU_MOSI_PIN);
	imu = IMU::create(IMU_MODEL, SPI, IMU_CS_PIN, -1);
	imu->begin();

	if (imu->status() != 0) {
		Serial.printf("IMU init failed, status code %d\n", imu->status());
		imuResult = RESULT_FAIL;
		return;
	}

	imu->setAccelRange(IMU::ACCEL_RANGE_4G);
	imu->setGyroRange(IMU::GYRO_RANGE_2000DPS);
	imu->setDLPF(IMU::DLPF_MAX);
	imu->setRate(IMU::RATE_1KHZ_APPROX);

	bool allZero = true;
	bool outOfRange = false;
	const int samples = 10;

	for (int i = 0; i < samples; i++) {
		imu->waitForData();
		float gx, gy, gz, ax, ay, az;
		imu->getGyro(gx, gy, gz);
		imu->getAccel(ax, ay, az);

		Serial.printf("  sample %2d  gyro(rad/s): %7.3f %7.3f %7.3f  accel(m/s^2): %7.3f %7.3f %7.3f\n",
			i + 1, gx, gy, gz, ax, ay, az);

		if (gx != 0 || gy != 0 || gz != 0 || ax != 0 || ay != 0 || az != 0) allZero = false;

		float gyroMagDeg = sqrt(gx * gx + gy * gy + gz * gz) * RAD_TO_DEG;
		if (gyroMagDeg > GYRO_STATIONARY_LIMIT) outOfRange = true;
		if (i == samples - 1 && (az < 0.7 * ONE_G || az > 1.3 * ONE_G)) outOfRange = true; // board should be resting flat
	}

	if (allZero) {
		Serial.println("All readings were zero — check SPI wiring.");
		imuResult = RESULT_FAIL;
	} else if (outOfRange) {
		Serial.println("Readings out of expected range — check IMU is stationary and level.");
		imuResult = RESULT_FAIL;
	} else {
		imuResult = RESULT_PASS;
	}
	Serial.println();
}

// ---- Test 2: Motor spin ----
void testMotors() {
	Serial.println("--- Test 2: Motor spin (25% throttle, one at a time) ---");

	for (int i = 0; i < 4; i++) {
		ledcAttach(MOTOR_PINS[i], PWM_FREQUENCY, PWM_RESOLUTION);
	}

	for (int i = 0; i < 4; i++) {
		Serial.printf("Motor %d (%s, GPIO%d): spinning...\n", i, MOTOR_NAMES[i], MOTOR_PINS[i]);
		ledcWrite(MOTOR_PINS[i], dutyForFraction(0.25));
		delay(1500);
		ledcWrite(MOTOR_PINS[i], 0);
		delay(2000);
	}

	Serial.println("Did all motors spin in the correct position and direction?");
	Serial.println("(Check against the flix motor map in docs/wiring.md)\n");
}

// ---- Test 3: Battery voltage ----
void testBattery() {
	Serial.println("--- Test 3: Battery voltage ---");

	float v = analogReadMilliVolts(BATTERY_PIN) * BATTERY_DIVIDER_SCALE / 1000.0;
	lastVoltage = v;
	Serial.printf("Measured: %.2f V\n", v);

	if (v < 3.0 || v > 4.3) {
		batteryResult = RESULT_FAIL;
	} else if (v < 3.3 || v > 4.25) {
		batteryResult = RESULT_WARN;
	} else {
		batteryResult = RESULT_PASS;
	}
	Serial.println();
}

// ---- Test 4: Failsafe ----
void testFailsafe() {
	Serial.println("--- Test 4: Failsafe cutoff ---");

	for (int i = 0; i < 4; i++) {
		ledcWrite(MOTOR_PINS[i], dutyForFraction(0.20));
	}
	delay(2000);

	Serial.println("Simulating radio loss...");
	unsigned long cutStart = micros();
	bool radioLost = true;
	if (radioLost) {
		for (int i = 0; i < 4; i++) ledcWrite(MOTOR_PINS[i], 0);
	}
	unsigned long cutDuration = micros() - cutStart;

	bool allZero = true;
	for (int i = 0; i < 4; i++) {
		if (ledcRead(MOTOR_PINS[i]) != 0) allZero = false;
	}

	Serial.printf("Cutoff took %lu us, all motors zero: %s\n", cutDuration, allZero ? "yes" : "no");
	failsafeResult = (allZero && cutDuration < 100000) ? RESULT_PASS : RESULT_FAIL;
	Serial.println();
}

void printSummary() {
	Serial.println("=== SMOKE TEST RESULTS ===");
	Serial.printf("IMU:      %s\n", resultName(imuResult));
	Serial.printf("MOTORS:   %s — visual confirmation needed\n", resultName(motorResult));
	Serial.printf("BATTERY:  %s (%.2fV)\n", resultName(batteryResult), lastVoltage);
	Serial.printf("FAILSAFE: %s\n", resultName(failsafeResult));
}
