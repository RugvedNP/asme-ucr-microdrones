# ASME @ UCR Microdrones — Claude Code Master Prompt

How to use this file: Open Claude Code in your terminal (`claude` command). Paste the relevant section below depending on what you need. Each section is self-contained — you don't need to paste the whole file. Replace anything in `[BRACKETS]` with your actual values.

## 0. Project Context (paste this FIRST in any Claude Code session)

```
You are helping the ASME @ UCR Microdrones club build, test, and debug ESP32-based micro quadcopters. We have two build tracks:

BUILD 1 (Fall quarter — "flix" platform):
- Repo: https://github.com/okalachev/flix (clone locally first)
- MCU: ESP32 Mini (ESP32 Dev Module in Arduino IDE)
- IMU: GY-91 (MPU-9250) connected via VSPI
  - SCK = GPIO18, MOSI = GPIO23, MISO = GPIO19, CS = GPIO5
- Motors: 4x 8520 3.7V brushed, driven by UMW 100N03A MOSFETs with 10kΩ pull-down resistors
  - Motor 0 (Rear Left, CCW, prop B): GPIO12
  - Motor 1 (Rear Right, CW, prop A): GPIO13
  - Motor 2 (Front Right, CCW, prop B): GPIO14
  - Motor 3 (Front Left, CW, prop A): GPIO15
- Battery: 3.7V single-cell LiPo, 850mAh, ≥25C discharge
- Battery voltage divider: two 10kΩ resistors on GPIO32 (optional)
- RC receiver (optional): SBUS on UART2, signal pin GPIO4
- Frame: 3D-printed from flix repo STL files
- Firmware: flix Arduino firmware (flix/flix.ino)
- Radio control: USB gamepad over Wi-Fi, or RC transmitter via SBUS/ESP-NOW

BUILD 2 (Winter quarter — "ESP-FC" platform):
- Repo: https://github.com/rtlopez/esp-fc
- MCU: ESP32 or ESP32-S3
- IMU: SPI gyro (MPU6050/MPU9250/ICM20602/BMI160)
- Motors: 4x brushless (1103–1204 size) with DShot-capable 4-in-1 ESC
- Receiver: CRSF/ELRS on UART
- Firmware: ESP-FC (Betaflight-compatible, configured via Betaflight Configurator v10.10)
- Frame: 2.5–3.5" toothpick/micro

We are college students. Keep code well-commented, safe, and beginner-friendly. Always include failsafe logic. Never spin motors without explicit user confirmation in test code. All test sketches should print clear PASS/FAIL to Serial at 115200 baud.

```

## 1. Hardware Smoke Test (paste after Section 0)

Use this after soldering is done, BEFORE first flight. Props must be OFF.

```
Generate an Arduino sketch called "smoke_test.ino" for our Build 1 flix hardware that runs the following test sequence automatically on boot. Props will NOT be attached — this is a bench test only.

TEST 1 — IMU CHECK:
- Initialize the MPU-9250 (or MPU-6050 if that's what we have) on SPI with the pins from the project context.
- Read 10 samples of gyro + accelerometer data.
- Print each sample to Serial.
- PASS if all readings are non-zero and within reasonable range (gyro < 500 deg/s when stationary, accel Z ≈ 1g ± 0.3g).
- FAIL if SPI communication fails, readings are all zeros, or values are wildly out of range.

TEST 2 — MOTOR SPIN TEST:
- For each motor (0 through 3), spin it at 25% duty cycle for 1.5 seconds, then stop.
- Wait 2 seconds between motors.
- Print which motor is spinning and its GPIO pin so the builder can visually confirm correct position and direction.
- After all 4, prompt on Serial: "Did all motors spin in the correct position and direction? (Check against flix motor map)"

TEST 3 — BATTERY VOLTAGE CHECK:
- Read the ADC on GPIO32 (voltage divider: two 10kΩ resistors = half of battery voltage).
- Convert to actual battery voltage.
- PASS if voltage is between 3.3V and 4.25V (healthy single-cell LiPo range).
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

Use the ESP32 Arduino framework. Use analogWrite or ledcWrite for motor PWM (whichever is appropriate for this ESP32 Arduino core version). Include all necessary library includes.

```

