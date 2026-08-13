# Sources

Where the code in [`build1-flix/test-scripts/`](../build1-flix/test-scripts/)
came from. Written up so nobody has to guess what's borrowed, what's
standard-protocol boilerplate, and what's original to this club.

Only [`okalachev/flix`](https://github.com/okalachev/flix) was used as a
reference, pinned in this repo as the submodule at
[`build1-flix/flix`](../build1-flix/flix), commit
[`7312aef`](https://github.com/okalachev/flix/commit/7312aeff325302dd554cd968b598203c47ebc815)
(2026-08-12). File headers in that repo carry `Copyright (c) 2023 Oleg
Kalachev <okalachev@gmail.com>`; no separate `LICENSE` file was present at
that commit. [`rtlopez/esp-fc`](https://github.com/rtlopez/esp-fc) (the
Build 2 platform) has not been used yet — nothing below or in the test
scripts is sourced from it.

## Reused from `okalachev/flix`

| What was reused | Where it's used here | Source in flix |
|---|---|---|
| IMU init — `SPI.begin(sck,miso,mosi)`, `IMU::create(model, SPI, cs, int)`, `imu->begin()`, `status()`, `whoAmI()` | all three scripts | [`flix/imu.ino:29-46`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/imu.ino#L29-L46) (`setupIMU()`) |
| IMU config — `setAccelRange(ACCEL_RANGE_4G)`, `setGyroRange(GYRO_RANGE_2000DPS)`, `setDLPF(DLPF_MAX)`, `setRate(RATE_1KHZ_APPROX)` | all three scripts | [`flix/imu.ino:48-54`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/imu.ino#L48-L54) (`configureIMU()`) |
| Reading samples — `waitForData()`, `getGyro()`, `getAccel()` | all three scripts | [`flix/imu.ino:56-60`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/imu.ino#L56-L60) (`readIMU()`) |
| `imuModel` value (`1` = MPU9250, for the GY-91 board) | all three scripts | [`flix/imu.ino:14`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/imu.ino#L14) |
| Motor pin map `{12, 13, 14, 15}`, PWM frequency 78000Hz, resolution 10-bit | all three scripts | [`flix/motors.ino:10-12`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/motors.ino#L10-L12) |
| `ledcAttach(pin, freq, res)` / `ledcWrite(pin, duty)` calling convention | all three scripts | [`flix/motors.ino:19-35`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/motors.ino#L19-L35) |
| Duty-cycle formula `round(value * ((1 << resolution) - 1))` | all three scripts | [`flix/motors.ino:45-47`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/motors.ino#L45-L47) (`getDutyCycle()`) |
| Battery read — `analogReadMilliVolts(pin) * scale / 1000.0`, `voltageScale = 2` | smoke_test, tethered_hover_demo, preflight_check | [`flix/power.ino:14-29`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/power.ino#L14-L29) |
| `Serial.begin(115200)` | all three scripts | [`flix/flix.ino:19`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/flix.ino#L19) |
| Toolchain requirements — ESP32 core 3.3.10, board "WEMOS D1 MINI ESP32", `FlixPeriph` library | [`build1-flix/test-scripts/README.md`](../build1-flix/test-scripts/README.md) | [`docs/usage.md:51-56`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/docs/usage.md#L51-L56), [`docs/troubleshooting.md:9`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/docs/troubleshooting.md#L9) |

## Written for this club, not sourced from either repo

- The 45° tilt cutoff, 100Hz non-blocking safety loop, and ARM/STOP command
  handling in `tethered_hover_demo.ino`. flix's own disarm tilt is 120°
  ([`flix/safety.ino:11`](https://github.com/okalachev/flix/blob/7312aeff325302dd554cd968b598203c47ebc815/flix/safety.ino#L11)) —
  this repo uses the tighter 45° from `CLAUDE.md` Section 3 since it's a
  bench safety guard, not flix's real in-flight disarm threshold.
- The SBUS frame sync/decode in `preflight_check.ino` — a standard public
  SBUS bit-unpacking scheme (11-bit channels packed across 22 bytes).
  flix doesn't implement SBUS decoding in the files referenced above, and
  esp-fc's CRSF/receiver code was never opened for this.
- All PASS/FAIL/WARN/SKIP threshold logic, drift/level math, and the overall
  test structure — driven by the Section 1/3/8 specs in
  [`../CLAUDE.md`](../CLAUDE.md), not by either repo.
