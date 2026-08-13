// ASME @ UCR Microdrones — Build 1 (flix platform) — Pre-Flight Validation
//
// !! REMOVE PROPELLERS BEFORE RUNNING THIS SKETCH !!
//
// Final go/no-go checklist before the first untethered flight. Runs all
// checks automatically on boot and prints a GO / NO-GO verdict.
//
// Setup: same as smoke_test.ino (ESP32 core 3.3.10, board "WEMOS D1 MINI
// ESP32", FlixPeriph library, Serial Monitor at 115200 baud).
//
// Critical checks (a FAIL here forces NO-GO): IMU init, IMU calibration,
// accelerometer/level, battery, failsafe, free memory.
// Non-critical checks (FAIL degrades to SKIP if the hardware isn't fitted):
// motor response (needs a current sensor we don't have), RC link (only
// relevant if flying with a receiver instead of a gamepad).

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
const float BATTERY_MIN_VOLTS = 3.6;
const float BATTERY_MAX_VOLTS = 4.3;

const int RC_RX_PIN = 4; // SBUS signal, UART2

const float ONE_G = 9.80665;
const float GYRO_DRIFT_LIMIT_DEG = 5.0;
const unsigned long FREE_HEAP_MIN = 50000;

enum Result { RESULT_PASS, RESULT_FAIL, RESULT_SKIP };

IMU *imu = nullptr;
bool overallGo = true;

const char *resultName(Result r) {
	if (r == RESULT_PASS) return "PASS";
	if (r == RESULT_SKIP) return "SKIP";
	return "FAIL";
}

// Prints one checklist line and folds critical failures into the overall verdict.
void report(const char *name, Result r, const char *detail, bool critical) {
	Serial.printf("%-16s %-4s  %s\n", name, resultName(r), detail);
	if (critical && r == RESULT_FAIL) overallGo = false;
}

int dutyForFraction(float fraction) {
	fraction = constrain(fraction, 0.0, 1.0);
	return round(fraction * ((1 << PWM_RESOLUTION) - 1));
}

void setup() {
	Serial.begin(115200);
	delay(500);
	Serial.println("\n=== ASME Microdrones — Pre-Flight Validation ===");
	Serial.println("Make sure propellers are REMOVED before continuing.\n");

	for (int i = 0; i < 4; i++) ledcAttach(MOTOR_PINS[i], PWM_FREQUENCY, PWM_RESOLUTION);

	bool imuOk = checkImuInit();
	checkImuCalibration(imuOk);
	checkAccelerometer(imuOk);
	checkMotorResponse();
	checkRadioLink();
	checkBattery();
	checkFailsafe();
	checkFreeMemory();

	Serial.println();
	Serial.println("=== PRE-FLIGHT VALIDATION ===");
	Serial.printf("OVERALL: %s\n", overallGo ? "GO" : "NO-GO");
	if (!overallGo) Serial.println("NO-GO — DO NOT FLY");
}

void loop() {
	// Nothing to do — checklist runs once on boot.
}

// ---- 1. IMU init ----
bool checkImuInit() {
	SPI.begin(IMU_SCK_PIN, IMU_MISO_PIN, IMU_MOSI_PIN);
	imu = IMU::create(IMU_MODEL, SPI, IMU_CS_PIN, -1);
	imu->begin();

	char detail[48];
	bool ok = (imu->status() == 0);
	snprintf(detail, sizeof(detail), "status=%d who am I=0x%02X", imu->status(), imu->whoAmI());
	report("IMU_INIT", ok ? RESULT_PASS : RESULT_FAIL, detail, true);

	if (ok) {
		imu->setAccelRange(IMU::ACCEL_RANGE_4G);
		imu->setGyroRange(IMU::GYRO_RANGE_2000DPS);
		imu->setDLPF(IMU::DLPF_MAX);
		imu->setRate(IMU::RATE_1KHZ_APPROX);
	}
	return ok;
}

// ---- 2. IMU calibration / gyro drift ----
void checkImuCalibration(bool imuOk) {
	if (!imuOk) {
		report("IMU_CALIB", RESULT_FAIL, "skipped, IMU not initialized", true);
		return;
	}

	const int samples = 200;
	float minX = INFINITY, minY = INFINITY, minZ = INFINITY;
	float maxX = -INFINITY, maxY = -INFINITY, maxZ = -INFINITY;

	for (int i = 0; i < samples; i++) {
		imu->waitForData();
		float gx, gy, gz;
		imu->getGyro(gx, gy, gz);
		gx *= RAD_TO_DEG; gy *= RAD_TO_DEG; gz *= RAD_TO_DEG;
		minX = min(minX, gx); maxX = max(maxX, gx);
		minY = min(minY, gy); maxY = max(maxY, gy);
		minZ = min(minZ, gz); maxZ = max(maxZ, gz);
	}

	float driftX = maxX - minX, driftY = maxY - minY, driftZ = maxZ - minZ;
	float worstDrift = max(driftX, max(driftY, driftZ));

	char detail[48];
	snprintf(detail, sizeof(detail), "drift %.2f/%.2f/%.2f deg/s", driftX, driftY, driftZ);
	report("IMU_CALIB", worstDrift < GYRO_DRIFT_LIMIT_DEG ? RESULT_PASS : RESULT_FAIL, detail, true);
}

