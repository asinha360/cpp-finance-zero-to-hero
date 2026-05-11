# TASKS.md

Living task board. Move items between sections as they progress. See [WORKFLOW.md](WORKFLOW.md) for the lifecycle.

---

## Now (actively working)

_Nothing. Week 5 complete. Ready for W6 Day 1._

## Next (queued, ordered)

- **W6 Day 1 (2h)** — Classes + RAII concept intro. GBM path simulator motivation. Jensen's inequality (why σ²/2 in d1) — deferred from W4. Re-test due 2026-05-12: stack vs heap + vector internals; memory leak + RAII motivation.
- **Re-test 2026-05-14** — `push_back` vs pre-initialized increment.
- **Re-test 2026-05-15** — Three roles of `*`; T& vs T* distinctions; PV re-derive.
- **Re-test 2026-05-17** — BS inputs + directions (5/5); σ asymmetry one-sentence; range-for vs index loop.

## Done

- **2026-05-11 — W5 Day 5: Acceptance test passed + retrospective written.** Both criteria green: mean 0.00179 ∈ [-0.005, 0.005], stdev 0.99992 ∈ [0.995, 1.005], seed 123 byte-for-byte. Retrospective at [projects/week05/retrospective.md](projects/week05/retrospective.md). Carry-forward retrievals cleared: σ asymmetry one-sentence clean (full mechanism unaided); `push_back` vs `counts[bin_index]++` distinction articulated correctly. **Week 5 complete.**

