# Tethered hover demo sketch

> **Already generated.** The working sketch is at
> [`../../build1-flix/test-scripts/tethered_hover_demo/`](../../build1-flix/test-scripts/tethered_hover_demo).
> Use this prompt only to regenerate or modify it.

First powered test. **Props on, drone tethered or hand-restrained.**

---

```
Generate an Arduino sketch called "tethered_hover_demo.ino" for our Build 1 flix hardware. This is for the club's first indoor tethered hover test. The drone will be held by a tether or hand-restrained. Props WILL be on.

Requirements:
- On boot, run a quick IMU health check (gyro + accel responding, values in range). If it fails, print "IMU FAILED — DO NOT FLY" and halt.
- Read battery voltage on GPIO32. If below 3.4V, print "BATTERY TOO LOW — DO NOT FLY" and halt.
- Wait for a Serial command "ARM" (typed by the tester) before doing anything with motors. Print "Type ARM to begin hover test. ENSURE TETHER IS ATTACHED."
- Once "ARM" is received:
  1. Ramp all 4 motors from 0% to 35% throttle over 2 seconds (gradual spin-up).
  2. Hold at 35% throttle for 4 seconds (near hover for a ~80g flix build).
  3. Ramp back down to 0% over 2 seconds.
  4. Print "Test complete. Motors disarmed."
- During the entire sequence, check IMU data at 100Hz. If the drone tilts beyond +/-45 degrees on any axis, immediately cut all motors and print "TILT SAFETY CUT — motors killed."
- If Serial receives "STOP" at any time, immediately cut all motors.
- After the test, print peak tilt angle observed and average battery voltage during the test.

IMPORTANT: the throttle ramps must NOT be implemented with blocking delay() calls, because the tilt and STOP checks have to keep running at 100Hz throughout. Structure the ramps as a non-blocking loop that updates throttle and checks safety on every iteration.

This is NOT a full flight controller — it's a simple open-loop throttle ramp with safety guards. The flix PID loop is NOT running here. The purpose is to verify that the hardware produces thrust and the safety systems work before handing off to the real flix firmware.
```

## Note on the non-blocking requirement

The original version of this prompt didn't include that "IMPORTANT" paragraph,
and the first generated sketch used `delay()` for the ramps — which meant the
tilt and STOP checks couldn't actually run during them. The committed sketch
fixes this. Keep that requirement in if you regenerate.
