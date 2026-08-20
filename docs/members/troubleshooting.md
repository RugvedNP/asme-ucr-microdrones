# Troubleshooting

Common failures, most frequent first. Find your symptom, work down the checks
in order.

If your symptom isn't here, use
[`../prompts/09-quick-questions.md`](../prompts/09-quick-questions.md) — and
paste your actual Serial output, not a description of it.

---

## Arduino IDE can't see the board

1. Is the USB cable a **data** cable? Plenty of cables are charge-only. This
   is the answer more often than anyone expects.
2. Windows: install the
   [Silicon Labs USB-to-UART driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers).
3. Correct board selected? **WEMOS D1 MINI ESP32**.
4. Try a different USB port; some hubs don't supply enough current.

## Upload fails or times out

1. Some ESP32 boards need the BOOT button held while upload starts.
2. Close Serial Monitor — it can hold the port open.
3. **Disconnect the flight battery during upload.**
4. If it fails only after your drone is assembled but worked on the bare
   board, suspect something on GPIO12 or GPIO15 — those are boot-strapping
   pins, and a load on them can stop the ESP32 entering flash mode.

## Serial Monitor shows garbage characters

Baud rate. Set it to **115200**.

## IMU: FAIL

1. Check all four SPI wires against [CLAUDE.md](../../CLAUDE.md): SCK=18,
   MISO=19, MOSI=23, CS=5. Swapped MISO/MOSI is the classic error.
2. Is the IMU powered from **3.3V**, not 5V?
3. Reflow the IMU header joints — these are small pads and cold joints are
   common.
4. Run [`../prompts/09-quick-questions.md`](../prompts/09-quick-questions.md)
   with the whoAmI value the preflight script prints; a wrong value means the
   ESP32 is talking to something, but not the chip we expect.
5. Make sure no other MPU-9250 library is installed alongside `FlixPeriph` —
   flix's own docs warn that conflicting libraries break the build.

## A motor won't spin

Work outward from the ESP32:

1. Does the *other* motors' behavior look right? If all four are dead,
   suspect power, not signal.
2. Multimeter on the MOSFET gate while the test runs — do you see the pin
   going high?
3. Is the **pull-down resistor** present on that gate? Missing pull-downs
   cause both dead motors and phantom spin-ups.
4. Check motor lead solder joints — they take mechanical stress and crack.
5. Swap the motor with a known-good one to isolate motor vs. circuit.

Full step-by-step debug sequence:
[`../prompts/09-quick-questions.md`](../prompts/09-quick-questions.md).

## Motors spin, but the wrong ones

Your signal wires are crossed. The smoke test names each motor and GPIO as it
spins — note which physical motor actually moves for each, and re-map the
wires to match [CLAUDE.md](../../CLAUDE.md).

## A motor spins the wrong direction

Swap that motor's two leads. Then confirm the **prop type** (A vs B) matches
that position on the flix motor map — right motor direction with the wrong
prop still produces downforce.

## Motors twitch on power-up

Missing or wrong pull-down resistors on the MOSFET gates, or you've put a
motor on a boot-strapping pin without one. Props off until this is fixed.

## BATTERY: FAIL or a wildly wrong voltage

1. Reading roughly **half** what a multimeter says at the pack? Your voltage
   divider scale is right but something is bypassing it — check both 10kΩ
   resistors are actually in circuit.
2. Reading **double**? You've measured the pack directly into GPIO32. Stop —
   that's over the ESP32's safe input range.
3. Reading 0? Broken divider connection, or the wrong pin.

## Drone tilts or flips immediately on takeoff

Nearly always one of:

1. **Loose motors.** flix's docs are blunt about this — vibration wrecks
   attitude estimation. Motors must be tight enough not to move at all.
2. **Wrong prop on a position** (A vs B swapped).
3. **Motor order crossed** — passes the smoke test only if you didn't
   actually watch which motor moved.
4. IMU not mounted flat, or mounted rotated relative to the frame.

## Preflight says NO-GO but everything seems fine

Read *which* check failed — the summary line names it.

- `IMU_CALIB` failing → the drone wasn't still during the 200-sample drift
  check. Set it on a flat table, don't touch it, rerun.
- `ACCEL` failing → drone isn't level, or the IMU is mounted at an angle.
- `FREE_MEM` failing → something is wrong with the build, not your hardware;
  ask an officer.

## It flew, but wobbles or feels twitchy

That's tuning, not a fault. For the Winter brushless build, record a blackbox
log and use
[`../prompts/05-blackbox-analysis.md`](../prompts/05-blackbox-analysis.md).
For the Fall build, first rule out loose motors and a bent prop.
