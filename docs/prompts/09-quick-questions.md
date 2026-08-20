# Quick questions

One-liners for specific problems. Paste and fill in the brackets.

Outside Claude Code, paste
[`00-hardware-context.md`](00-hardware-context.md) first.

---

## Is this pin safe for a motor?

```
Is GPIO[NUMBER] safe to use as a motor PWM output on ESP32? Any boot-mode conflicts?
```

## A motor won't spin

```
Motor on GPIO[XX] won't spin. MOSFET is 100N03A, pull-down is 10k. ESP32 3.3V logic. What should I check with a multimeter? Give me a step-by-step debug sequence.
```

## Scale PID values for a smaller quad

```
Convert these Betaflight PID values from a 5-inch quad to something reasonable for a 2.5-inch micro: P[XX] I[XX] D[XX] on roll/pitch. Explain the scaling logic.
```

## Battery voltage reader

```
Write a simple Arduino function for ESP32 that reads battery voltage on GPIO32 through a voltage divider (two 10k resistors), converts to real voltage, and returns it as a float. Include ADC calibration notes for ESP32.
```

## Will flix run on a different ESP32?

```
Will the flix firmware (github.com/okalachev/flix) compile for ESP32-C3 without modifications? What changes are needed?
```

## Decode an error I don't understand

```
I got this error building/running our Build 1 flix drone. Explain what it means in beginner terms, then tell me how to fix it:

[PASTE THE FULL ERROR OR SERIAL OUTPUT]
```

---

## Getting better answers

**Paste actual output.** "The IMU failed" gets a guess. Pasting the ten lines
Serial printed gets a diagnosis.

**Say what you already tried.** Otherwise you'll get told to check the wiring
you already checked three times.

**Say you're a beginner** if you are. You'll get an explanation instead of a
one-word answer.
