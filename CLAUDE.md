# Project instructions

Context for Claude Code working in this repo. Claude Code loads this file
automatically — you don't need to paste it.

> Looking for the paste-into-chat prompts that used to be in this file? They
> moved to [`docs/prompts/`](docs/prompts/), one file per task.

## What this project is

ASME @ UCR Microdrones — a student club project teaching mostly-beginner
undergraduates to build and fly ESP32-based micro quadcopters. Members work
in **pairs**, one drone per pair.

Two build tracks:

- **Build 1 (Fall)** — "flix" platform, brushed motors. Firmware:
  [okalachev/flix](https://github.com/okalachev/flix), vendored as a
  submodule at `build1-flix/flix/`.
- **Build 2 (Winter)** — "ESP-FC" platform, brushless.
  [rtlopez/esp-fc](https://github.com/rtlopez/esp-fc), Betaflight-compatible.
  Not started yet.

## Build 1 hardware

| | |
|---|---|
| MCU | ESP32 Mini — board "WEMOS D1 MINI ESP32", ESP32 core 3.3.10 |
| IMU | GY-91 (MPU-9250) over VSPI — SCK=18, MISO=19, MOSI=23, CS=5 |
| IMU driver | `FlixPeriph` library |
| Motors | 4x 8520 3.7V brushed via UMW 100N03A MOSFETs, 10kΩ pull-downs |
| Motor 0 | Rear Left, CCW, prop B — **GPIO12** |
| Motor 1 | Rear Right, CW, prop A — **GPIO13** |
| Motor 2 | Front Right, CCW, prop B — **GPIO14** |
| Motor 3 | Front Left, CW, prop A — **GPIO15** |
| Motor PWM | 78kHz, 10-bit, via `ledcAttach`/`ledcWrite` |
| Battery | 1S 3.7V LiPo, 850mAh, ≥25C |
| Battery sense | Two 10kΩ resistors on GPIO32 (scale 2.0), optional |
| RC receiver | SBUS on UART2, signal GPIO4, optional |
| Serial | 115200 baud |

These values match the real flix firmware. If you change them, check
`build1-flix/flix/flix/motors.ino`, `imu.ino`, and `power.ino` first.

## Build 2 hardware

ESP32 or ESP32-S3; SPI gyro (MPU6050/MPU9250/ICM20602/BMI160); 4x brushless
1103–1204 motors on a DShot-capable 4-in-1 ESC; CRSF/ELRS receiver on UART;
2.5–3.5" frame. Configured via Betaflight Configurator v10.10.

## Conventions for code in this repo

- **Audience is beginners.** Comment generously; explain *why*, not just what.
- **Always include failsafe logic.** Never generate code that spins motors
  without an explicit user confirmation step.
- Test sketches print clear **PASS / FAIL / WARN / SKIP** to Serial at 115200,
  and end with a summary block.
- Sketch header comments must state whether **props go on or off**.
- Reuse flix's own constants and calling conventions rather than inventing
  parallel ones — the test scripts are meant to be representative of the real
  firmware's behavior.
- Arduino requires each sketch in a folder matching its `.ino` filename.
- Safety-critical loops must be **non-blocking**. Don't use `delay()` where a
  tilt check or abort command needs to keep running.

## Repo layout

```
CLAUDE.md                      this file
README.md                      entry point for humans
docs/members/                  guides for students building a drone
docs/officers/                 planning docs for whoever runs the project
docs/prompts/                  paste-into-chat prompts, one per task
docs/SOURCES.md                citations for the test-script code
build1-flix/flix/              upstream flix firmware (submodule)
build1-flix/test-scripts/      our bench-test sketches
```

## Verification note

No ESP32 toolchain is set up in this repo, so sketches here have **not been
compile-verified**. Don't describe them as tested. Hardware behavior
(motor direction, IMU orientation, failsafe timing) can only be confirmed on
a real drone.
