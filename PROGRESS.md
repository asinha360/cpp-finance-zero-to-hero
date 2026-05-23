# PROGRESS.md

## Current state
## Next session

**First action:** W8 Day 3 — code review of `projects/week08/` as Code Reviewer: check naming, missing guards (empty returns from `load_prices`, file-open failure in `csv_loader`), and output formatting.
**Retrieval question:** "Write the GBM path formula from memory — both terms with correct notation."
**Carry-forwards:** GBM formula notation (wrote (σ/2)² instead of σ²/2; 1/2 today)

---

- **Today's date:** 2026-05-22
- **Curriculum week:** 8 of 16 — **In Progress**
- **Days into curriculum:** 18 (calendar) / 31 sessions complete
- **Schedule status:** On track
- **Next milestone:** Week 8 — Monte Carlo VaR on real historical data
- **Today's artifact:** [notes/w8_d2.md](notes/w8_d2.md)

- **W8 Day 2 wins:**
  - Three-file architecture designed from scratch: csv_loader.h/cpp (adapted from W7), normal_sampler.h (header-only from W6), var_model.h, var_model.cpp — correct separation of declarations and definitions across all files.
  - All three VaR (Value at Risk) functions implemented: historical_VaR (sort log returns, percentile index), parametric_VaR (μ + z×σ with z = −1.645/−2.326), monte_carlo_VaR (100k NormalSampler draws, sort, percentile index).
  - Compiled clean, zero warnings under `-Wall -Wextra -std=c++20`. Output: historical −0.0256/−0.0357; parametric −0.0254/−0.0359; MC −0.0254/−0.0359 (95%/99%). Both sanity checks passed.
  - Key bugs caught and fixed: definitions in header (→ declarations only); `<ifstream>` doesn't exist (→ `<fstream>`); `load_prices()` ignoring filepath parameter; per-row print inside utility function; `std::sort` on `const&` (→ local copy); indexing sorted copy using wrong (unsorted) vector name; loop off-by-one (N+1 → N); z-score digit transposition (−2.236 → −2.326); comma operator in `cout` chain (→ `<<`).
  - Design reasoning: no CSVLoader class (no state to encapsulate); parametric/MC VaR take pre-computed mean/stddev from caller — caller computes once, passes to all three methods.
  - GBM formula carry-forward: 1/2 — wrote (σ/2)² instead of σ²/2; self-corrected after one algebraic coaching step.

- **W8 Day 1 wins:**
  - Three carry-forwards cleared: `>>` vs `getline` (2/2 with one follow-up at opening; 2/2 unaided on closing **[FIRST TIME]**); σ asymmetry full mechanism (2/2 unaided — floor at 0 neutralizes downside, payoff scales with distance past K); RNG state continuity (2/2 unaided — "identical").
  - Three VaR methods (Value at Risk — loss threshold exceeded only X% of the time) derived from first principles: historical simulation (sort log returns, index at 5%), parametric (μ + z×σ, z = −1.645 for 95%), Monte Carlo (simulate N draws from N(μ,σ), sort, index at 5%).
  - Fat tails identified as the assumption parametric VaR makes that real equity data violates — consequence articulated correctly 2/2 unaided: "parametric VaR at 99% will be too low compared to real equity returns due to thin tails."
  - Historical simulation weakness: bounded by observed data; 99% VaR rests on only 5 data points out of 500 — unstable estimate.
  - Percentile index arithmetic: 95% VaR → index 24 (with one coaching step from range to single index); 99% VaR → index 4 (2/2 unaided).
  - Toolkit inventory: identified which W5–W7 pieces each VaR method reuses and what is genuinely new (sort + percentile index; z-score constant for parametric; NormalSampler already exists from W6).

- **W7 Day 4 wins:**
  - log_returns function written from scratch: correct `const std::vector<double>&` parameter, index loop with `< size() - 1` bound, `std::log(price_vec[i+1] / price_vec[i])`. Four bugs caught and fixed: range-for-as-index error, comma vs semicolon, off-by-one (went wrong direction first), missing `&` in parameter.
  - Silent return 0.0 anti-pattern caught again in copied functions — `return EXIT_SUCCESS` (== 0) identified as same issue as W4/W5. Fixed to `assert(!returns.empty())` and `assert(returns.size() >= 2)`.
  - Output formatting bug caught: `log_mean << std_dev` with no separator. Fixed to separate labelled lines.
  - Verified against Python reference: mean 0.000932505, stdev 0.0143042 — match to 7 significant figures. Zero warnings under `-Wall -Wextra -std=c++20`.
  - Stationarity (due 2026-05-22, tested one day early): 2/2 after one build-up question. "Prices trend — the sample mean of years 1–5 differs from years 6–10 because the price level has drifted." Improved from 1/2 at introduction.
  - `break`/`continue` use-case: 2/2 — "continue because 1 row doesn't make the input invalid." Carry-forward cleared.
  - σ asymmetry precision: 1.5/2. Same error as W7D3 — "raises probability of ending ITM" vs "expected payoff scales with distance past K." Re-test next session.
  - RNG state continuity: 1.5/2. Mechanism correct; said "correlated" instead of "identical." Same precision error as W6D5. Re-test next session.

- **W7 Day 3 wins:****
  - `continue` structural rule: 1/2 opening → 2/2 after one coaching pass. Applied correctly to csv_loader.cpp: npos `continue` = load-bearing (substr/stod/catch below it); end-of-catch `continue` = redundant. Carry-forward cleared.
  - MC convergence O(1/√N): 2/2 unaided. CLT → SE = stdev/√N → 4×N halves error. Derived from first principles. Carry-forward cleared.
  - Range-for vs index loop: 2/2 after coaching. Initially reversed examples; corrected to: range-for requires existing collection; index loop when no collection (repeat-N). Carry-forward cleared.
  - BS inputs + directions: 5/5 unaided. All five inputs and directions correct. Carry-forward cleared.
  - σ asymmetry precision: "probability of reaching strike" corrected to "expected payoff scales with distance past K." Re-test due 2026-05-21.
  - `\n` vs `/n` vs `endl`: improved from 0/2 (W7D1) to 2/2. "clears" → "flushes" for `endl` corrected. Carry-forward cleared.
  - Stationarity: introduced — returns are approximately stationary (stable mean/variance); prices are not (drift with price level). **[FIRST TIME]**
  - `>>` vs `getline` delimiter: introduced — `>>` splits on all whitespace; `getline` reads to `\n`. **[FIRST TIME]**

