# Build guide — Fall microdrone

The path from a bag of parts to a flying drone, in the order you'll actually
do it. You and your partner work through this together across your build
sessions.

Read [safety.md](safety.md) first. Don't skip stages — each one catches
mistakes that get much more expensive to find later.

---

## Stage 1 — Set up your laptop

Do this before your first build session so you aren't waiting on downloads.

1. Install [Arduino IDE](https://www.arduino.cc/en/software) (version 2).
2. In **Boards Manager**, install the **ESP32 core, version 3.3.10**.
   ([Espressif's guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide))
3. In **Library Manager**, install **`FlixPeriph`**.
4. Windows only: you may need the
   [Silicon Labs USB-to-UART driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
   for your laptop to see the board.
5. Board setting: **WEMOS D1 MINI ESP32**. Serial Monitor: **115200 baud**.

**Checkpoint:** plug in a bare ESP32, upload Arduino's `Blink` example, see
the LED blink. If that works, your toolchain is fine.

---

## Stage 2 — Print and prep the frame

The frame files live in the flix repo, already checked out in this project at
[`build1-flix/flix/`](../../build1-flix/flix).

- Follow flix's own [assembly docs](../../build1-flix/flix/docs/assembly.md).
- Clean up any stringing or brim before you mount anything.
- Dry-fit the ESP32 and motors before soldering. It is much easier to
  discover a mismatch now.

---

## Stage 3 — Solder

This is the slowest stage and the one most worth doing carefully. Bad solder
joints cause intermittent faults that look like software bugs and waste
entire sessions.

Order of operations:

1. Motors into the frame — **very tightly**. flix's docs are emphatic about
   this: loose motors vibrate, vibration corrupts the sensor readings, and
   the drone won't hold level. Tape them tight if needed.
2. MOSFETs, one per motor, with their pull-down resistors.
3. Motor leads to MOSFETs.
4. Power bus — battery leads, switch.
5. ESP32 signal wires to the MOSFET gates.
6. IMU board to the ESP32 over SPI.

The exact pin-by-pin wiring is in [CLAUDE.md](../../CLAUDE.md). Match it
exactly — our test scripts assume those pins.

**Do not connect the battery yet.**

---

## Stage 4 — Get your wiring reviewed

Before first power-on, have someone check your work. Reversed battery leads
destroy an ESP32 instantly.

Two ways to do this, do both:

- Ask an officer or an experienced member to eyeball it.
- Run the wiring review prompt:
  [`../prompts/02-wiring-review.md`](../prompts/02-wiring-review.md) — it
  checks for boot-pin conflicts, missing pull-downs, and back-feed risk.

**Checkpoint:** continuity-check battery + to battery − with the switch off.
If it beeps, you have a short. Find it before applying power.

---

## Stage 5 — Bench tests (props OFF)

Now you can power up. Run the smoke test:
[`build1-flix/test-scripts/smoke_test/`](../../build1-flix/test-scripts/smoke_test)

It checks the IMU, spins each motor one at a time so you can confirm
position and direction, reads the battery, and times the failsafe cutoff.

Watch for: each motor spinning in the position the Serial output names. If
motor 2 spins when the script says motor 1, your signal wires are crossed.

Everything must PASS before you go further. See [testing.md](testing.md) for
what each result means.

---

## Stage 6 — Props on, tethered

Attach props — **check A vs B prop types against the flix motor map**, a
reversed prop produces downforce instead of lift — then run:
[`build1-flix/test-scripts/tethered_hover_demo/`](../../build1-flix/test-scripts/tethered_hover_demo)

Drone tethered or hand-restrained. This confirms the hardware actually makes
thrust and that the tilt/STOP safety cuts work.

---

## Stage 7 — Preflight, then fly

Props off again for the final checklist:
[`build1-flix/test-scripts/preflight_check/`](../../build1-flix/test-scripts/preflight_check)

It prints **GO** or **NO-GO**. On NO-GO, fix the flagged item and rerun.

On GO: flash the real flix firmware, following
[flix's usage docs](../../build1-flix/flix/docs/usage.md), and fly indoors
with a spotter.

---

## If you get stuck

[troubleshooting.md](troubleshooting.md) covers the common failures. If your
symptom isn't there, the prompts in [`../prompts/`](../prompts/) are written
for exactly this — they give the AI our full hardware context so it doesn't
guess wrong about our pin numbers.
