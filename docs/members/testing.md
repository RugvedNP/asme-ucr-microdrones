# Testing your drone

Three test scripts, run in this order. Each one is a gate — don't move to the
next until the current one passes.

They live in
[`build1-flix/test-scripts/`](../../build1-flix/test-scripts). Open the
folder matching the script name in Arduino IDE, upload, and watch Serial
Monitor at **115200 baud**.

| # | Script | Props | When |
|---|---|---|---|
| 1 | `smoke_test` | **OFF** | Right after soldering |
| 2 | `tethered_hover_demo` | **ON, tethered** | After smoke test fully passes |
| 3 | `preflight_check` | **OFF** | Final gate before untethered flight |

---

## 1. Smoke test

Confirms the drone is electrically alive and correctly assembled.

**What it does:** reads the IMU 10 times, spins each motor for 1.5s one at a
time, reads battery voltage, then verifies motors stop when a simulated radio
loss fires.

**What to watch for:** the Serial output names each motor and its GPIO pin as
it spins. Physically confirm the *named* motor is the one moving. Crossed
signal wires are the single most common build error and this is where you
catch them.

**Reading the results:**

```
=== SMOKE TEST RESULTS ===
IMU:      PASS
MOTORS:   PASS — visual confirmation needed
BATTERY:  PASS (3.92V)
FAILSAFE: PASS
```

- `IMU: FAIL` → SPI wiring or a dead sensor. See [troubleshooting.md](troubleshooting.md).
- `MOTORS` always says "visual confirmation needed" — the script cannot tell
  which way a motor spun. That judgment is yours.
- `BATTERY: WARN` → 3.0–3.3V, usable but low. Charge before flying.
- `BATTERY: FAIL` → below 3.0V or above 4.3V. Either a dead cell or your
  voltage divider is wrong.
- `FAILSAFE: FAIL` → do not proceed. This is the system that stops the drone
  when things go wrong.

---

## 2. Tethered hover demo

The first time your drone makes real thrust. **Props on. Tethered or
hand-restrained. Eye protection.**

**What it does:** waits for you to type `ARM`, then ramps all four motors
0% → 35% over 2 seconds, holds 4 seconds, ramps back down.

**Your safety controls:**
- Type `STOP` at any moment to cut motors.
- The script cuts motors itself if the drone tilts past 45° on any axis.

**Important:** this is *not* the real flight controller. There's no PID loop
holding it level — it's an open-loop throttle ramp. The drone will not
self-stabilize. That's expected; you're testing thrust and safety cutoffs,
not flight.

At the end it reports peak tilt and average battery voltage during the run.
A large voltage sag under load means your pack is tired or undersized.

---

## 3. Preflight check

The go/no-go gate. Props off.

**What it checks:** IMU communication and identity, gyro drift over 200
stationary samples, whether the drone is reading level and 1g, a brief motor
pulse, RC link (if you have a receiver), battery, failsafe timing, and free
memory.

**Reading the results:**

```
=== PRE-FLIGHT VALIDATION ===
OVERALL: GO
```

- **SKIP is not a failure.** Motor response skips because we have no current
  sensor. RC link skips if you're flying with a gamepad instead of a
  receiver. Both are normal.
- Any **FAIL** on IMU, battery, failsafe, level, or memory forces **NO-GO**.
- `NO-GO — DO NOT FLY` means exactly that. Fix and rerun.

Keep the drone still on a flat surface during the gyro drift check, or it
will fail for the wrong reason.

---

## When results don't make sense

Bring the actual Serial output with you when you ask for help — "the IMU
failed" is much harder to diagnose than the pasted lines showing what it
printed. The same goes for asking the AI: the prompts in
[`../prompts/`](../prompts/) work far better with real output pasted in.
