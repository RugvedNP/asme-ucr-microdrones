# Team structure and roles

Planning doc for officers.

## Why this exists

Highlander Combat Robotics — our sibling project — runs on named subdivisions
(Drivetrain, Weapon Systems, Electrical Integration, Chassis Design), weekly
sub-team meetings, and a rule that new members are trained by veterans before
they touch major design tasks. That structure is why HCR can absorb beginners
without drowning.

The Drone Project has had no written equivalent. This is a first draft of
one, scaled to our size.

> **TODO:** assign names to each role before the quarter starts.

## The base unit: pairs

Every member is in a **pair**, and every pair owns **one drone** end to end.
Both people work on every part of it — this is a teaching project, not a
production line, so we don't split "you do electronics, I do frames" within
a pair.

Pairing rules that have to hold:
- Pair a returning member with a new one wherever numbers allow.
- Both partners' names go on the drone. Shared ownership, shared blame.
- If a pair loses a member, merge them into another pair rather than letting
  someone work alone.

## Roles above the pairs

Small enough team that these are individual people, not sub-teams:

| Role | Owns | Roughly |
|---|---|---|
| **Project Lead** | Overall schedule, gate sign-offs, sponsor-facing updates | 1 person |
| **Safety Officer** | Battery handling, prop discipline, incident follow-up, the week-1 briefing | 1 person |
| **Build Mentor** | Soldering quality, wiring reviews, unblocking stuck pairs | 1–2 people |
| **Firmware Lead** | Arduino toolchain, flashing, test scripts, this repo | 1 person |
| **Parts & Inventory** | Bin stock, orders, what's broken, what needs reordering | 1 person |

The **Safety Officer is not optional and not ceremonial.** They hold the
authority to stop a session. Put an actual name on it.

## As the project grows

If the project outgrows one-person roles, split along the same lines HCR
uses — by subsystem, each with a lead and a weekly check-in:

- **Airframe** — frames, printing, mounting, weight
- **Electronics** — wiring, power, soldering standards
- **Firmware & Tuning** — flashing, configuration, PID tuning, logs
- **Flight Operations** — safety, test protocol, pilot training, competition prep

## Knowledge transfer

The part that's easy to skip and expensive to lose. HCR's model — veterans
train newcomers before newcomers touch real tasks — only works if the
training is a scheduled thing, not an accident.

Concretely:
- Every workshop gets **two** instructors: one experienced, one learning to
  teach. The second one is next year's instructor.
- Anything a pair figures out the hard way goes into
  [`../members/troubleshooting.md`](../members/troubleshooting.md). If it
  cost someone two hours, it goes in the doc.
- Working test sketches get committed to
  [`../../build1-flix/test-scripts/`](../../build1-flix/test-scripts) so the
  next person doesn't regenerate them.
- **End of year: name your successor and hand off in person.** A repo does
  not replace this.