## 2. Wiring Review (paste after Section 0)

Use this to catch wiring mistakes before powering on.

```
I'm about to power on my Build 1 flix drone for the first time. Review my wiring for safety issues, shorts, and mismatches against the official flix schematics (https://github.com/okalachev/flix/blob/master/docs/wiring.md).

My actual wiring:
[PASTE YOUR WIRING HERE — example format below]

ESP32 VCC ← Battery + (through switch)
ESP32 GND ← Battery -
GPIO18 → GY-91 SCL
GPIO23 → GY-91 SDA
GPIO19 → GY-91 SAO
GPIO5  → GY-91 NCS
GY-91 3.3V ← ESP32 3.3V
GY-91 GND ← ESP32 GND
GPIO12 → MOSFET gate (Motor 0, rear left)
GPIO13 → MOSFET gate (Motor 1, rear right)
GPIO14 → MOSFET gate (Motor 2, front right)
GPIO15 → MOSFET gate (Motor 3, front left)
Each MOSFET: drain → motor −, source → GND, 10kΩ between gate and source
Each motor: + → battery VCC (through common bus)
GPIO4 ← RC receiver signal (SBUS)

Check for:
1. Any pins that conflict with ESP32 boot strapping pins (GPIO0, GPIO2, GPIO12, GPIO15 have boot-mode implications — is my motor assignment safe?)
2. Missing pull-down resistors on any MOSFET gate
3. Missing flyback/snubber protection on brushed motors (does flix's design handle this, or do I need diodes?)
4. Correct voltage levels (3.3V logic driving the MOSFET gates — is 3.3V enough for the 100N03A threshold voltage?)
5. Any risk of back-feeding voltage into the ESP32
6. Whether my SBUS receiver wiring needs an inverter (ESP32 supports software inversion — confirm)

```

## 3. Tethered Hover Demo (paste after Section 0)

Use this for the first powered indoor test. Drone should be tethered or hand-held.

```
Generate an Arduino sketch called "tethered_hover_demo.ino" for our Build 1 flix hardware. This is for the club's first indoor tethered hover test. The drone will be held by a tether or hand-restrained. Props WILL be on.

Requirements:
- On boot, run a quick IMU health check (gyro + accel responding, values in range). If it fails, print "IMU FAILED — DO NOT FLY" and halt.
- Read battery voltage on GPIO32. If below 3.4V, print "BATTERY TOO LOW — DO NOT FLY" and halt.
- Wait for a Serial command "ARM" (typed by the tester) before doing anything with motors. Print "Type ARM to begin hover test. ENSURE TETHER IS ATTACHED."
- Once "ARM" is received:
  1. Ramp all 4 motors from 0% to 35% throttle over 2 seconds (gradual spin-up).
  2. Hold at 35% throttle for 4 seconds (this should be near hover for a ~80g flix build).
  3. Ramp back down to 0% over 2 seconds.
  4. Print "Test complete. Motors disarmed."
- During the entire sequence, check IMU data at 100Hz. If the drone tilts beyond ±45 degrees on any axis, immediately cut all motors and print "TILT SAFETY CUT — motors killed."
- If Serial receives "STOP" at any time, immediately cut all motors.
- After the test, print peak tilt angle observed and average battery voltage during the test.

This is NOT a full flight controller — it's a simple open-loop throttle ramp with safety guards. The flix PID loop is NOT running here. The purpose is to verify that the hardware produces thrust and the safety systems work before handing off to the real flix firmware.

```

## 4. Betaflight CLI Dump Review (paste after Section 0)

Use this after configuring ESP-FC in Betaflight Configurator for Build 2.