- **W7 Day 2 wins:**
  - `std::stod` conversion applied correctly; `try/catch` on `std::invalid_argument` placed correctly per-row inside loop.
  - `std::accumulate` with `0.0` (double, not int) — correct on first attempt.
  - Empty-vector guard: `if (!price_vec.empty())` with `cerr` + `return 1` — correct after one coaching pass (initial proposal `assert(price_vec.empty())` had inverted condition and wrong tool).
  - IEEE 754 float div/0 distinguished from integer UB: `0.0/0.0 = NaN`, not undefined behaviour — corrected belief; connected to W4 silent-return anti-pattern independently.
  - npos+1 overflow chain traced unaided when double-print bug appeared: "if(npos) block & catch both print malformed row — removed continue for the if so execution reaches second one."
  - Zero warnings under `-Wall -Wextra -std=c++20`; mean 477.832 verified correct.

- **W7 Day 1 wins:**
  - SE/CLT carry-forward improved from 0/2 → partial: CLT mechanism stated correctly; skewness-as-cause conflation corrected after coaching. Follow-up check ("symmetric payoffs — still divide by √N?") answered correctly unaided.
  - File I/O model understood: `std::ifstream` as stream pipe; `std::getline` as loop condition (stream → bool). Initially confused stream return with `npos` — corrected after explanation.
  - Tokenization implemented correctly on first attempt: `find(',')`, `substr(0, pos)`, `substr(pos+1)`. `npos` guard with `continue` applied correctly.
  - `\n` vs `endl` vs `/n` bug caught and corrected: `"/n"` prints literal `/n`; `"\n"` is the newline escape; `endl` = newline + flush (slower, unnecessary).
  - `std::stod` introduced: "string to double"; returns `double`; throws on bad input. Meaning + return type retrieved unaided. **[FIRST TIME]**
  - `csv_loader.cpp` compiles zero warnings under `-Wall -Wextra -std=c++20`; output correct; malformed-row guard fires to stderr.

- **W6 Day 5 wins:**
  - Acceptance test passed: MC price 10.4384 inside band [10.2802, 10.5609] containing BS 10.4502. Zero warnings, exit 0. **[FIRST TIME]** assert-based convergence test written from scratch.
  - `std::pair<double,double>` introduced: `price_call()` extended to return discounted mean and stdev; structured binding `auto [price, stddev]` used correctly in `main()`.
  - One-pass variance formula applied: `sum_sq/N - mean^2`. Bug caught: `(p-p)*p` → corrected to `p*p` independently after one coaching question.
  - Standard error concept landed: SE = stdev of sample mean across runs (not stdev of individual payoffs). Payoff stdev 14.79 vs SE 0.047 — distinction confirmed understood.
  - 3-sigma band: 99.73% coverage from CLT; "3" is not from convergence rate but from normal distribution. Python visual confirmed before C++ implementation.
  - Opening carry-forward cleared: `_simulator` member vs local — correct mechanism unaided. **[FIRST TIME]** cleared without scaffolding.
  - Retrospective written at [projects/week06/retrospective.md](projects/week06/retrospective.md). **Week 6 complete.**

- **W6 Day 4 wins:**
  - Three roles of `*` carry-forward: 3/3 clean. Declaration example corrected (`&x` not `5.0`). **[FIRST TIME]** carry-forward cleared on opening retrieval.
  - Code review completed: `NormalSampler`, `GBMSimulator`, `MCPricer` — zero blocking issues.
  - `MCPricer` refactored: seed and steps promoted to constructor parameters; `_simulator` promoted to member variable; redundant private fields removed; reorder warning fixed.
  - RNG state continuity understood: fresh-local vs persistent-member distinction articulated correctly — "contiguous RNG state maintained across calls."
  - `reserve()` rationale understood: one upfront allocation vs repeated realloc on `push_back`.
  - Zero compiler warnings under `-Wall -Wextra -std=c++20`; output 10.4384 confirmed.

- **W6 Day 3 wins:**
  - Three roles of `*`: 3/3 clean. All named and exemplified correctly. Precision point: in declaration, `*` is part of the type, not an operator (`double* p, q;` trap).
  - `push_back` vs pre-initialized `counts[i]++`: 2/2 — sharpest version yet. "Fixed-size vector of counters vs dynamic append" articulated correctly with histogram context.
  - Member initializer list syntax: 2/2. **[FIRST TIME]** Correct after one failed attempt in W6 Day 1. Values in `()`, not type names.
  - MC convergence O(1/√N): concept landed. σ/√N recalled from W3 unaided. Quadrupling N halves error derived algebraically. 100× paths for 10× error reduction correct unaided. Initial "exponential" intuition corrected.

- **W6 Day 2 wins:**
  - σ²/2 mechanism articulated in one sentence after one numerical hint: "e^x is convex — upside lifts more than downside drops; σ²/2 subtracts the excess so expected price grows at exactly r." Jensen's inequality cleared.
  - `#include` mechanics understood from first principles: preprocessor copy-paste, not a function call. **[FIRST TIME]**
  - Header guards written correctly and independently on all three headers. **[FIRST TIME]**
  - Header/source split applied across a three-file project. **[FIRST TIME]**
  - `MCPricer` implemented correctly. At N=100,000: 10.4384 vs BS 10.45 — within convergence band. W6 acceptance criterion passed.
  - Six bugs caught and fixed: wrong index (`sim_vec[251]` → `sim_vec.back()`), unused `_N`, missing type in range-for, duplicate class definition in `.cpp`, unused includes, missing `<algorithm>`.

- **W6 Day 1 wins:**
  - Spaced retests cleared: vector internals (control block/data/destructor) 3/3 unaided; memory leak mechanism — "OS cannot reclaim" sharpened to "runtime allocator cannot reclaim mid-run."
  - `NormalSampler` class built from scratch: member initializer list, `public`/`private`, RAII principles applied correctly. Two independent seeds confirmed to produce independent streams.
  - `GBMSimulator` class built: constructor, member initializer list with nested `_sampler` init, `simulate_path()` loop correct on first attempt. Compiled clean under `-Wall -Wextra -std=c++20`.
  - GBM formula two-part structure (drift + shock) understood; sigma=0 reduction to pure compounding derived and verified.
  - Weak spots flagged for re-test: member initializer list syntax; GBM formula from memory.
  - **[FIRST TIME]** full class built from scratch with correct RAII structure, no raw new/delete.

