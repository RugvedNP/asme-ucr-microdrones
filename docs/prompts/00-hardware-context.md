# Hardware context

Paste this **first** when using any AI tool other than Claude Code in this
repo. (Claude Code loads [`../../CLAUDE.md`](../../CLAUDE.md) automatically,
so you can skip this there.)

---

```
You are helping the ASME @ UCR Microdrones club build, test, and debug ESP32-based micro quadcopters. We have two build tracks:

BUILD 1 (Fall quarter — "flix" platform):
- Repo: https://github.com/okalachev/flix
- MCU: ESP32 Mini (board "WEMOS D1 MINI ESP32" in Arduino IDE, ESP32 core 3.3.10)
- IMU: GY-91 (MPU-9250) connected via VSPI
  - SCK = GPIO18, MOSI = GPIO23, MISO = GPIO19, CS = GPIO5
- Motors: 4x 8520 3.7V brushed, driven by UMW 100N03A MOSFETs with 10k pull-down resistors
  - Motor 0 (Rear Left, CCW, prop B): GPIO12
  - Motor 1 (Rear Right, CW, prop A): GPIO13
  - Motor 2 (Front Right, CCW, prop B): GPIO14
  - Motor 3 (Front Left, CW, prop A): GPIO15
  - PWM: 78kHz, 10-bit resolution, via ledcAttach/ledcWrite
- Battery: 3.7V single-cell LiPo, 850mAh, >=25C discharge
- Battery voltage divider: two 10k resistors on GPIO32 (optional)
- RC receiver (optional): SBUS on UART2, signal pin GPIO4
- Frame: 3D-printed from flix repo STL files
- Firmware: flix Arduino firmware (flix/flix.ino)
- IMU driver library: FlixPeriph
- Radio control: USB gamepad over Wi-Fi, or RC transmitter via SBUS/ESP-NOW

BUILD 2 (Winter quarter — "ESP-FC" platform):
- Repo: https://github.com/rtlopez/esp-fc
- MCU: ESP32 or ESP32-S3
- IMU: SPI gyro (MPU6050/MPU9250/ICM20602/BMI160)
- Motors: 4x brushless (1103-1204 size) with DShot-capable 4-in-1 ESC
- Receiver: CRSF/ELRS on UART
- Firmware: ESP-FC (Betaflight-compatible, configured via Betaflight Configurator v10.10)
- Frame: 2.5-3.5" toothpick/micro

We are college students, and most members are beginners. Keep code well-commented, safe, and beginner-friendly. Always include failsafe logic. Never spin motors without explicit user confirmation in test code. All test sketches should print clear PASS/FAIL to Serial at 115200 baud.
```
