# Glossary

Terms you'll hear in meetings, in plain language. Skim it once; come back
when someone says something confusing.

## The drone itself

**Quadcopter / quad** — a drone with four rotors. Ours are all quads.

**Frame** — the plastic skeleton holding everything together. Ours are
3D-printed from files in the flix repo.

**Microdrone** — the small, light, brushed-motor drone we build in Fall.
Light enough to fly indoors safely.

**FPV (First Person View)** — flying by watching a live video feed from a
camera on the drone, usually through goggles, instead of watching the drone
from the ground. Planned for later in the year.

## Electronics

**ESP32** — the small computer (microcontroller) that runs the drone. It reads
the sensors and decides how fast each motor spins, hundreds of times a second.

**IMU (Inertial Measurement Unit)** — the sensor that tells the drone which
way is up and how fast it's rotating. Ours is a GY-91 board. Contains:
- **Gyroscope / gyro** — measures rotation speed
- **Accelerometer / accel** — measures acceleration, including gravity, which
  is how the drone knows which way is down

**GPIO** — a numbered pin on the ESP32. "GPIO12" means physical pin 12. Which
part connects to which GPIO is fixed in our design — see [CLAUDE.md](../../CLAUDE.md).

**MOSFET** — an electronic switch. The ESP32 can't supply enough current to
drive a motor directly, so it tells a MOSFET to do it. One per motor.

**Pull-down resistor** — a resistor that holds a MOSFET's input at "off" when
nothing is driving it. Without it, motors can twitch on unpredictably at boot.

**ESC (Electronic Speed Controller)** — the brushless equivalent of our
MOSFETs. Used in the Winter build, not the Fall one.

**LiPo** — lithium polymer battery. See [safety.md](safety.md).

**Voltage divider** — two resistors that halve the battery voltage so the
ESP32 can safely measure it. The ESP32 can only read up to ~3.1V, and a full
battery is 4.2V.

## Software

**Firmware** — the program running on the drone itself, as opposed to
software on your laptop.

**flix** — the open-source firmware we use for the Fall build.
[github.com/okalachev/flix](https://github.com/okalachev/flix)

**ESP-FC** — the firmware for the Winter build. Compatible with Betaflight.

**Betaflight** — the standard configuration software for hobby drones. Used
in Winter, not Fall.

**Arduino IDE** — the program on your laptop that compiles code and uploads
it to the ESP32.

**Sketch** — Arduino's word for a program. Files end in `.ino`.

**Serial Monitor** — the window in Arduino IDE that shows text the drone
prints back to you. Set it to **115200 baud** or you'll see garbage.

**Flashing / uploading** — putting new firmware onto the drone.

## Flying and tuning

**Arming** — enabling the motors. A drone that isn't armed won't spin up no
matter what the throttle says. Deliberate safety step.

**Failsafe** — automatic behavior when something goes wrong, e.g. cutting
motors when the radio signal is lost.

**Throttle** — overall power to all four motors; controls climb and descent.

**Roll / pitch / yaw** — tilting side to side / tilting forward and back /
spinning flat like a turntable.

**PID loop** — the control math that keeps the drone level. Three numbers
(P, I, D) per axis that get tuned until the drone flies stably instead of
wobbling.

**Blackbox** — an in-flight log of sensor and motor data, used to diagnose
why a drone flew badly.

**Prop wash** — turbulent air from the props disturbing the drone; a common
cause of wobble when descending.