```
I just configured my Build 2 ESP-FC drone in Betaflight Configurator. Here is my CLI dump from the Betaflight CLI tab (type "dump" to get this). Review it for misconfigurations, safety issues, and anything that doesn't match a micro brushless quad setup.

My hardware:
- ESP32-S3 dev board running ESP-FC firmware
- IMU: [YOUR IMU MODEL, e.g., ICM20602 on SPI]
- Motors: 4x [YOUR MOTOR MODEL, e.g., 1103 8000KV] on DShot300
- ESC: [YOUR ESC, e.g., generic 4-in-1 12A BLHeli_S]
- Receiver: [YOUR RECEIVER, e.g., Happymodel EP1 ELRS 2.4GHz] on [UART NUMBER]
- Battery: [YOUR BATTERY, e.g., 1S 450mAh 75C]
- Frame: [YOUR FRAME, e.g., 2.5" toothpick]
- AUX channels: AUX1 = arm switch, AUX2 = angle/acro toggle

CLI dump:
[PASTE YOUR FULL CLI DUMP HERE]

Check for:
1. Motor protocol matches my ESCs (DShot300 for BLHeli_S is correct?)
2. Receiver protocol matches my ELRS receiver (CRSF on correct UART?)
3. PID values are reasonable for a micro quad (not too aggressive for a first flight)
4. Failsafe is configured to DROP (cut motors) not LAND (which requires GPS we don't have)
5. Arming is on the correct AUX range
6. Angle mode is available for beginners
7. Motor idle percentage is safe (not too low = motor desync, not too high = flips on arm)
8. Any ESP-FC-specific settings that differ from standard Betaflight and might cause issues
9. Pin mapping matches my actual wiring
10. Anything else that looks wrong or could cause a crash on first flight

```

## 5. Blackbox Log Analysis (paste after Section 0)

Use this after recording a test flight with blackbox enabled.

```
I have a blackbox log from a test flight of our Build 2 ESP-FC drone. The flight was [DESCRIBE: e.g., "a 30-second indoor hover in angle mode, the drone oscillated on the roll axis and felt twitchy"].

Analyze this data and tell me:
1. Is there visible gyro noise? What frequency range?
2. Are the PID outputs saturating (hitting max values)?
3. Are motors hitting 100% or 0% during the flight? (indicates the PID loop is running out of authority)
4. Is there a visible oscillation pattern? What axis? What frequency?
5. What specific PID changes would you recommend? Give me exact numbers or slider adjustments.
6. Is the D-term noisy? Should I lower D or add filtering?
7. Any signs of motor desync, ESC issues, or electrical noise?

Log data (CSV format from Betaflight Blackbox Explorer export):
[PASTE CSV DATA HERE — or provide the .bbl file path if running Claude Code locally]

```

## 6. Gazebo Simulation Setup (paste after Section 0)

Use this if a member doesn't have hardware yet and wants to practice with the flix simulator.

```
Help me set up the flix Gazebo simulator on my machine. I'm running [YOUR OS: Ubuntu 22.04 / Ubuntu 24.04 / macOS with Homebrew / WSL2 on Windows].

Walk me through:
1. Installing Gazebo (which version does flix need?)
2. Cloning the flix repo and building the simulation plugin
3. Launching the simulator
4. Connecting a USB gamepad or keyboard for control
5. What the expected behavior should look like when it's working correctly

Reference: https://github.com/okalachev/flix/blob/master/gazebo/README.md

If there are any known issues with my OS version, flag them and provide workarounds.

```

## 7. Custom Frame Iteration (paste after Section 0)

Use this when Rugved's team is modifying the flix frame for different IMU boards or motors.

```
I'm modifying the flix 3D-printed frame to accommodate a different IMU board. The original frame is designed for the GY-91 board with M3 mounting holes spaced [MEASURE AND INSERT: e.g., 17mm x 17mm].

My new IMU board is: [YOUR BOARD, e.g., GY-521 (MPU-6050)]
Its mounting hole spacing is: [MEASURE AND INSERT: e.g., 15.2mm x 15.2mm]
Its board dimensions are: [MEASURE AND INSERT: e.g., 20mm x 16mm]

The original flix frame STEP file is at: flix/docs/assets/flix-frame-1.1.step

Help me:
1. Identify which features in the STEP file define the IMU mounting holes
2. Calculate the coordinate changes needed to move the mounting posts
3. If I'm editing in [YOUR CAD: FreeCAD / Fusion 360 / OnShape], give me step-by-step instructions to modify the hole positions
4. Flag any structural concerns (will moving the holes weaken the arm roots? change the center of gravity?)
5. Suggest print settings if the modified area is thinner than the original

```

