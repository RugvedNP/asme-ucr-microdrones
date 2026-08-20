# ASME @ UCR Microdrones

Building and flying ESP32-based micro quadcopters. Part of ASME at the
University of California, Riverside.

Most members here are beginners — that's the point. You don't need prior
experience with electronics, CAD, or code.

## Where do I go?

**I'm a new member.**
→ [docs/members/START-HERE.md](docs/members/START-HERE.md) — five-minute read,
start there and nowhere else.

**I'm building a drone right now.**
→ [Build guide](docs/members/build-guide.md) ·
[Testing](docs/members/testing.md) ·
[Troubleshooting](docs/members/troubleshooting.md) ·
[Glossary](docs/members/glossary.md)

**Something is on fire / I need the safety rules.**
→ [docs/members/safety.md](docs/members/safety.md)

**I'm running the project.**
→ [Quarter plan](docs/officers/schedule.md) ·
[Roles](docs/officers/roles.md) ·
[Parts & budget](docs/officers/parts-list.md) ·
[Competitions](docs/officers/competitions.md)

**I want AI help with a specific task.**
→ [docs/prompts/](docs/prompts/) — one file per task, use only the one you need.

## The one rule

**Propellers come off before you test anything.** The only exception is the
tethered hover demo, and that requires the drone to be restrained. Every test
script states which it expects. Full rules in
[safety.md](docs/members/safety.md).

## Getting the code

This repo uses a git submodule for the flix firmware, so a plain clone leaves
`build1-flix/flix/` empty:

```bash
git clone --recurse-submodules https://github.com/RugvedNP/asme-ucr-microdrones.git
```

Already cloned without it? From inside the repo:

```bash
git submodule update --init --recursive
```

## What's in here

```
docs/members/       guides for students building a drone
docs/officers/      planning docs for whoever runs the project
docs/prompts/       paste-into-chat prompts, one per task
docs/SOURCES.md     where the test-script code came from
build1-flix/flix/         upstream flix firmware (submodule)
build1-flix/test-scripts/ our bench-test sketches
CLAUDE.md           hardware context, auto-loaded by Claude Code
```

Build 2 (the Winter brushless / ESP-FC track) hasn't started yet.

## Contributing

Save useful things back here so the next person doesn't redo them — working
sketches in `build1-flix/test-scripts/`, anything you learned the hard way in
[troubleshooting.md](docs/members/troubleshooting.md), modified frames
alongside the build they're for.

## Contact

ASME @ UCR — Ezekiel Brown, President — ebrow077@ucr.edu
