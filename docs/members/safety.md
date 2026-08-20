# Safety

Read this before your first build session. It's short because the rules that
matter are few.

## Propellers

**Props off for every bench test.** The only exception in this whole repo is
the tethered hover demo, and that one requires the drone to be tethered or
hand-restrained.

Our test scripts state this in their header comments. If a script doesn't
say props can be on, they can't.

- Wear eye protection when props are on.
- Never hold the drone by the arms with props spinning — hold the body.
- Keep hair, sleeves, and cables clear.

## Batteries (LiPo)

We use single-cell 3.7V LiPo packs. They're small, but LiPo chemistry is
genuinely unforgiving:

- **Never charge unattended.** Charge on a hard, non-flammable surface, not
  on your bed or a stack of paper.
- **Never puncture, crush, or bend a pack.** A crashed drone's battery needs
  inspecting before it goes back on the charger.
- **Stop using a puffed pack.** Swelling means it's done. Hand it to an
  officer for disposal — it does not go in a normal trash can.
- **Don't over-discharge.** Below ~3.0V a 1S pack starts taking permanent
  damage. Our preflight script flags this before you fly.
- **Unplug the battery when you're not actively testing.** Not just "throttle
  at zero" — physically disconnected.

## Soldering

- Ventilate. Flux fumes are an irritant.
- The iron tip is ~350°C and looks identical hot or cold. Assume hot.
- Eye protection — solder can spit.
- Never solder with the battery connected.

## Wiring and power

- **Check polarity twice before first power-on.** Reversed battery leads kill
  an ESP32 instantly and can vent a LiPo.
- Have someone else look over your wiring before you first apply power. There
  is a prompt for exactly this in
  [../prompts/02-wiring-review.md](../prompts/02-wiring-review.md).
- Short circuits on a LiPo produce a lot of current very fast. If something
  smells hot or smokes, disconnect the battery first, diagnose second.

## Flying

- Indoors only until you've passed the preflight check.
- Clear the area. People, not just objects.
- Know how to cut motors before you arm them — for our test scripts that's
  typing `STOP` in Serial Monitor.
- If a script prints **NO-GO**, don't fly. Fix what it flagged and rerun.

## If something goes wrong

1. Disconnect the battery.
2. Tell whoever's running the session.
3. Don't quietly put a damaged part back in the bin — flag it.

Nobody is in trouble for breaking a part. People are in trouble for hiding a
damaged battery that then catches fire in a drawer.
