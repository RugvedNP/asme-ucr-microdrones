# Prompts

Ready-made prompts for getting AI help on this project. Each file is one
task. Open only the one you need — you don't read this folder front to back.

## How to use these

**If you're using Claude Code inside this repo:** just paste the prompt. The
hardware context (pin numbers, parts, safety rules) is in
[`../../CLAUDE.md`](../../CLAUDE.md), which Claude Code loads automatically.

**If you're using claude.ai, ChatGPT, or anything else:** paste
[`00-hardware-context.md`](00-hardware-context.md) **first**, then your task
prompt. Without it the AI will invent pin numbers and confidently give you
wrong answers.

Replace anything in `[BRACKETS]` with your real values before sending. These
work far better with actual pasted output — real Serial logs, real CLI dumps
— than with descriptions of what happened.

## The prompts

| File | Use when |
|---|---|
| [00-hardware-context.md](00-hardware-context.md) | Always first, outside Claude Code |
| [01-smoke-test.md](01-smoke-test.md) | Regenerating or modifying the smoke test |
| [02-wiring-review.md](02-wiring-review.md) | **Before first power-on** — catch wiring mistakes |
| [03-tethered-hover.md](03-tethered-hover.md) | Regenerating or modifying the hover demo |
| [04-betaflight-dump.md](04-betaflight-dump.md) | Winter build — reviewing your Betaflight config |
| [05-blackbox-analysis.md](05-blackbox-analysis.md) | Winter build — drone flies badly, diagnosing why |
| [06-simulator-setup.md](06-simulator-setup.md) | No hardware yet, want to practice |
| [07-frame-cad.md](07-frame-cad.md) | Modifying the 3D-printed frame |
| [08-preflight-check.md](08-preflight-check.md) | Regenerating or modifying the preflight script |
| [09-quick-questions.md](09-quick-questions.md) | One-off questions — dead motor, pin safety, etc. |

## Already generated — don't redo these

Prompts 01, 03, and 08 have **already been run**, and their output is
committed and working in
[`../../build1-flix/test-scripts/`](../../build1-flix/test-scripts).

Use those sketches. Only reach for the prompt if you're deliberately changing
behavior — different IMU, different throttle, extra check.

## When output isn't right

Say what's wrong and ask for a fix. "Motor 2 should be on GPIO14, not GPIO15
— fix the sketch" is a perfectly good follow-up. You don't have to start over.

## Always review before flashing

AI output is good, not infallible. Check pin assignments against your actual
wiring before uploading anything to hardware — especially anything that spins
a motor.
