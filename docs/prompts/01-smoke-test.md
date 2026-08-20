# Smoke test sketch

> **Already generated.** The working sketch is at
> [`../../build1-flix/test-scripts/smoke_test/`](../../build1-flix/test-scripts/smoke_test).
> Use this prompt only to regenerate or modify it.

Bench test after soldering, before first flight. **Props off.**

---

```
Generate an Arduino sketch called "smoke_test.ino" for our Build 1 flix hardware that runs the following test sequence automatically on boot. Props will NOT be attached — this is a bench test only.

TEST 1 — IMU CHECK:
- Initialize the MPU-9250 on SPI using the FlixPeriph library and the pins from the project context.
- Read 10 samples of gyro + accelerometer data.
- Print each sample to Serial.
- PASS if all readings are non-zero and within reasonable range (gyro < 500 deg/s when stationary, accel Z ~= 1g +/- 0.3g).
- FAIL if SPI communication fails, readings are all zeros, or values are wildly out of range.

TEST 2 — MOTOR SPIN TEST:
- For each motor (0 through 3), spin it at 25% duty cycle for 1.5 seconds, then stop.
- Wait 2 seconds between motors.
- Print which motor is spinning and its GPIO pin so the builder can visually confirm correct position and direction.
- After all 4, prompt on Serial: "Did all motors spin in the correct position and direction? (Check against flix motor map)"

TEST 3 — BATTERY VOLTAGE CHECK:
- Read the ADC on GPIO32 (voltage divider: two 10k resistors = half of battery voltage).
- Convert to actual battery voltage.
- PASS if voltage is between 3.3V and 4.25V.
- WARN if between 3.0V and 3.3V (low battery).
- FAIL if below 3.0V or above 4.3V (dead cell or measurement error).

TEST 4 — FAILSAFE TEST:
- Spin all 4 motors at 20% duty cycle.
- After 2 seconds, simulate radio loss by setting a "radioLost" flag to true.
- Verify all motors stop within 100ms.
- PASS if all motor PWM outputs read 0 after the flag is set.
- FAIL if any motor is still running.

At the end, print a summary:
"=== SMOKE TEST RESULTS ==="
"IMU:      [PASS/FAIL]"
"MOTORS:   [PASS/FAIL — visual confirmation needed]"
"BATTERY:  [PASS/FAIL/WARN] ([voltage]V)"
"FAILSAFE: [PASS/FAIL]"

Use the ESP32 Arduino framework with ledcAttach/ledcWrite for motor PWM, matching flix's own PWM settings (78kHz, 10-bit). Include all necessary library includes.
```