- **W5 Day 5 wins:**
  - Acceptance test passed: mean 0.00179 ∈ [-0.005, 0.005] ✓, stdev 0.99992 ∈ [0.995, 1.005] ✓, seed 123 byte-for-byte ✓.
  - σ asymmetry carry-forward cleared: "downside is floored at 0 (call expires worthless), upside is unbounded; σ lifts both tails but only the beneficial one counts" — full mechanism, unprompted, one sentence. [FIRST TIME robust unaided retrieval under closing pressure]
  - `push_back` vs `counts[bin_index]++` carry-forward cleared: growth (append new element) vs mutation (increment existing slot) distinction articulated correctly.
  - Retrospective written at [projects/week05/retrospective.md](projects/week05/retrospective.md). Three concrete process changes logged for W6.
  - **Week 5 complete.**

- **W5 Day 4 wins:**
  - Code review: blocking issue (silent `return 0.0` sentinel) identified and fixed in both `mean` and `sample_variance` — same W4 anti-pattern, caught independently after one prompt.
  - Range-for applied correctly with `const double&`; type error (`const int&`) self-corrected after one prompt.
  - `assert(size() >= 2)` and `static_cast<double>` polish applied correctly.
  - Histogram built from scratch: binning algorithm, clamping, `counts[i]++` vs `push_back` distinction understood, aligned print loop with inner star loop.
  - BS inputs retrieval: 5/5 directions unaided. σ asymmetry (downside floor = 0, upside unlimited) stated without prompting. [FIRST TIME] full reasoning unaided — W5 Day 2 needed coaching.
  - Range-for vs index loop distinction: range-for requires an existing collection; repeat-N loop has no collection — index loop is correct. Retrieved unaided.

- **W5 Day 3 wins:**
  - PV calculator re-implemented from scratch (week+4 spaced re-derive): formula recalled and coded; `std::setprecision` bug self-diagnosed after one hint (address-of vs call); `assert(r > -1)` improvement spotted after coaching.
  - Three roles of `*` recalled unaided — all three clean. [FIRST TIME] all three without prompting.
  - T& vs T* distinctions named correctly unaided; "static memory" framing corrected to stack vs heap distinction.
  - Pointer rebinding trace: x=10.0, y=99.0 — correct unaided.
  - Stack vs heap: labels were initially swapped (called stack "heap"); corrected. Vector internals understood: control block on stack, data on heap. [FIRST TIME] correct model unprompted after explanation.
  - Memory leak mechanism understood; RAII motivation clear — W6 foundation set.

- **W5 Day 2 wins:**
  - RNG harness built and both W5 acceptance criteria green: mean in [-0.005, 0.005], stdev in [0.995, 1.005], same seed reproduces byte-for-byte.
  - `dist(sample)` vs `dist(engine)` bug self-diagnosed after one coaching question (type reasoning: engine vs double).
  - Seeding: non-reproducibility identified independently by observing different output on second run; fixed to hardcoded seed.
  - `.empty()` method introduced; signed/unsigned cast removed from both guards.
  - W4 spaced retrieval (BS inputs + directions): 5/5 on inputs and directions. σ direction wrong initially; self-corrected after asymmetry coaching (capped downside, uncapped upside). r direction correct unaided — [FIRST TIME], W4 Day 1 needed correction.

- **W5 Day 1 wins:**
  - Memory model: pointers, references, `const&` — all concepts landed correctly with minimal scaffolding.
  - Off-by-one on address arithmetic caught and self-corrected after explanation.
  - Three roles of `*` (declaration / read-dereference / write-dereference) clarified; confusion flagged honestly.
  - Two-pointer aliasing retrieved correctly unaided (both p and q see *p = 20.0 change).
  - RNG: engine/distribution separation understood; seeding purpose reasoned from first principles without knowing the term. [FIRST TIME] unaided on seeding rationale.
  - W2 spaced retrieval (const-ref vs by-value): [FIRST TIME] retrieved unaided — prior session needed scaffolding.

- **W4 Day 5 wins:**
  - Bessel's correction retrieved correctly: minimizer property named unaided; degrees-of-freedom reasoning for n=1 (zero deviations, undefined variance) reached without a prompt. [FIRST TIME] minimizer framing landed cleanly — prior session needed scaffolding.
  - Week 4 retrospective written at [projects/week04/retrospective.md](projects/week04/retrospective.md). Three concrete process changes identified for W5.
  - Milestone 1 closed: Black-Scholes pricer from scratch — both acceptance criteria green.

- **W4 Day 4 wins:**
  - `compute_d1` / `compute_d2` helpers extracted; d1 duplication eliminated across all 4 callers.
  - Assert placed in `compute_d1` — single point of protection, all callers covered automatically. Principle understood: guard at the most foundational level.
  - Silent `return 1` anti-pattern removed — now crashes loudly via assert.
  - Parity test extended to 20 varied inputs (ITM/OTM/ATM, T 1–20, sigma 0.1–0.9); all pass at 1e-10.
  - Table-driven testing pattern understood and applied independently.
  - **[FIRST TIME]** ITM / OTM / ATM terminology introduced and applied to test case design.
  - Spaced retrieval (W1): PV derivation — FV=PV·(1+r)^n derived unaided; "accumulation factor" vs "rate of growth per year" distinction sharpened.