## 8. Full Pre-Flight Validation Script (paste after Section 0)

Use this as a final go/no-go check before the first untethered flight.

```
Generate an Arduino sketch called "preflight_check.ino" for our Build 1 flix hardware. This is the final validation before we fly untethered for the first time. It should be a comprehensive go/no-go checklist that runs automatically.

Run these checks in sequence and print results:

1. IMU INIT — SPI communication with MPU-9250/6050 successful? Whoami register returns expected value?
2. IMU CALIBRATION — Collect 200 gyro samples while stationary. Calculate gyro bias. Is drift < 5 deg/s on all axes?
3. ACCELEROMETER — Is measured gravity between 0.9g and 1.1g? Is the drone sitting level (pitch/roll < 5 degrees)?
4. MOTOR RESPONSE — Briefly pulse each motor (50ms at 20%). Does the ADC show a current spike? (Or if no current sensing: does the motor audibly click?) Skip this if you prefer visual-only confirmation.
5. RADIO LINK — Is the receiver producing valid data on GPIO4? Are stick values in the expected range (1000–2000μs)? Are all channels responding?
6. BATTERY — Voltage in safe range? Above 3.6V for a full-charge flight?
7. FAILSAFE — Simulate radio loss. Do all motors reach zero within 100ms?
8. FREE MEMORY — Is there enough heap for stable operation? (ESP32 should have >50KB free)

Print a final summary:
"=== PRE-FLIGHT VALIDATION ==="
[Each check: PASS / FAIL / SKIP with one-line detail]
"OVERALL: [GO / NO-GO]"

If ANY critical check fails (IMU, failsafe, battery), print "NO-GO — DO NOT FLY" in all caps. Non-critical fails (radio not connected if using gamepad, current sensing unavailable) should print SKIP, not FAIL.

```

## 9. Quick Reference: Common Claude Code Queries

These are one-liners you can paste directly:

```
# Check if a specific ESP32 GPIO pin is safe to use for motors (boot strapping concerns)
"Is GPIO[NUMBER] safe to use as a motor PWM output on ESP32? Any boot-mode conflicts?"

# Convert a Betaflight PID profile for micro quad
"Convert these Betaflight PID values from a 5-inch quad to something reasonable for a 2.5-inch micro: P[XX] I[XX] D[XX] on roll/pitch. Explain the scaling logic."

# Debug a motor that won't spin
"Motor on GPIO[XX] won't spin. MOSFET is 100N03A, pull-down is 10kΩ. ESP32 3.3V logic. What should I check with a multimeter? Give me a step-by-step debug sequence."

# Generate a battery voltage monitor
"Write a simple Arduino function for ESP32 that reads battery voltage on GPIO32 through a voltage divider (two 10kΩ resistors), converts to real voltage, and returns it as a float. Include ADC calibration notes for ESP32."

# Check if flix firmware compiles for a different ESP32 variant
"Will the flix firmware (github.com/okalachev/flix) compile for ESP32-C3 without modifications? What changes are needed?"

```

## Notes for Club Officers

* Always paste Section 0 first — it gives Claude Code the full hardware context so it doesn't hallucinate pin numbers or assume wrong IMU models.
* Replace `[BRACKETS]` with your actual values before pasting. Claude Code works best with specific, concrete details.
* Review generated code before uploading to hardware. Claude Code is excellent but not infallible — a human should sanity-check pin assignments against actual wiring before flashing.
* Save good outputs. When Claude Code generates a test sketch that works, save it to the club's shared repo (`test-scripts/`) so the next person doesn't have to regenerate it.
* Iterate. If the output isn't quite right, tell Claude Code what's wrong and ask it to fix it. "Motor 2 should be on GPIO14, not GPIO15 — fix the sketch" is a perfectly good follow-up.

Generated for ASME @ UCR Microdrones Program — August 2026. Based on flix v1.5 (github.com/okalachev/flix) and ESP-FC v0.2.1 (github.com/rtlopez/esp-fc).
