# Retrospective: Week 6 — Classes + RAII; GBM Monte Carlo Option Pricer

**Date:** 2026-05-14
**Cycle covered:** 2026-05-11 → 2026-05-14 (Days 1–5)
**Participants:** User, Claude

---

## What we set out to do

Build a GBM path simulator and Monte Carlo European call pricer using C++ classes with proper RAII structure. Acceptance criterion: MC price converges to the W4 Black-Scholes closed form within 3×(stdev/√N) at N=100,000, with no raw `new`/`delete` in any class.

## What actually happened

All three classes (`NormalSampler`, `GBMSimulator`, `MCPricer`) were built across Days 1–2, reviewed and refactored on Day 4, and the acceptance test was run and passed on Day 5. The refactor promoted `_simulator` from a local variable to a member variable — the most important structural insight of the week. Day 5 extended `price_call()` to return `std::pair<double,double>` (mean and stdev of discounted payoffs) so the convergence band could be verified via assert. Final output: 10.4384 vs BS 10.4502, inside the [10.2802, 10.5609] band. Both acceptance criteria green.

## What worked

- Naming the exact mechanism of the local-vs-member RNG state issue early (Day 4) made the refactor obvious rather than arbitrary.
- The Python visual for SE and the 3-sigma band made an abstract formula concrete before writing the C++ acceptance test — user arrived at the C++ version with the right mental model already in place.
- Coaching on `std::pair` as "just a container for two values" before the user attempted the implementation prevented a detour into struct design.
- One-pass variance formula (`sum_sq/N - mean^2`) transferred cleanly from W3 context — no re-teaching needed.

## What didn't work

- `normal_sampler.cpp` and `gbm_simulator.cpp` each contain a standalone `main()` test driver — linking all three `.cpp` files into the final binary produced a duplicate-symbol linker error. No build system exists to separate test drivers from library code; this was worked around by compiling only `mc_pricer.cpp`. This will become a real problem in W15 when CMake is introduced.
- `(p - p) * (p - p)` as a first attempt at "p squared" — the confusion between "deviation from mean" and "square of the value" suggests the W3 one-pass variance formula wasn't fully internalized as a formula, only as a procedure.

## Surprises

- 44.2% of individual payoffs are exactly zero (option expires worthless) — seeing this in the Python output made the large payoff stdev (14.79) immediately intuitive. The skewness of the payoff distribution was visible, not just asserted.
- The `(p - p)` bug was surprising in a good way: it showed the user was thinking about variance as "deviation from something" (correct intuition) but hadn't yet anchored what that something is in the one-pass formula.

## Decisions to revisit

- Header-only class implementations (all method bodies in `.h` files) — works for a single-file build but will require restructuring when W15 introduces separate compilation and CMake test targets.

## What we'll change next cycle

1. W7 introduces `<fstream>` — establish from Day 1 that `.cpp` files containing `main()` are standalone programs, not library source; never link them together.
2. When a one-pass formula is introduced, write it on paper with a worked numeric example before coding it — the `(p-p)` error would not have happened with a 3-row trace on paper first.
3. Continue the pattern of Python visualization before C++ implementation for any statistical concept — it worked well this week.

## Open follow-ups

- [ ] Re-test 2026-05-17: MC convergence O(1/√N); BS inputs + directions; σ asymmetry one-sentence; range-for vs index loop.
- [ ] Re-test 2026-05-21: Three roles of `*`; `push_back` vs pre-initialized increment; member initializer list syntax; RNG state continuity.
- [ ] W7 Day 1: establish `.cpp` = standalone program convention before any file I/O work begins.
