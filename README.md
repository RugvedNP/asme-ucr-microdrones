# ASME @ UCR Microdrones

Code, firmware, and test scripts for the club's ESP32-based micro quadcopter
builds. If you're a member picking this up for the first time, start here.

## What's in this repo

| Path | What it is |
|---|---|
| [`CLAUDE.md`](CLAUDE.md) | The club's Claude Code master prompt — copy/paste sections from it to get AI help on wiring reviews, test sketches, PID tuning, blackbox analysis, etc. Read this first, it explains our exact hardware. |
| [`build1-flix/flix/`](build1-flix/flix) | The [flix](https://github.com/okalachev/flix) firmware itself, pulled in as a submodule (see [Getting the code](#getting-the-code) below). This is the real flight firmware for Build 1. |
| [`build1-flix/test-scripts/`](build1-flix/test-scripts) | Our own bench-test sketches — smoke test, tethered hover demo, pre-flight checklist. Run these **before** flying, in that order. See the [README in that folder](build1-flix/test-scripts/README.md) for details. |
| [`docs/SOURCES.md`](docs/SOURCES.md) | Line-by-line citations for the test scripts — what was reused from flix, what's a standard protocol implementation, what's original. |

Build 2 (ESP-FC / Betaflight platform, winter quarter) doesn't have anything
here yet.

## Safety first

- **Never spin motors with propellers attached unless you mean to fly.**
- Every test sketch prints clear PASS/FAIL/WARN/SKIP results to Serial —
  read them before doing anything else.
- The tethered hover demo is the first (and only) test script where props
  should be on. Tether or hand-restrain the drone for that one.
- If you're not sure a test script is safe for what you're about to do,
  ask an officer before running it.

## Getting the code

This repo uses a **git submodule** for the flix firmware, so a plain
`git clone` will leave `build1-flix/flix/` empty. Clone it like this:

```bash
git clone --recurse-submodules https://github.com/RugvedNP/asme-ucr-microdrones.git
```

Already cloned without `--recurse-submodules`? Run this from inside the repo:

```bash
git submodule update --init --recursive
```

## Setting up Arduino IDE

Needed for both the flix firmware and our test scripts in
`build1-flix/test-scripts/`:

1. Install [Arduino IDE](https://www.arduino.cc/en/software) (version 2 recommended).
2. Install **ESP32 core, version 3.3.10** via Boards Manager — see
   [Espressif's install guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide).
3. Install the **`FlixPeriph`** library via Library Manager — it's the IMU
   driver used by both the real firmware and our test scripts.
4. Select board **"WEMOS D1 MINI ESP32"** and the correct port.
5. Open Serial Monitor at **115200 baud** before running anything.

Full flix-specific setup details (flashing, ground control software,
simulator, etc.) are in [`build1-flix/flix/README.md`](build1-flix/flix/README.md)
and [`build1-flix/flix/docs/`](build1-flix/flix/docs).

## Typical first-build workflow

1. Solder up your drone following flix's [assembly docs](build1-flix/flix/docs/assembly.md)
   and the wiring in [Section 2 of `CLAUDE.md`](CLAUDE.md#2-wiring-review-paste-after-section-0).
2. **Props off.** Run [`build1-flix/test-scripts/smoke_test/`](build1-flix/test-scripts/smoke_test).
   Fix anything that doesn't PASS before moving on.
3. **Props on, tethered.** Run [`tethered_hover_demo/`](build1-flix/test-scripts/tethered_hover_demo).
4. **Props off again.** Run [`preflight_check/`](build1-flix/test-scripts/preflight_check)
   as your final go/no-go before flashing the real flix firmware and flying.
5. Flash flix itself and fly, following [`build1-flix/flix/docs/usage.md`](build1-flix/flix/docs/usage.md).

## Getting help

Stuck? Paste [`CLAUDE.md`](CLAUDE.md) Section 0 into Claude Code along with
whatever's going wrong (compile error, weird sensor reading, motor spinning
the wrong way) — it has the full hardware context and can usually get you
unstuck faster than digging through docs alone.

## Contributing

Save anything useful back to this repo so the next person doesn't have to
regenerate it — new test scripts go in `build1-flix/test-scripts/` (or a new
`build2-espfc/` folder once that track starts), reference material and
write-ups go in `docs/`.