- **W4 Day 3 wins:**
  - d1 and d2 recalled exactly unaided.
  - **[FIRST TIME — finance]** σ²/2 as log-normal asymmetry: even when log returns are symmetric around zero, prices drift up on average because e^(+x) raises more than e^(−x) lowers. Demonstrated numerically: (e^0.1 + e^-0.1)/2 = 1.005 ≠ 1. The full mechanism (Jensen's inequality) is deferred to W6 when GBM paths can be seen empirically.
  - **[FIRST TIME — finance]** r₁×r₂ cross-term: expanding (1+r₁)(1+r₂) produces four terms; the r₁×r₂ term is "the return on the return." Naive arithmetic sum drops it. Correct compound arithmetic (21%) and log return (19.06%) are different measurement scales, not errors — demonstrated on P₀=100, P₁=110, P₂=121.
  - **[FIRST TIME — algorithms]** Bisection method: first numerical root-finding algorithm. Rewrite equation as f(x)=0, bracket root with known sign-change, halve the interval each iteration until tolerance is met. Implemented from scratch at [projects/week04/bond_pricer_ytm.cpp](projects/week04/bond_pricer_ytm.cpp).
  - **[FIRST TIME — finance]** Yield to maturity as a root-finding problem: YTM is the r solving f(r) = bondPrice(r) − market_price = 0. No closed form exists — numerical search required. f(r)=0 formulation needed algebra scaffolding (subtraction, not division).
  - **[FIRST TIME — C++ best practice]** Silent numeric error return anti-pattern: returning `1` from a price function is indistinguishable from a valid price. Bisection would treat it as data and produce a wrong answer silently. Fix: `assert` crashes loudly; `NaN` propagates visibly through arithmetic.
  - Guard placement reasoning: functions own their preconditions because they can be called from anywhere — not just `main`.

- **W4 Day 2 wins:**
  - normal_cdf written correctly: Φ(x) = 0.5·(1+erf(x/√2)) relationship understood and applied.
  - normal_pdf written correctly: differentiation from CDF to PDF reasoned with coaching.
  - blackScholesCall implemented; two bugs caught and self-corrected after T=0.5 test: missing `*T` on r term and operator precedence in denominator (both masked by T=1).
  - Delta derived from ∂C/∂S = N(d1) by mental differentiation — second term drops to zero correctly.
  - Put-call parity derived from payoff reasoning; C−P = S−K·e^(−rT) computed correctly for test inputs.
  - blackScholesPut implemented correctly; parity assert passes to 1e-10.
  - Edge case guards on sigma=0 and T=0 added.
  - UB "plausible-yet-misleading" outcome identified in own code (buggy d1 that passed T=1 test).

- **W4 Day 1 wins:**
  - Option payoff structure derived: max(S_T − K, 0) reasoned from first principles without prompting.
  - All five BS inputs named, symbolised, and directional effects on call price reasoned correctly (4/5 unaided; r mechanism needed one correction — discounting reduces present value of K, not increases it).
  - d1 and d2 recalled from memory exactly, unaided, at end of session.
  - Two-term formula structure understood: expected receipt (S·N(d1)) minus expected payment (K·e^(−rT)·N(d2)).
  - Foundation: log returns → CLT → log-normal S_T → normal distribution is the right tool.

- **W3 summary:**
  - Arithmetic vs log returns derived from first principles; additivity of log returns proved via ln product rule.
  - Sample variance with n−1 reasoned from sample estimation; n=1 edge case understood (undefined, not a crash).
  - `std::vector` declaration, `.push_back()`, `.size()` all applied correctly in code.
  - const-ref parameter pattern applied in code for first time — landed after W2 scaffolding.
  - Signed/unsigned comparison warning understood and fixed independently after explanation.
  - Operator precedence bug caught and fixed without prompting (second occurrence — pattern solidifying).
  - Output verified against Python reference to 4 d.p.

## Week-by-week ledger

| Week | Topic | Status | Started | Completed | Artifact | Retrospective |
|------|-------|--------|---------|-----------|----------|---------------|
| 1 | Toolchain works; present-value calculator | **Complete** | 2026-04-18 | 2026-04-20 | [projects/week01/pv.cpp](projects/week01/pv.cpp) | [projects/week01/retrospective.md](projects/week01/retrospective.md) |
| 2 | Functions + control flow; bond pricer | **Complete** | 2026-04-23 | 2026-04-29 | [projects/week02/bond_pricer.cpp](projects/week02/bond_pricer.cpp) | [projects/week02/retrospective.md](projects/week02/retrospective.md) |
| 3 | Collections + summary statistics; returns stats tool | **Complete** | 2026-04-29 | 2026-05-03 | [projects/week03/price_series.cpp](projects/week03/price_series.cpp) | [projects/week03/retrospective.md](projects/week03/retrospective.md) |
| 4 | **MILESTONE 1** — Black-Scholes pricer with Δ, ν | **Complete** | 2026-05-03 | 2026-05-06 | [projects/week04/bs_pricer.cpp](projects/week04/bs_pricer.cpp) | [projects/week04/retrospective.md](projects/week04/retrospective.md) |
| 5 | Memory model + first RNG; normal RNG harness | **Complete** | 2026-05-07 | 2026-05-11 | [projects/week05/rng_harness.cpp](projects/week05/rng_harness.cpp) | [projects/week05/retrospective.md](projects/week05/retrospective.md) |
| 6 | Classes + RAII; GBM MC option pricer | **Complete** | 2026-05-11 | 2026-05-14 | [projects/week06/mc_pricer.h](projects/week06/mc_pricer.h) | [projects/week06/retrospective.md](projects/week06/retrospective.md) |
| 7 | File I/O; CSV loader + returns summary | **Complete** | 2026-05-18 | 2026-05-21 | [projects/week07/csv_loader.cpp](projects/week07/csv_loader.cpp) | [projects/week07/retrospective.md](projects/week07/retrospective.md) |
| 8 | **MILESTONE 2** — Monte Carlo VaR on real data | In Progress | 2026-05-22 | — | [projects/week08/var_model.cpp](projects/week08/var_model.cpp) | — |
| 9 | STL containers + algorithms; OHLC bar aggregator | Not started | — | — | — | — |
| 10 | Polymorphism; SMA-crossover strategy | Not started | — | — | — | — |
| 11 | Limit order book with matching | Not started | — | — | — | — |
| 12 | **MILESTONE 3** — order-book replay backtester | Not started | — | — | — | — |
| 13 | Performance: profiling + variance reduction | Not started | — | — | — | — |
| 14 | Parallelism; parallel MC pricer | Not started | — | — | — | — |
| 15 | CMake + GoogleTest + repo hygiene | Not started | — | — | — | — |
| 16 | **MILESTONE 4** — 3 polished GitHub portfolio repos | Not started | — | — | — | — |

## Milestones (from [CONTEXT.md](CONTEXT.md) success criteria)
- [x] Week 4 — Black-Scholes pricer from scratch
- [x] Week 7 — CSV loader with File I/O (prerequisite for Milestone 2)
- [ ] Week 8 — Monte Carlo VaR on real data
- [ ] Week 12 — Order-book replay backtester
- [ ] Week 16 — 3 portfolio projects on GitHub

## Retrieval-practice scores (rolling)

| Date | Topic | Score (correct/total) | Re-test on |
|------|-------|----------------------|------------|
| 2026-04-18 | PV derivation + `r↑ ⇒ PV↓` intuition | 2/2 (after derivation coaching) | 2026-04-21 |
| 2026-04-18 | Compiler warnings semantics (`-Wall` off) | 1/1 | 2026-04-25 |
| 2026-04-18 | PV formula recall (same-day retest, ~hours after first derivation) | Formula ✓; intuition re-coached to "smaller seed reaches same FV at higher r" | 2026-04-21 |
| 2026-04-18 | `double` vs `float` for money — reasoning from compounding rounding error | 1/1 unaided | 2026-04-25 |
| 2026-04-18 | Undefined-vs-odd input classification (r=-1 breaks, n<0 is fine) | Got it on second pass after walking through algebra | 2026-04-22 |
| 2026-04-18 | `double` vs `float` — compounding of rounding error | 1/1 core reasoning; catastrophic cancellation added as enrichment | 2026-04-25 |
| 2026-04-18 | Loop to compute `(1+r)^n` via repeated multiplication — trace at `n=3` | Correct trace; mis-labeled "factor of 20" corrected to factor of `(1+r)` | 2026-04-22 |
| 2026-04-18 | Identity-of-operation principle for loop init (`x=1` makes `n=0` free) | 1/1 after trace-based elicitation | 2026-04-25 |
| 2026-04-18 | Breakpoint semantics + uninitialised-memory reading | Predicted "panel empty"; corrected via live debugger observation | 2026-04-21 |
| 2026-04-18 | Read vs write behavior on debugger Variables panel | 1/1 unaided | 2026-04-25 |
| 2026-04-18 | Guard placement (before vs after the operation) | Correct placement; *why* upgraded from "compute time" to "correctness" | 2026-04-21 |
| 2026-04-20 | `-Wall` — category and purpose | Got it with one hint (example: uninit variable warning) | 2026-04-23 |
| 2026-04-25 | `-Wall` — category and purpose (spaced retest) | 1/1 unaided — no hint needed; correctly named warnings vs errors and gave concrete example (unintended assignment) | 2026-04-30 |
| 2026-04-29 | UB mechanism (spaced retest) — leftover stack bytes, why compiler doesn't refuse | Retrieved with one prompt; syntax vs semantics vocabulary gap filled; silent corruption > crash reasoning unaided | 2026-05-04 |
| 2026-04-29 | Zero-overhead principle — why C++ warns not errors on uninit reads | Concept retrieved after two prompts; "runtime overhead" vocabulary wasn't there unprompted | 2026-05-03 |
| 2026-04-29 | PV re-derivation (spaced W2 retrieval) | 1/1 unaided | 2026-05-06 |
| 2026-04-29 | `r` vs `y` distinction — coupon rate vs yield | 1/1 unaided | 2026-05-04 |
| 2026-04-29 | Bond price direction when yield rises — formula reasoning | Direction unaided; one mechanical error (said numerator drops; correct: denominator grows) | 2026-05-04 |
| 2026-04-29 | const-ref vs by-value — reasoning from copy cost | Needed scaffolding (concept not yet coded); retrieved correctly once framed | 2026-05-02 |
| 2026-04-29 | Arithmetic vs log returns — additivity, when to use each | Derived unaided after ln product rule shown; cross-section vs compounding distinction clean | 2026-05-04 |
| 2026-04-29 | Sample variance n−1 — Bessel's correction | Needed scaffolding to reach "sample mean is estimated not known"; n=1 edge case reasoned correctly | 2026-05-04 |
| 2026-04-29 | Operator precedence — returns formula and variance denominator | Bug caught and fixed without prompting on second occurrence — pattern solidifying | 2026-05-06 |
| 2026-04-29 | Signed/unsigned comparison warning | Understood after explanation; fix applied correctly | 2026-05-06 |
| 2026-04-20 | Undefined behavior — definition, mechanism, why it doesn't crash | Needed scaffolding; mechanism (leftover stack bytes) retrieved after prompting | 2026-04-22 |
| 2026-05-03 | W4 Day 1 — option payoff, BS inputs, d1/d2 recall | d1 and d2 recalled exactly unaided; all 5 inputs named and directional reasoning correct 4/5; r mechanism corrected after one prompt | 2026-05-10 |
| 2026-05-05 | UB mechanism (spaced W1 retest) | Zero-overhead principle named after one prompt; plausible-yet-misleading outcome identified independently in own buggy d1 formula | 2026-05-12 |
| 2026-05-05 | d1/d2 distinction — σ²/2 term and N(d1) vs N(d2) roles | Mechanical difference correct unaided; N(d1)/N(d2) role mixed up (attributed N(d1) to K payment) — corrected after one prompt | 2026-05-12 |
| 2026-05-05 | Delta derivation from ∂C/∂S | Second term correctly dropped to zero unaided; delta = N(d1) derived cleanly | 2026-05-12 |
| 2026-05-05 | Put-call parity — derivation and numeric check | C−P = S−K·e^(−rT) derived from payoff table with coaching; numeric result 4.88 computed correctly | 2026-05-12 |
| 2026-05-06 | PV derivation spaced retest (W1, third rep) | Formula unaided; derivation path shown correctly (FV=PV·(1+r)^n → solve for PV); "accumulation factor" vs "rate per year" sharpened | 2026-05-13 |
| 2026-05-06 | W3 spaced retest — log vs arithmetic returns, r₁×r₂ cross-term | (1+r₁)(1+r₂) expansion correct after one algebra correction; naive sum vs compound distinction clean; log symmetry demonstrated numerically | 2026-05-13 |
| 2026-05-06 | Sample variance n−1 — Bessel's correction (W3 spaced retest, overdue) | Minimizer property named after one hint; degrees-of-freedom reasoning for n=1 reached unaided | 2026-05-13 |
| 2026-05-06 | d1 and d2 recall (W4 Day 3 retrieval) | Both recalled exactly unaided | 2026-05-13 |
| 2026-05-06 | σ²/2 role in d1 | Log-normal asymmetry understood numerically; "corrects for" vs "accounts for" framing sharpened | 2026-05-13 |
| 2026-05-06 | YTM bisection solver — algorithm and implementation | f(r)=0 formulation needed algebra coaching; bisection written correctly; bounds-swap bug self-corrected via trace | 2026-05-13 |
| 2026-05-03 | `-Wall` spaced retest (W1) | 1/1 unaided — warnings vs errors and two concrete examples (uninit vars, assignment-vs-comparison) | 2026-05-10 |
| 2026-05-03 | Bond pricer re-implementation from scratch (W3 Day 3a) | Structure recalled correctly; formula used `r` instead of `y` in denominator — caught and self-corrected after one prompt; sum lower bound started at `i=2`, corrected after one prompt; code compiled and logic verified correct | 2026-05-10 |
| 2026-05-03 | `std::accumulate` double precision loss (W3 Day 3b) | Mechanism (rounding errors compound) correct direction; confused "exponentiate" with additive accumulation; large-total / small-element precision floor understood after one worked example; correctly applied to price_series.cpp variance — no loss there | 2026-05-10 |
| 2026-05-03 | Log vs simple returns — additivity (W3 Day 3c) | Direction (time vs cross-section) retrieved unaided; ln product rule identity written correctly; cancellation of intermediate P₁ derived after one prompt; full mechanism clean by end | 2026-05-10 |

| 2026-05-14 | Member vs local `_simulator` — W6 Day 5 opening carry-forward | 2/2 unaided. Mechanism correct: local resets seed → identical paths; member maintains stream → independent estimates. One precision fix: "correlated" → "independent." **[FIRST TIME]** cleared without scaffolding. | 2026-05-21 |
| 2026-05-14 | Standard error — what SE measures | 1/2. First answer: "estimates" (close, one word short). After one prompt: SE = stdev of the *sample mean* — how much the MC price bounces across runs with different seeds. Payoff stdev vs SE of mean distinction confirmed. | 2026-05-21 |
| 2026-05-14 | Why divide by √N (CLT reason) | 0/2. Said "because distribution is wildly skewed" — wrong reason. Skewness explains large numerator (14.79); division by √N comes from CLT (sampling distribution of mean). Full explanation needed. | 2026-05-21 |
| 2026-05-14 | What does "3" in 3×SE mean | 0/2. Said "error halves every 2 decimal places" — confused with O(1/√N) convergence rate. Full explanation needed: 3-sigma from normal distribution, 99.73% coverage. | 2026-05-21 |
| 2026-05-14 | payoff_sq_sum accumulation — `p * p` | 1/2. First attempt: `(p-p)*(p-p)` (always zero — confused square-of-value with deviation-from-mean). One hint: "what is p squared?" → corrected to `p * p`. | 2026-05-21 |
| 2026-05-14 | Discounting stdev consistently | 2/2 unaided. Independently applied `* std::exp(-_r * _T)` to stdev return without prompting — recognized mean and stdev must be on the same scale. | 2026-05-21 |
| 2026-05-14 | Member vs local `_simulator` — W6 Day 5 closing check | 2/2 unaided. Self-corrected "correlated" → "independent" without prompting — improvement over opening answer. Clean sweep both ends of session. | 2026-05-21 |
| 2026-05-14 | Three roles of `*` — W6 Day 4 opening carry-forward | 3/3 clean. Declaration corrected: `double* p = &x`. **[FIRST TIME]** carry-forward cleared. | 2026-05-21 |
| 2026-05-14 | Member vs local variable — RNG state continuity | Articulated correctly: fresh local resets seed each call (same paths); member persists RNG state (independent path batches). | 2026-05-21 |
| 2026-05-14 | Three roles of `*` — W6 Day 4 closing check | 2/2 unaided. Identical to opening answer. Clean sweep both ends of session. | 2026-05-21 |
| 2026-05-14 | Three roles of `*` — W6 Day 3 retrieval | 3/3 clean. Declaration (`double* p`), read-dereference (`double q = *p`), write-dereference (`*p = 20.0`). "Pointer on left/right" shortcut noted. | 2026-05-21 |
| 2026-05-14 | `push_back` vs pre-initialized `counts[i]++` — W6 Day 3 retrieval | 2/2 — sharpest version yet. Fixed-size counter vector vs dynamic append. | 2026-05-21 |
| 2026-05-14 | Member initializer list syntax — W6 Day 3 retrieval | 2/2 **[FIRST TIME]** Correct after flagged failure in W6 Day 1. Values in `()`, not type names. | 2026-05-21 |
| 2026-05-14 | MC convergence O(1/√N) — first test | Concept landed. σ/√N recalled unaided. 4×N → half error derived correctly. 100× paths for 10× error reduction correct. Initial "exponential" intuition corrected to square root. | 2026-05-17 |
| 2026-05-14 | Three roles of `*` — closing retrieval check | 1/2. Roles named correctly; declaration example wrong: `double* p = 5.0` is a compile error (pointer holds address, not value). Opening answer same session had `&x` correct. Re-test: 2026-05-17 (carry-forward). | 2026-05-17 |

| 2026-05-13 | GBM formula from memory — W6 Day 2 opening re-test | Full credit. Structure correct; drift/shock split correct; `rt` notation ambiguity flagged (should be `r`, not `r*t`). | 2026-05-20 |
| 2026-05-13 | σ²/2 mechanism — W6 Day 2 re-test (opening) | 1/2. Named "log-normal asymmetry correction" correctly; needed numerical hint (e^0.1+e^-0.1)/2=1.005; then articulated full mechanism cleanly. | 2026-05-20 |
| 2026-05-13 | σ²/2 mechanism — W6 Day 2 closing check | 2/2 unaided. Full mechanism in one sentence without any hint: "e^x is convex — average of e^(+x) and e^(-x) exceeds 1; σ²/2 subtracts that excess so expected price growth stays at exactly r." [FIRST TIME fully unaided] | 2026-05-20 |
| 2026-05-13 | Call payoff `max(S_T - K, 0)` | Unaided. Retrieved correctly when prompted. | 2026-05-20 |
| 2026-05-13 | `#include` mechanics — preprocessor copy-paste | [FIRST TIME] Understood correctly from first principles without explanation. | 2026-05-20 |

| 2026-05-11 | Vector internals — opening W6 Day 1 retest | 3/3 unaided. Control block on stack (pointer, size, capacity); data on heap; destructor fires on scope exit, frees heap before stack wipe; no leak. | 2026-05-18 |
| 2026-05-11 | Memory leak mechanism — W6 Day 1 retest | 2/3. Mechanism and consequence correct; "OS cannot reclaim" sharpened to "runtime allocator cannot reclaim mid-run; OS only reclaims on process exit." | 2026-05-18 |
| 2026-05-11 | Member initializer list syntax | Partial — understood pattern; typed type names inside `()` instead of just values. Re-test: write constructor from scratch. | 2026-05-14 |
| 2026-05-11 | GBM formula — drift + shock structure | Understood with coaching; sigma=0 reduction correct unaided. Flagged weak — re-test write from memory. | 2026-05-14 |
| 2026-05-11 | Vector internals — closing retrieval check (same question as session open) | 2/2 unaided. Added RAII destructor point unprompted — key gain vs session open. "OS hasn't reclaimed" persists (same imprecision as morning); runtime allocator distinction still sticky. | 2026-05-18 |
| 2026-05-11 | σ asymmetry — opening carry-forward re-test (due 2026-05-11) | 2/2 unaided. Full mechanism: floor at 0 operative ("load bearing"), σ lifts both tails, asymmetric benefit → higher EV → higher call price. [FIRST TIME robust under pressure] | 2026-05-17 |
| 2026-05-11 | `push_back` vs pre-initialized `counts[i]++` — carry-forward re-test | 1/2 — mechanism correct (growth vs mutation); "raw values" said instead of "bin indices" — one precision sharpened | 2026-05-14 |
| 2026-05-11 | σ asymmetry — closing check (same session, reframed prompt) | 2/2 unaided. Word-for-word same mechanism as opening. [FIRST TIME] closing check clean — Day 4 closing had scored 1/2 | 2026-05-17 |

| 2026-05-10 | BS inputs + directions — spaced retest (due 2026-05-10, from W4 Day 1) | 5/5 unaided; σ asymmetry (downside floor) stated without prompting [FIRST TIME full reasoning] | 2026-05-17 |
| 2026-05-10 | BS inputs — closing check (directions + σ reason) | 1/2 — directions 5/5 unaided; σ reason dropped when asked explicitly; re-test Day 5 | 2026-05-11 |
| 2026-05-10 | Range-for vs index loop — when each applies | Unaided: range-for needs an existing collection; repeat-N needs an index | 2026-05-17 |
| 2026-05-10 | `push_back` vs pre-initialized `counts[i]++` | Distinction understood after one explanation | 2026-05-14 |

| 2026-05-08 | PV re-derive from scratch (week+4 spaced, W5 Day 3) | Formula recalled; coded correctly; `setprecision` bug self-diagnosed after one hint; assert tightened from `!= -1` to `> -1` after coaching | 2026-05-15 |
| 2026-05-08 | Three roles of `*` | [FIRST TIME] all three unaided — declaration, read-dereference, write-dereference | 2026-05-15 |
| 2026-05-08 | T& vs T* distinctions | All distinctions correct unaided; "static memory" framing corrected to stack/heap | 2026-05-15 |
| 2026-05-08 | Stack vs heap — concept intro | Labels initially swapped; corrected after explanation; vector internals (control block on stack, data on heap) understood correctly [FIRST TIME] | 2026-05-12 |
| 2026-05-08 | Memory leak mechanism + RAII motivation | Mechanism understood correctly; RAII as destructor-based cleanup understood as W6 foundation | 2026-05-12 |
| 2026-05-07 | W4 spaced retest — BS inputs + directional effects | σ direction wrong initially (said "down"); self-corrected after asymmetry coaching; r direction correct unaided [FIRST TIME] — W4 Day 1 needed correction | 2026-05-14 |
| 2026-05-07 | const-ref vs by-value — W2 spaced retest (overdue since 2026-05-02) | 1/1 unaided — [FIRST TIME] no scaffolding needed; prior session needed prompting | 2026-05-14 |
| 2026-05-07 | Pointers: `&`, `*`, address arithmetic, two-pointer aliasing | Address off-by-one corrected; write-dereference vs pointer-rebind confused initially, resolved cleanly; two-pointer aliasing correct unaided | 2026-05-14 |
| 2026-05-07 | References vs pointers — null, rebinding, syntax | Differences stated correctly unaided after explanation | 2026-05-14 |
| 2026-05-07 | `const&` — performance and safety | "no copy + read-only promise" retrieved correctly; O(1) framing sharpened to "no allocation" | 2026-05-14 |
| 2026-05-07 | RNG seeding — purpose and reproducibility | Reasoned from first principles without knowing the term — [FIRST TIME] unaided | 2026-05-14 |

| 2026-05-21 | Stationarity — why prices are non-stationary (due 2026-05-22, tested one day early) | 2/2 after one build-up question (opening). Closing check: 2/2 unaided — "prices trend and bounce around, so the mean of a given time period is completely different to that of a different one, whereas log returns represent the same rate of change regardless of price level." Improved from 1/2 at introduction. Carry-forward cleared. | — |
| 2026-05-21 | σ asymmetry precision — "expected payoff scales with distance past K" | 1.5/2. Mechanism correct; still saying "probability of ending ITM" instead of "expected payoff scales with distance past K." Same error as W7D3. | 2026-05-22 |
| 2026-05-21 | `break`/`continue` use-case — CSV context | 2/2. "continue because 1 bad row doesn't make the input invalid." Clean. **Carry-forward cleared.** | — |
| 2026-05-21 | RNG state continuity — local vs member `_simulator` | 1.5/2. Mechanism correct (local resets seed → same paths each call; member persists state). Said "correlated" instead of "identical." Same precision error as W6D5. | 2026-05-22 |
| 2026-05-21 | Range-for vs index loop — applied in code | Error in first attempt: used range-for to index into vector (`price_vec[i+1]` where `i` is a `double`). Self-corrected after one question. Concept retrieved correctly (2/2) but not yet solid in code. | 2026-05-28 |

| 2026-05-19 | Stream-as-bool opening re-test (W7D1 scored 0/2) | 1/2 — mechanism correct (bool conversion, true=success, false=EOF/error); missed that `getline` returns the stream; one hint needed | — |
| 2026-05-19 | Stream-as-bool closing check | 2/2 unaided — "`getline` returns the stream itself; `while` converts to bool — true if last read succeeded, false if EOF or error." Full answer, no prompting. **Carry-forward cleared.** | — |
| 2026-05-19 | npos+1 overflow chain — why BADROW printed twice | 2/2 unaided — correct mechanical trace: npos `continue` missing → falls through → npos+1 wraps → substr(0) → stod throws → catch fires | — |
| 2026-05-19 | `continue` structural rule: top-of-body vs. end-of-body | 0/2 — said "before the mean calculation" (mean is outside the loop); full explanation needed | 2026-05-21 |

| 2026-05-19 | `continue` structural rule — W7D3 retest | 1/2 opening (mechanism only) → 2/2 after applying to csv_loader.cpp. npos guard = load-bearing; end-of-catch = redundant. **Carry-forward cleared.** Closing check: 2/2 unaided — same answer delivered cleanly end-of-session. | — |
| 2026-05-19 | MC convergence O(1/√N) — spaced retest (overdue 2026-05-17) | 2/2 unaided. CLT → SE = stdev/√N → 4×N halves error. Derived from first principles. **Carry-forward cleared.** | — |
| 2026-05-19 | Range-for vs index loop — spaced retest (overdue 2026-05-17) | 2/2 after coaching. Initially reversed examples. Corrected to: range-for needs existing collection; index loop when no collection (repeat-N). **Carry-forward cleared.** | — |
| 2026-05-19 | BS inputs + directions — spaced retest (overdue 2026-05-17) | 5/5 unaided. All five inputs and directions correct. **Carry-forward cleared.** | — |
| 2026-05-19 | σ asymmetry precision — "probability vs distance past K" | 1/2. Floor + unlimited upside mechanism correct. "Probability of reaching strike" corrected to "expected payoff scales with distance past K." | 2026-05-21 |
| 2026-05-19 | `\n` vs `/n` vs `endl` — spaced retest (was 0/2 on 2026-05-18) | 2/2. "clears" → "flushes" for `endl` corrected. **Carry-forward cleared.** | — |
| 2026-05-19 | Stationarity — why returns not prices | 1/2. Reached "mean/variance stable for returns" after one coaching pass. Term "stationarity" introduced. **[FIRST TIME]** | 2026-05-22 |
| 2026-05-19 | `>>` vs `getline` delimiter difference | Introduced. `>>` splits on all whitespace; `getline` reads to `\n`. **[FIRST TIME]** | 2026-05-22 |

| 2026-05-18 | SE / CLT — carry-forward re-test (was 0/2 W6D5) | 1/2 opening. Closing check: 2/2 unaided. Skewness → large numerator (14.79); CLT → √N division; SE = spread of sample means. Causal chain clean. Carry-forward cleared. | — |
| 2026-05-18 | Stream-as-bool loop condition | 0/2. Said "returns npos." Corrected: `getline` returns the stream; stream converts to bool based on last operation state. | 2026-05-21 |
| 2026-05-18 | `\n` escape vs `/n` literal vs `endl` | 0/2. Said `"/n"` prints newline; said fix is `endl`. Corrected: `"/n"` is literal `/n`; `"\n"` is newline escape; `endl` = newline + flush (slower). | 2026-05-21 |
| 2026-05-18 | `break` vs `continue` — mechanics | 2/2. Break exits loop; continue skips to next iteration. Both correct. | 2026-05-25 |
| 2026-05-18 | `break` vs `continue` — CSV use-case | 1/2. Said break is right for "reporting" — corrected: reporting is a print statement (independent); `continue` is right for CSV (one bad row shouldn't discard the rest). | 2026-05-21 |
| 2026-05-18 | `std::stod` — meaning and return type | 2/2 unaided. "String to double"; returns `double`. **[FIRST TIME]** | 2026-05-25 |

| 2026-05-21 | σ asymmetry — W7 D5 opening retrieval | 1/2. "Expected payoff scales with distance past K" correct; needed one coaching pass to add the asymmetry mechanism (floor at 0, upside unbounded). | — |
| 2026-05-21 | σ asymmetry — W7 D5 closing check | 1/2. Identical partial answer: "expected payoff scales with distance past K, benefits S_T − K." Floor at 0 / upside-only asymmetry mechanism absent again. Same gap as opening. Carry-forward to W8 D1. | 2026-05-22 |

| 2026-05-22 | `>>` vs `getline` — opening retrieval (carry-forward due today) | 1/2 — described optional 3-arg form of `getline` rather than default `\n` behavior; answered `\n` correctly after one follow-up. | — |
| 2026-05-22 | σ asymmetry — carry-forward (due today): floor at 0 + payoff scales with distance past K | 2/2 unaided — full mechanism on first attempt. **Carry-forward cleared.** | — |
| 2026-05-22 | RNG state continuity — carry-forward (due today): local vs member `_simulator` | 2/2 unaided — "identical" immediately; no "correlated" error. **Carry-forward cleared.** | — |
| 2026-05-22 | Historical simulation method — identified from hint | 1/2 — said "no idea"; after "most direct possible way using raw data" hint answered correctly. | — |
| 2026-05-22 | Historical simulation weakness — tail data sparsity | 1/2 — initially described a strength; after coaching (different 2-year windows) reached "bounded by what happened" and "5 data points at 99%." | — |
| 2026-05-22 | Parametric VaR assumption violation — fat tails | 1/2 — said growth bias first (that's in μ); corrected to fat tails after the term was provided. | — |
| 2026-05-22 | Parametric VaR at 99%: direction of error | 2/2 unaided — "too low compared to real equity returns due to thin tails." | — |
| 2026-05-22 | 95% VaR index in 500 sorted returns | 1/2 — gave range 0–24; after "VaR is a single threshold" prompt answered index 24 correctly. | — |
| 2026-05-22 | 99% VaR index in 500 sorted returns | 2/2 unaided — index 4, 5 observations. | — |
| 2026-05-22 | `>>` vs `getline` — closing retrieval check | 2/2 unaided — "`getline` uses `\n`, `>>` uses all whitespace; `>>` fragments the row, `getline` hands you the whole row." **[FIRST TIME]** fully unaided; was 1/2 at session open. | — |

| 2026-05-22 | GBM formula — drift + shock notation (W6 spaced rep, overdue 2026-05-20) | 1/2 — wrote (σ/2)² not σ²/2; self-corrected after "expand that algebraically" coaching step. | 2026-05-23 |
| 2026-05-22 | VaR index arithmetic — 95% and 99% for 500 returns (W8D1 closing check retested) | 2/2 unaided — index 24 and index 4, both immediate. Improvement from W8D1 where 95% needed one coaching step. | — |
| 2026-05-22 | Fat tails closing check — parametric VaR understates tail risk at 99% | 2/2 unaided — "real equity returns have fat tails so parametric VaR understates tail risk, too low at 99%." | — |

## Blockers / questions parked for later
- (none yet)
