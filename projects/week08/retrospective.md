# Retrospective: Week 8 — Monte Carlo VaR on Real Historical Data

**Date:** 2026-05-25
**Cycle covered:** 2026-05-22 → 2026-05-25 (Days 1–5)
**Participants:** Aryaman, Claude

---

## What we set out to do

Build a Monte Carlo VaR model on real historical data — the Week 8 / Milestone 2 target from CONTEXT.md. Three VaR methods (historical simulation, parametric, Monte Carlo) computed at 95% and 99% confidence on calibrated SPY log returns, tested against an out-of-sample window with empirical exceedance frequencies reported and sanity-checked.

## What actually happened

All three methods were derived from first principles on Day 1, implemented across a five-file architecture (csv_loader.h/cpp, normal_sampler.h, var_model.h, var_model.cpp) on Day 2, and code-reviewed on Day 3 — fixing a missing file-open guard and signed/unsigned index arithmetic. Day 4 added `exceedance_frequency()` and wired the calibration/out-of-sample split using iterator arithmetic. Day 5 added nine assert-based acceptance checks (magnitude ordering + exceedance bounds) which all passed silently. Final output: historical 4.6%/1.2%, parametric 6.2%/1.2%, MC 6.2%/1.2%. Milestone 2 closed.

## What worked

- Getting fuller explanations before and after retrieval attempts — having context around why an answer matters helped the correction land rather than just sound like a correction.
- Iterating on retrieval answers within the session rather than moving on after a partial score — the historical exceedance mechanism went from 0/2 to a clean one-sentence answer by the end of today's opening retrieval.
- The code-review day (D3) as a dedicated session — catching the file-open guard and index arithmetic before the model ran on real data avoided silent wrong answers.

## What didn't work

- Spaced retrieval without notes is becoming harder as the concept count grows — retrievals are relying more on reconstruction than recall, which is slower and error-prone under session pressure.
- Concepts that score poorly across multiple sessions (historical VaR exceedance mechanism, σ asymmetry precision) are not getting dedicated consolidation time — they keep appearing as carry-forwards without a focused session to close them.

## Surprises

- None logged.

## Decisions to revisit

- Out-of-sample split at 70%/30% (350/150 returns) — no formal justification was given; worth revisiting when W13 covers variance reduction to check whether this ratio affects exceedance stability.

## What we'll change next cycle

1. Schedule one dedicated concept-review session before W9 progresses past Day 2 — focus specifically on retrievals that have scored below 1.5/2 across three or more attempts.
2. Spend more time in the conceptual phase before moving to code — talk through the design with the coach verbally before typing, not after.
3. Sharpen retrieval answers toward the precise form on the first attempt — not just "right direction" but the complete mechanism in one sentence.

## Open follow-ups

- [ ] Add to TASKS.md: dedicated concept-review session (σ asymmetry, historical VaR exceedance mechanism, parametric thin-tail mechanism) before W9 Day 3.
- [ ] Improve BADROW error message in csv_loader.cpp to include file path and row number — deferred from W8 as out of scope.
