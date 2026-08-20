# Betaflight config review

**Winter build (ESP-FC) only.** Run this after configuring in Betaflight
Configurator, before your first brushless flight.

Get the dump by opening the **CLI** tab in Betaflight Configurator and typing
`dump`.

---

```
I just configured my Build 2 ESP-FC drone in Betaflight Configurator. Here is my CLI dump. Review it for misconfigurations, safety issues, and anything that doesn't match a micro brushless quad setup.

My hardware:
- ESP32-S3 dev board running ESP-FC firmware
- IMU: [YOUR IMU MODEL, e.g. ICM20602 on SPI]
- Motors: 4x [YOUR MOTOR MODEL, e.g. 1103 8000KV] on DShot300
- ESC: [YOUR ESC, e.g. generic 4-in-1 12A BLHeli_S]
- Receiver: [YOUR RECEIVER, e.g. Happymodel EP1 ELRS 2.4GHz] on [UART NUMBER]
- Battery: [YOUR BATTERY, e.g. 1S 450mAh 75C]
- Frame: [YOUR FRAME, e.g. 2.5" toothpick]
- AUX channels: AUX1 = arm switch, AUX2 = angle/acro toggle

CLI dump:
[PASTE YOUR FULL CLI DUMP HERE]

Check for:
1. Motor protocol matches my ESCs (is DShot300 correct for BLHeli_S?)
2. Receiver protocol matches my receiver (CRSF on the correct UART?)
3. PID values reasonable for a micro quad, not too aggressive for a first flight
4. Failsafe set to DROP (cut motors), not LAND (which needs GPS we don't have)
5. Arming on the correct AUX range
6. Angle mode available for beginners
7. Motor idle percentage safe (too low = desync, too high = flips on arm)
8. Any ESP-FC-specific settings that differ from stock Betaflight and might cause issues
9. Pin mapping matches my actual wiring
10. Anything else that looks wrong or could cause a crash on first flight
```

## Two things to check yourself regardless

- **Failsafe must be DROP, not LAND.** We have no GPS. A LAND failsafe on a
  GPS-less quad does not do what the name suggests.
- **Angle mode should be on AUX2** for anyone who hasn't flown acro before.
  Beginners in acro mode crash immediately.
