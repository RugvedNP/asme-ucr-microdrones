# Blackbox log analysis

**Winter build (ESP-FC) only.** Use when the drone flies but flies *badly* —
wobbling, twitchy, oscillating, or feeling sluggish.

Record a log with blackbox enabled, then export CSV from Betaflight Blackbox
Explorer.

---

```
I have a blackbox log from a test flight of our Build 2 ESP-FC drone. The flight was [DESCRIBE: e.g. "a 30-second indoor hover in angle mode, the drone oscillated on the roll axis and felt twitchy"].

Analyze this data and tell me:
1. Is there visible gyro noise? What frequency range?
2. Are the PID outputs saturating (hitting max values)?
3. Are motors hitting 100% or 0% during the flight? (indicates the PID loop is running out of authority)
4. Is there a visible oscillation pattern? What axis? What frequency?
5. What specific PID changes would you recommend? Give me exact numbers or slider adjustments.
6. Is the D-term noisy? Should I lower D or add filtering?
7. Any signs of motor desync, ESC issues, or electrical noise?

Log data (CSV from Betaflight Blackbox Explorer export):
[PASTE CSV DATA HERE — or give the .bbl file path if using Claude Code locally]
```

## Rule out mechanical problems first

Blackbox analysis will happily produce PID recommendations for a problem
that's actually a bent prop or a loose motor. Before tuning:

- Are all four motors tight? (flix's docs call this out as a top cause of
  instability)
- Any bent or chipped props? Swap them.
- Is the flight controller mounted with some vibration isolation, not rigid?

Tuning a mechanically bad drone just moves the wobble around.
