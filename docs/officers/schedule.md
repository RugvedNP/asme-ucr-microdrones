# Quarter plan and meeting cadence

Planning doc for whoever is running the Drone Project. Members don't need to
read this.

> **TODO before the quarter starts:** fill in actual dates, meeting room, and
> meeting times. Everything below is structure, not a committed calendar.

## Cadence

Per the 2026–2027 sponsorship packet, the project runs **2–3 meetings per
week**, with members working in **pairs**, one drone per pair.

A workable split of that:

| Session | Purpose | Who runs it |
|---|---|---|
| **Build session** (2h) | Pairs work on their drone. Officers float and unblock. | Project lead + 1–2 experienced members |
| **Workshop** (1h) | One skill, taught to everyone: soldering, CAD, Arduino, flight theory | Rotating |
| **Open lab** (optional) | Catch-up time for pairs who fell behind | Any officer present |

The open lab matters more than it sounds. Pairs fall behind for ordinary
reasons — a midterm, a dead part — and without a catch-up slot they quietly
drop out.

## Fall quarter — microdrone build

Ten weeks, mapped to [the member build guide](../members/build-guide.md).

| Week | Focus | Gate |
|---|---|---|
| 1 | Intro, safety briefing, pair assignments, laptop setup | Arduino `Blink` uploads |
| 2 | Soldering workshop; frame printing starts | Everyone has soldered *something* |
| 3 | Frame prep, dry fit, motors mounted | Motors tight, nothing glued yet |
| 4 | Solder MOSFETs and motor leads | — |
| 5 | ESP32 wiring, IMU mounting | — |
| 6 | **Wiring review**, first power-on | Wiring signed off by an officer |
| 7 | **Smoke test** (props off) | All PASS |
| 8 | **Tethered hover** (props on, tethered) | Thrust confirmed, safety cuts work |
| 9 | **Preflight check**, flash flix firmware | GO verdict |
| 10 | First flights, indoor | Every pair has flown |

Two things to protect: the **week 6 wiring review** (skipping it is how
ESP32s die) and the **week 1 safety briefing** (do it before anyone touches
a soldering iron, not "when we get to it").

## Winter quarter — brushless / ESP-FC

Moving up to brushless motors, DShot ESCs, and Betaflight-compatible
firmware. Faster, less forgiving, and the platform we'd actually compete on.

Rough shape — **TODO: expand once Fall completes and we know the survival rate**:

- Weeks 1–3: brushless theory, ESC and receiver differences, parts arrive
- Weeks 4–6: build
- Weeks 7–8: Betaflight configuration and first tuning
  ([prompt](../prompts/04-betaflight-dump.md))
- Weeks 9–10: blackbox-driven tuning
  ([prompt](../prompts/05-blackbox-analysis.md)), pilot practice

## Spring quarter — flying and competing

Per the packet: obstacle courses, practice competitions, and competing
against other schools. See [competitions.md](competitions.md).

## Members without hardware

Anyone waiting on parts, or joining mid-quarter, can start in the flix
Gazebo simulator instead of stalling — see
[`../prompts/06-simulator-setup.md`](../prompts/06-simulator-setup.md). Worth
offering proactively; a member with nothing to do for two weeks usually
doesn't come back.

## Recurring officer tasks

- **Before each build session:** charge packs, check the parts bin, confirm
  no swollen batteries
- **After each session:** note which pairs hit their gate and which didn't
- **Weekly:** follow up with pairs who missed a gate, before they're two
  weeks behind
- **End of quarter:** photos and results for the sponsorship packet — sponsor
  recognition in "team presentations and project documentation" is a
  benefit we've promised, so it needs material