// ---- 3. Accelerometer / level ----
void checkAccelerometer(bool imuOk) {
	if (!imuOk) {
		report("ACCEL", RESULT_FAIL, "skipped, IMU not initialized", true);
		return;
	}

	imu->waitForData();
	float ax, ay, az;
	imu->getAccel(ax, ay, az);

	float magnitudeG = sqrt(ax * ax + ay * ay + az * az) / ONE_G;
	float roll = atan2(ay, az) * RAD_TO_DEG;
	float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * RAD_TO_DEG;

	bool ok = magnitudeG > 0.9 && magnitudeG < 1.1 && fabs(roll) < 5.0 && fabs(pitch) < 5.0;

	char detail[64];
	snprintf(detail, sizeof(detail), "%.2fg, roll=%.1f deg, pitch=%.1f deg", magnitudeG, roll, pitch);
	report("ACCEL", ok ? RESULT_PASS : RESULT_FAIL, detail, true);
}

// ---- 4. Motor response (visual/audible only, no current sensor fitted) ----
void checkMotorResponse() {
	for (int i = 0; i < 4; i++) {
		ledcWrite(MOTOR_PINS[i], dutyForFraction(0.20));
		delay(50);
		ledcWrite(MOTOR_PINS[i], 0);
		delay(200);
	}
	report("MOTOR_RESP", RESULT_SKIP, "pulsed all 4, confirm visually/audibly (no current sensor wired)", false);
}

// ---- 5. RC link (SBUS on UART2, optional hardware) ----
bool readSbusFrame(uint16_t *channels) {
	Serial2.begin(100000, SERIAL_8E2, RC_RX_PIN, -1, true); // SBUS: 100kbaud, 8E2, inverted
	unsigned long deadline = millis() + 1500;
	uint8_t frame[25];

	while (millis() < deadline) {
		if (!Serial2.available()) continue;
		if (Serial2.read() != 0x0F) continue; // look for SBUS start byte

		frame[0] = 0x0F;
		int got = Serial2.readBytes(frame + 1, 24); // rest of the frame, blocks briefly
		if (got != 24) continue;

		uint8_t endByte = frame[24];
		if ((endByte & 0x0F) != 0x00 && (endByte & 0x0F) != 0x04) continue; // not a recognized SBUS end byte

		uint8_t *p = frame + 1; // 22 bytes of packed 11-bit channel data
		channels[0] = (uint16_t)((p[0]      | p[1] << 8))                        & 0x07FF;
		channels[1] = (uint16_t)((p[1] >> 3  | p[2] << 5))                       & 0x07FF;
		channels[2] = (uint16_t)((p[2] >> 6  | p[3] << 2 | p[4] << 10))          & 0x07FF;
		channels[3] = (uint16_t)((p[4] >> 1  | p[5] << 7))                       & 0x07FF;
		Serial2.end();
		return true;
	}
	Serial2.end();
	return false;
}

void checkRadioLink() {
	uint16_t channels[4];
	if (!readSbusFrame(channels)) {
		report("RC_LINK", RESULT_SKIP, "no SBUS frames seen, ok if flying via USB gamepad", false);
		return;
	}

	bool allInRange = true;
	char detail[64];
	int pos = snprintf(detail, sizeof(detail), "us:");
	for (int i = 0; i < 4; i++) {
		int us = round(channels[i] * 0.625 + 880); // raw 172..1811 -> ~1000..2000us
		pos += snprintf(detail + pos, sizeof(detail) - pos, " %d", us);
		if (us < 950 || us > 2050) allInRange = false;
	}
	report("RC_LINK", allInRange ? RESULT_PASS : RESULT_FAIL, detail, false);
}

// ---- 6. Battery ----
void checkBattery() {
	float v = analogReadMilliVolts(BATTERY_PIN) * BATTERY_DIVIDER_SCALE / 1000.0;
	char detail[24];
	snprintf(detail, sizeof(detail), "%.2f V", v);
	bool ok = v >= BATTERY_MIN_VOLTS && v <= BATTERY_MAX_VOLTS;
	report("BATTERY", ok ? RESULT_PASS : RESULT_FAIL, detail, true);
}

// ---- 7. Failsafe ----
void checkFailsafe() {
	for (int i = 0; i < 4; i++) ledcWrite(MOTOR_PINS[i], dutyForFraction(0.20));
	delay(500);

	unsigned long cutStart = micros();
	for (int i = 0; i < 4; i++) ledcWrite(MOTOR_PINS[i], 0);
	unsigned long cutDuration = micros() - cutStart;

	bool allZero = true;
	for (int i = 0; i < 4; i++) {
		if (ledcRead(MOTOR_PINS[i]) != 0) allZero = false;
	}

	char detail[32];
	snprintf(detail, sizeof(detail), "cut in %lu us", cutDuration);
	report("FAILSAFE", (allZero && cutDuration < 100000) ? RESULT_PASS : RESULT_FAIL, detail, true);
}

// ---- 8. Free memory ----
void checkFreeMemory() {
	uint32_t freeHeap = ESP.getFreeHeap();
	char detail[24];
	snprintf(detail, sizeof(detail), "%u bytes free", (unsigned)freeHeap);
	report("FREE_MEM", freeHeap > FREE_HEAP_MIN ? RESULT_PASS : RESULT_FAIL, detail, true);
}
