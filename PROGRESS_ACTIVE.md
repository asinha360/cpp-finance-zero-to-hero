# PROGRESS_ACTIVE.md — Current Session State
<!-- Cap: ≤40 lines. Overflow → PROGRESS_HISTORY.md. Updated by /end each session. -->

## Current state

- **Today's date:** 2026-06-01
- **Curriculum week:** 9 of 16 — Day 1 complete, Day 2 pending
- **Days into curriculum:** 19 (calendar) / 35 sessions complete
- **Schedule status:** On track
- **Next milestone:** Week 12 — Order-book replay backtester
- **Today's artifact:** [notes/w9_d1.md](notes/w9_d1.md)

## Next session

**First action:** Open `ohlc_bar.cpp`, write `struct OHLCBar` and `std::map<int, OHLCBar> bars;` from memory, then attempt the full per-tick update block solo — no Claude code until a first attempt is on the page.
**Retrieval question:** Without notes, write the per-tick update block: what does `.find()` return, what condition tests "first tick," and what three things update in the else branch?
**Carry-forwards:** historical VaR exceedance mechanism (1/2 — needs one unaided pass); σ asymmetry (untested, due W9D3); `std::map` Big O terminology (O(log n) vs O(1) conflated in closing check)

## Open retrieval gaps

| Topic | Score | Re-test |
|-------|-------|---------|
| `std::map` ordering / Big O terminology | 1/2 | 2026-06-02 |

## Milestones

- [x] Week 4 — Black-Scholes pricer from scratch
- [x] Week 7 — CSV loader with File I/O
- [x] Week 8 — Monte Carlo VaR on real data
- [ ] Week 12 — Order-book replay backtester
- [ ] Week 16 — 3 portfolio projects on GitHub
