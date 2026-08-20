# Wiring review

**Run this before you first apply power.** Reversed leads kill an ESP32
instantly, and this prompt catches the mistakes that are cheap to fix now and
expensive to fix later.

Replace the wiring block with what you *actually* built, not what you meant
to build.

---

```
I'm about to power on my Build 1 flix drone for the first time. Review my wiring for safety issues, shorts, and mismatches against the official flix schematics (https://github.com/okalachev/flix/blob/master/docs/wiring.md).

My actual wiring:
[PASTE YOUR WIRING HERE — example format below]

ESP32 VCC <- Battery + (through switch)
ESP32 GND <- Battery -
GPIO18 -> GY-91 SCL
GPIO23 -> GY-91 SDA
GPIO19 -> GY-91 SAO
GPIO5  -> GY-91 NCS
GY-91 3.3V <- ESP32 3.3V
GY-91 GND <- ESP32 GND
GPIO12 -> MOSFET gate (Motor 0, rear left)
GPIO13 -> MOSFET gate (Motor 1, rear right)
GPIO14 -> MOSFET gate (Motor 2, front right)
GPIO15 -> MOSFET gate (Motor 3, front left)
Each MOSFET: drain -> motor -, source -> GND, 10k between gate and source
Each motor: + -> battery VCC (through common bus)
GPIO4 <- RC receiver signal (SBUS)

Check for:
1. Any pins that conflict with ESP32 boot strapping pins (GPIO0, GPIO2, GPIO12, GPIO15 have boot-mode implications — is my motor assignment safe?)
2. Missing pull-down resistors on any MOSFET gate
3. Missing flyback/snubber protection on brushed motors (does flix's design handle this, or do I need diodes?)
4. Correct voltage levels (3.3V logic driving the MOSFET gates — is 3.3V enough for the 100N03A threshold voltage?)
5. Any risk of back-feeding voltage into the ESP32
6. Whether my SBUS receiver wiring needs an inverter (ESP32 supports software inversion — confirm)
```

## Also get a human to look

The AI catches design-level problems. It cannot see your cold solder joint or
the strand of wire bridging two pads. Have an officer or experienced member
physically inspect the board too — see
[../members/build-guide.md](../members/build-guide.md), Stage 4.
