# Retrospective: Week 1 — Toolchain + PV Calculator

**Date:** 2026-04-20
**Cycle covered:** 2026-04-18 → 2026-04-20 (Days 1–5)
**Participants:** User, Claude

---

## What we set out to do

Get a working C++ development environment on macOS and build a present-value calculator from first principles — deriving the formula, implementing it, debugging it in a live debugger, and having it pass a code review. The goal was not just a working artifact but the ability to explain every line: why `double` over `float`, why the guard is placed before the division, why `-Wall` matters.

## What actually happened

All five days completed, three calendar days. Environment was clean from Day 1 (all 9 setup checks green). The PV formula was derived unaided from opportunity-cost reasoning. Implementation produced `863.84` on first correct compile. Debugger was used live — uninitialised memory was observed in the Variables panel directly, not described from a slide. Code review caught one blocking issue (silent exit with no message on `r == -1`) and two non-blocking patterns worth knowing. Acceptance test on Day 5: 2/2 pass, zero warnings.

## What worked

- **Trace-based coaching on the discount loop.** Walking through `n=3` step by step — what the accumulator holds after each iteration — made the loop body obvious without handing over code. The off-by-one in the hand-written loop was caught during this trace, before it ever made it into source.
- **Live debugger session.** Seeing the Variables panel show garbage (`4.179…`) and then `863.84` after the assignment made the read/write distinction concrete in a way no diagram would have.
- **Struggle-first constraint.** No code was handed over before an attempt. Every concept that landed cleanly was retrieved, not received.

## What didn't work

- **Hints lacked context when scaffolding UB.** The undefined-behavior concept needed scaffolding (correct — it's subtle). But the hints were directional without enough surrounding context, so each hint felt like a nudge toward the right word rather than a richer mental model. Result: the mechanism was retrieved but felt thin. **Fix for Week 2:** when giving a hint, briefly state *why* the hint points that direction, not just what to think about next.

## Surprises

- Five days completed in three calendar days — the user runs multiple sessions per day. Pacing is faster than the nominal 1-session-per-day assumption. Spaced repetition intervals are built for calendar days, not session counts; they should hold.
- The `std::cerr` vs `std::cout` distinction (separate OS-level streams) was absorbed faster than expected — no confusion once the analogy to two separate pipes was used.

## Decisions to revisit

- No entries from DECISIONS.md are in doubt after Week 1. Plain `g++` invocations and `assert`-based testing remain the right call at this stage.

## What we'll change next cycle

1. **Hints come with context.** When scaffolding a retrieval attempt, include a brief "why this hint points here" alongside the nudge — not just the direction, but a fragment of the underlying model.

## Open follow-ups

- [ ] Re-test: PV derivation + guard placement intuition — scheduled 2026-04-21
- [ ] Re-test: undefined behavior mechanism — scheduled 2026-04-22 (flagged as needs-strengthening)
- [ ] Re-test: `-Wall` category — scheduled 2026-04-23
