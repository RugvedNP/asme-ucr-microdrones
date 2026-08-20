# Build 1 (flix) test scripts

Bench/pre-flight sketches for the flix platform, generated from the prompts in
[`../../docs/prompts/`](../../docs/prompts). Each is a self-contained Arduino sketch
(folder name matches the `.ino` file, as Arduino IDE requires) reusing the
same wiring, PWM settings, and `FlixPeriph` IMU driver as the real firmware
in [`../flix`](../flix), so results here are representative of the real
firmware's behavior.

Run them in this order:

1. **`smoke_test/`** — props OFF, bench only. Checks IMU, spins each motor
   briefly for a position/direction check, reads battery, and times the
   failsafe cutoff. Run this once right after soldering.
2. **`tethered_hover_demo/`** — props ON, drone tethered/hand-restrained.
   Open-loop throttle ramp to confirm the hardware produces thrust and the
   tilt/STOP safety cuts work. Not the real flight controller — no PID loop.
3. **`preflight_check/`** — props OFF, bench only. Final go/no-go checklist
   before the first untethered flight: IMU init + calibration drift, level
   check, motor pulse, RC link (SBUS, optional), battery, failsafe, free heap.

All three require the same Arduino IDE setup as flix itself: ESP32 core
3.3.10, board "WEMOS D1 MINI ESP32", and the `FlixPeriph` library from the
Library Manager. Serial Monitor at 115200 baud.
