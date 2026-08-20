# Preflight check sketch

> **Already generated.** The working sketch is at
> [`../../build1-flix/test-scripts/preflight_check/`](../../build1-flix/test-scripts/preflight_check).
> Use this prompt only to regenerate or modify it.

Final go/no-go before the first untethered flight. **Props off.**

---

```
Generate an Arduino sketch called "preflight_check.ino" for our Build 1 flix hardware. This is the final validation before we fly untethered for the first time. It should be a comprehensive go/no-go checklist that runs automatically.

Run these checks in sequence and print results:

1. IMU INIT — SPI communication with MPU-9250 successful? whoAmI register returns expected value?
2. IMU CALIBRATION — Collect 200 gyro samples while stationary. Is drift < 5 deg/s on all axes?
3. ACCELEROMETER — Is measured gravity between 0.9g and 1.1g? Is the drone sitting level (pitch/roll < 5 degrees)?
4. MOTOR RESPONSE — Briefly pulse each motor (50ms at 20%). Report SKIP with a note that visual/audible confirmation is needed, since we have no current sensing.
5. RADIO LINK — Is the receiver producing valid SBUS data on GPIO4? Are stick values in the expected range (1000-2000us)? Are channels responding?
6. BATTERY — Voltage in safe range? Above 3.6V for a full-charge flight?
7. FAILSAFE — Simulate radio loss. Do all motors reach zero within 100ms?
8. FREE MEMORY — Is there enough heap for stable operation? (ESP32 should have >50KB free)

Print a final summary:
"=== PRE-FLIGHT VALIDATION ==="
[Each check: PASS / FAIL / SKIP with one-line detail]
"OVERALL: [GO / NO-GO]"

If ANY critical check fails (IMU, calibration, accelerometer, battery, failsafe, memory), print "NO-GO — DO NOT FLY" in all caps. Non-critical checks (RC link when flying via USB gamepad, motor current sensing) should print SKIP, not FAIL, and must not force a NO-GO.
```

## Note on the SBUS decoder

No SBUS library was specified, so the generated sketch contains a
hand-written frame decoder (start byte `0x0F`, 25-byte frame, 11-bit channels
packed across 22 bytes). If you regenerate and want a library instead, say so
explicitly in the prompt.
