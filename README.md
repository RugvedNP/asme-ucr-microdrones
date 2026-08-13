# ASME @ UCR Microdrones

Build, test, and fly ESP32-based micro quadcopters. This repo holds the
club's Claude Code workflows, bench-test firmware, and (once cloned) the
actual flight firmware for both build tracks.

New to the club or this repo? Start here, in order:

1. Read the **Safety first** section below before touching any hardware.
2. Skim **Repo structure** so you know where things live.
3. Follow **Quick start** to get the code on your machine.
4. Open [`CLAUDE.md`](CLAUDE.md) and paste Section 0 into Claude Code before
   asking it anything about our hardware — it gives Claude the pin numbers,
   parts, and safety rules so it doesn't guess wrong.

## Safety first

- **Never spin motors with propellers attached unless you mean to fly.**
  `smoke_test.ino` and `preflight_check.ino` are bench tests — props off.
- **`tethered_hover_demo.ino` is the only sketch meant to run with props on**,
  and only with the drone tethered or hand-restrained.
- Every generated test sketch prints clear PASS/FAIL/WARN/SKIP results to
  Serial at 115200 baud — read them before proceeding to the next step.
- If a sketch tells you NO-GO, don't fly. Fix the flagged issue and rerun.

## Repo structure

```
asme-ucr-microdrones/
├── README.md              <- you are here
├── CLAUDE.md               Master prompt: paste into Claude Code for hardware context
├── docs/
│   └── SOURCES.md          Where every line of generated code came from
└── build1-flix/            Fall quarter build (flix platform)
    ├── flix/                Upstream firmware (git submodule, github.com/okalachev/flix)
    └── test-scripts/        Our bench-test sketches, see its own README
        ├── smoke_test/
        ├── tethered_hover_demo/
        └── preflight_check/
```

Build 2 (ESP-FC / winter quarter) will get its own `build2-espfc/` folder
the same way once that work starts.

## Quick start

Clone with submodules so the `flix` firmware comes down too — a plain
`git clone` leaves that folder empty:

```bash
git clone --recurse-submodules https://github.com/RugvedNP/asme-ucr-microdrones.git
```

Already cloned without `--recurse-submodules`? Fetch it after the fact:

```bash
git submodule update --init --recursive
```

To run a bench test sketch: open `build1-flix/test-scripts/<name>/<name>.ino`
in Arduino IDE (see that folder's [README](build1-flix/test-scripts/README.md)
for the exact board/library setup), flash it, and watch the Serial Monitor
at 115200 baud.

## Using Claude Code on this project

[`CLAUDE.md`](CLAUDE.md) is a library of ready-to-paste prompts for common
tasks — smoke testing, wiring review, Betaflight config review, blackbox log
analysis, and more. Paste Section 0 (project context) first in any new
Claude Code session, then paste whichever numbered section matches what
you're doing.

Generated code should always be sanity-checked by a human against the real
wiring before it touches hardware — Claude Code is very capable but not
infallible, especially on pin assignments.

## Attribution

Test sketches in `build1-flix/test-scripts/` reuse real config and driver
patterns from the upstream `flix` firmware rather than reinventing them.
See [`docs/SOURCES.md`](docs/SOURCES.md) for exactly what came from where.

## Officer notes

- Save every working Claude Code output to this repo — don't let good
  sketches live only in someone's chat history.
- If a generated sketch needs a fix, just tell Claude Code what's wrong
  ("Motor 2 should be on GPIO14, not GPIO15") rather than regenerating
  from scratch.
- Keep [`docs/SOURCES.md`](docs/SOURCES.md) updated whenever new firmware
  is generated from the flix or esp-fc repos.
