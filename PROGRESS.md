# PROGRESS.md

## Current state
## Next session

**First action:** W6 Day 2 — solo implementation of MC option pricer using GBMSimulator. Before new content, re-test: member initializer list syntax (write constructor from scratch); GBM formula (write from memory, identify drift vs shock). Jensen's inequality introduction when simulating paths.
**Retrieval question (opening W6 Day 2):** "Write the GBM one-step formula from memory. Which part is deterministic and which is random, and why is σ²/2 in the drift term?"
**Carry-forwards into W6 Day 2:** Jensen's inequality (deferred from W4 Day 3); `push_back` vs pre-initialized increment re-test due 2026-05-14; "runtime allocator cannot reclaim mid-run" (not "OS") — sticky imprecision, re-test at open.

---

- **Today's date:** 2026-05-11
- **Curriculum week:** 6 of 16 — **In progress (Day 1 complete)**
- **Days into curriculum:** 12 (calendar) / 23 sessions complete
- **Schedule status:** On track
- **Next milestone:** Week 8 — Monte Carlo VaR on real historical data
- **Today's artifact:** [notes/w6_d1.md](notes/w6_d1.md) | [projects/week06/normal_sampler.cpp](projects/week06/normal_sampler.cpp) | [projects/week06/gbm_simulator.cpp](projects/week06/gbm_simulator.cpp)

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
| 6 | Classes + RAII; GBM MC option pricer | **In progress** | 2026-05-11 | — | [projects/week06/gbm_simulator.cpp](projects/week06/gbm_simulator.cpp) | — |
| 7 | File I/O; CSV loader + returns summary | Not started | — | — | — | — |
| 8 | **MILESTONE 2** — Monte Carlo VaR on real data | Not started | — | — | — | — |
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

## Blockers / questions parked for later
- (none yet)