- **2026-05-10 — W5 Day 4: Code review complete.** Blocking issue resolved: silent `return 0.0` sentinel in `mean` and `sample_variance` replaced with `assert` (same anti-pattern as W4's `return 1`). Suggestions applied: range-for with `const double&` replacing `(int)` cast loops; `setprecision(5)`; `>= 2` in assert; `static_cast<double>` in both divisions. Histogram built from scratch: binning, clamping, counting, aligned print loop. Bell-curve shape confirmed. BS inputs retrieval: 5/5 directions unaided; σ asymmetry (downside floor argument) stated without prompting [FIRST TIME]. Range-for vs index loop distinction retrieved correctly unaided.

- **2026-05-08 — W5 Day 3: Closed-book retrieval complete.** (a) PV calculator re-implemented from scratch — formula recalled; `std::setprecision` bug self-diagnosed after one hint; `assert(r > -1)` tightened from `!= -1` after coaching. (b) Three roles of `*` recalled unaided [FIRST TIME all three clean]. (c) T& vs T* distinctions correct unaided; "static memory" framing corrected to stack/heap. New concept landed: stack vs heap — labels were initially swapped, corrected; vector internals (control block on stack, data on heap) understood correctly [FIRST TIME]; memory leak mechanism and RAII motivation clear — W6 foundation set.

- **2026-05-07 — W5 Day 2: RNG harness implemented and acceptance criteria green.** [projects/week05/rng_harness.cpp](projects/week05/rng_harness.cpp) compiles clean under `-Wall -Wextra -std=c++20`. Both W5 criteria pass: mean 0.00 ∈ [-0.005, 0.005], stdev 1.00 ∈ [0.995, 1.005], seed 123 reproduces byte-for-byte. Key fixes: `dist(engine)` not `dist(sample)` (type error); hardcoded seed for reproducibility; `#include <vector>` added; `.empty()` guard replacing `(int)size <= 0`; unsigned cast removed from variance guard. W4 spaced retrieval (BS inputs + directions): 5/5; r direction correct unaided [FIRST TIME].

- **2026-05-07 — W5 Day 1: Memory model + RNG concept intro complete.** Pointers (`&`, `*`, address arithmetic, aliasing), references (bind-once, no null), `const&` (no copy + read-only promise), `*` operator three roles, pointer vs reference table, function parameter patterns table. RNG: engine/distribution separation, seeding purpose reasoned from first principles [FIRST TIME unaided]. W2 spaced retrieval (const-ref vs by-value) retrieved unaided [FIRST TIME — prior session needed scaffolding]. Homework: attempt `projects/week05/rng_harness.cpp` skeleton solo before Day 2.

- **2026-05-06 — W4 Day 5: Retrospective complete. Milestone 1 closed.** Bessel's correction retrieved correctly (minimizer property named after one hint; n=1 degrees-of-freedom reasoning unaided). Retrospective at [projects/week04/retrospective.md](projects/week04/retrospective.md). Three process changes for W5 logged. Week 4 ledger updated; milestone checkbox ticked.

- **2026-05-06 — W4 Day 4: Code review complete.** All three open items resolved: (1) silent `return 1` anti-pattern replaced with `assert(sigma > 0 && T > 0)` in `compute_d1` — assert placed at the foundational function so all callers are protected automatically; (2) d1 duplication across 4 functions eliminated by extracting `compute_d1` and `compute_d2` helpers; `compute_d2` signature changed to accept d1 as parameter, eliminating double-computation; (3) parity test extended from 1 to 20 varied input sets (ITM, OTM, ATM, varied T 1–20, varied sigma 0.1–0.9) — all 20 asserts pass at 1e-10. Both W4 acceptance criteria now green. Retrieval: PV derivation clean (unaided derivation path: FV=PV·(1+r)^n → PV=FV/(1+r)^n); accumulation factor terminology sharpened.

- **2026-05-06 — W4 Day 3: Closed-book retrieval complete.** (a) d1 recalled exactly unaided; d2 recalled exactly unaided; σ²/2 role understood as log-normal asymmetry correction (e^(+0.1)+e^(−0.1))/2 > 1 demonstrated numerically. (b) YTM bisection solver built from scratch at [projects/week04/bond_pricer_ytm.cpp](projects/week04/bond_pricer_ytm.cpp) — bondPrice extracted from W2 logic unaided; f(r)=0 formulation derived after algebra coaching; bisection loop written correctly; bounds-swap bug caught via one-iteration trace and self-corrected; YTM=0.05 verified on par bond. (c) σ=0 and T=0 break d1/d2 denominator (division by zero) — guards correctly placed in functions not main; silent `return 1` identified as bad error signal; assert recommended as fix. Spaced W3 retrieval: log vs arithmetic returns — r₁×r₂ cross-term derived from (1+r₁)(1+r₂) expansion; arithmetic sum vs compound distinction clean; log symmetry demonstrated numerically.

- **2026-05-05 — W4 Day 2: BS pricer implemented and tests passing.** [projects/week04/bs_pricer.cpp](projects/week04/bs_pricer.cpp) compiles clean under `-Wall -Wextra -std=c++20`. Call(100,100,0.05,0.2,1) = 10.45 ✓. Delta = N(d1) = 0.64 ✓. Vega = S·√T·φ(d1) = 37.52 ✓. Put pricer added; put-call parity assert passes. Two bugs caught and fixed: missing `*T` on r term, operator precedence in denominator (both masked by T=1 — exposed at T=0.5). Edge case guards on sigma=0 and T=0. Remaining: parity test covers 1 input set; curriculum requires 20.

- **2026-05-03 — W3 Day 5: Acceptance test passed + retrospective written.** Both criteria cleared: output matches Python reference to 4 d.p. (Mean 0.0163, Variance 0.0009, Std Dev 0.0301); n=1 edge case handled cleanly via guards with no crash. Retrospective at [projects/week03/retrospective.md](projects/week03/retrospective.md). Week 3 complete.

- **2026-05-03 — W3 Day 4: Code review complete.** Blocking fix: `mean()` guard changed from `<= 1` to `<= 0` (mean defined for n=1; only empty vector is invalid). Suggestions applied: `price_series` global marked `const`; `returns_vector()` now takes `const std::vector<double>& prices` parameter instead of reading global; parameter `mean` renamed to `mean_val` in `sample_variance()` and `standard_deviation()` to eliminate function-name shadowing.

- **2026-05-03 — W3 Day 3: Closed-book retrieval complete.** (a) Bond pricer re-implemented from scratch — structure correct; `r` vs `y` in denominator caught after one prompt; sum range `i=2` corrected after one prompt; code verified correct. (b) `accumulate` precision loss — additive mechanism understood after one worked example; applied correctly to price_series.cpp variance. (c) Log vs simple returns — time vs cross-section direction unaided; ln product rule cancellation derived after one prompt.

- **2026-04-29 — W3 Days 1–2: Stats tool implemented.** [projects/week03/price_series.cpp](projects/week03/price_series.cpp) compiles clean under `-Wall -Wextra -std=c++20`. Output matches Python reference to 4 d.p.: Mean 0.0163, Variance 0.0009, Std Dev 0.0301. Key concepts landed: arithmetic vs log returns; why log returns are additive (ln product rule); sample variance with n−1 (Bessel's correction); `std::vector` declaration and `.push_back()`; const-ref parameters applied in code for first time; signed/unsigned comparison warning understood and fixed; operator precedence bug caught and fixed independently.

- **2026-04-29 — W2 Day 4: Code review complete.** Two blocking issues fixed: (1) missing `n <= 0` guard added after reading `n`; (2) WHAT comments removed throughout. Loop condition cleaned up (`i < n+1` → `i <= n`). `y == -1` tightened to `y == -1.0`. Both acceptance criteria still pass. Floating-point equality pattern and tolerance bands explained; will apply in W4.

- **2026-04-29 — W2 Day 3: Closed-book retrieval complete.** (a) PV re-derivation: unaided. (b) `r` vs `y` distinction: unaided. (c) Bond price/yield direction: unaided — one mechanical error (said numerator drops; correct: denominator grows) caught and fixed. Spaced retest from W1: UB mechanism retrieved with one prompt (syntax/semantics gap); zero-overhead principle needed two prompts — concept understood, vocabulary wasn't there. const-ref reasoning needed scaffolding — expected, not yet coded.

- **2026-04-25 — W2 Day 2: Bond pricer implemented.** [projects/week02/bond_pricer.cpp](projects/week02/bond_pricer.cpp) compiles clean under `-Wall -Wextra -std=c++20`. Both acceptance criteria pass: F=1000 r=0.05 y=0.05 n=5 → 1000.00; y=0.06 → 957.88 (below par). Key concepts landed: `r` (coupon rate) vs `y` (yield/discount rate) distinction; guard placement before computation; loop off-by-one (`i < n+1`); `n` as `int` not `double`; WHAT comments removed.

- **2026-04-23 — W2 Day 1: Bond pricer spec locked.** Bond price formula derived from first principles: `Σ C/(1+y)^i + F/(1+y)^n`. Spec: inputs `F: double`, `C: double`, `y: double`, `n: int`; guards `y == -1.0` and `n <= 0`; output to 2 d.p. Functions introduced: `couponPV` and `facePV` written correctly (with coached fix: missing `double` return type). Integer division trap (`7/2 = 3`) and assignment-too-late fix understood.

- **2026-04-20 — W1 Day 5: Acceptance test re-run + retrospective complete.** [projects/week01/pv.cpp](projects/week01/pv.cpp) passes 2/2 acceptance tests (compile clean, output `863.84`, guard exit-code 1). Week 1 retrospective written at [projects/week01/retrospective.md](projects/week01/retrospective.md). Key learning: hints need surrounding context, not just direction.
- **2026-04-20 — W1 Day 4: Code review complete.** One blocking issue fixed: silent `return 1` on `r==-1` guard → now emits `std::cerr` message before exit. Two non-blocking suggestions logged (floating-point equality pattern; `n<0` silent oddity). All five edge cases (`n=0`, `n<0`, large `n`, `r` near `-1`, negative `FV`) analyzed — no crashes, behavior documented. `std::cerr` vs `std::cout` distinction understood: separate OS streams, not just error-vs-success labeling.
- **2026-04-20 — W1 Day 3: Closed-book retrieval complete.** (a) PV derivation: strong, unaided. (b) `double` vs `float`: strong, unaided. (c) `-Wall` warnings: got it with one hint. (d) Undefined behavior: got it with scaffolding — mechanism (leftover stack bytes) retrieved after prompting. Re-test UB on 2026-04-22.
- **2026-04-18 — W1 Day 2: PV calculator implemented & debugged.** [projects/week01/pv.cpp](projects/week01/pv.cpp) compiles clean under `-Wall -Wextra -std=c++20`, prints `863.84` for spec input, breakpoint on discount line (15) hits under CodeLLDB, `PV` observed transitioning from uninitialised garbage (`4.179…`) to `863.84`. Guard `r == -1.0` in place before division. Uses `std::pow` from `<cmath>`; output formatted via `<iomanip>` (`std::fixed << std::setprecision(2)`). Off-by-one in hand-written loop caught via trace-based coaching (never made it into source).
- **2026-04-18 — Pre-flight environment setup.** All 9 boxes in [setup.md:297-307](setup.md#L297-L307) green: Apple Clang 21, git 2.45.2, lldb 2100, Homebrew 5.1.0, VS Code 1.116 (arm64), cpptools + CodeLLDB extensions, GitHub account, `projects/week01/` created, smoke test `./hello` printed `Hello, finance`.
- **2026-04-18 — PV formula derived from first principles.** User reasoned from opportunity cost to `FV = PV × (1+r)^n`, solved for PV, computed `PV(1000, 5%, 3) = 863.84`, and correctly predicted PV decreases as `r` increases.
- **2026-04-18 — Compiler flags understood.** User correctly reasoned that `-Wall` off → compile succeeds but program may misbehave (warnings ≠ errors).
- **2026-04-18 — W1 Day 1: PV calculator spec locked.** Inputs: `FV: double`, `r: double` (reject `r == -1.0`), `n: int`. Output: `PV: double`, printed to 2 decimal places. User derived: `double` over `float` from compounding rounding error; `r=-1` breaks math (div by zero) while `n<0` is defined but unusual; near-singularity overflow behavior derived unaided.

## Blocked / parked

_None._
