# curriculum.md — 16-Week C++ for Quant Finance

Designed by Claude acting as **Project Architect + Learning Coach** per [AGENTS.md](AGENTS.md).
Grounded in [CONTEXT.md](CONTEXT.md) (goals, constraints, pedagogical commitments) and labeled per [REFERENCES.md](REFERENCES.md) §7.

## Pedagogical framing (verification labels per [REFERENCES.md](REFERENCES.md))

- `[UNVERIFIED PLACEHOLDER]` **Ebbinghaus forgetting curve** — rationale for spacing reviews at widening intervals (24h, 72h, 7d, 21d). Primary source not read this session; queued in [REFERENCE_RESEARCH_QUEUE.md](REFERENCE_RESEARCH_QUEUE.md).
- `[UNVERIFIED PLACEHOLDER]` **Karpicke — retrieval practice / testing effect**: recalling beats re-reading. Basis for weekly retrieval prompts.
- `[UNVERIFIED PLACEHOLDER]` **Ericsson — deliberate practice**: targeted reps at the edge of ability with immediate feedback. Basis for weekly acceptance tests + code-review loop.
- `[UNVERIFIED PLACEHOLDER]` **Project-based learning** — one runnable artifact per week; knowledge demonstrated, not claimed.
- `[UNVERIFIED PLACEHOLDER]` **Rohrer & Taylor — interleaving** improves transfer vs. blocked practice. Used in retrieval prompts that mix prior weeks' concepts.

No statistics, effect sizes, or study results are cited. Labels upgrade to `[VERIFIED]` only after primary sources are read.

## Spacing schedule (applied every week)

- Retrieval prompts each week cover: **current week + prior week + one earlier week** (interleaved).
- Re-implement-from-scratch challenges recur at **week + 4** intervals (W5 re-derives W1, W9 re-derives W5, etc.).

## Milestone map (from [CONTEXT.md](CONTEXT.md))

- **W4** → Black-Scholes pricer
- **W8** → Monte Carlo VaR on real data
- **W12** → Order-book replay backtester
- **W16** → 3 polished GitHub portfolio projects

---

## Curriculum

| Week | Learning goals | Project (runnable artifact) | Math / finance concept | C++ concept | Retrieval-practice prompts | Acceptance test |
|------|----------------|-----------------------------|------------------------|-------------|----------------------------|-----------------|
| 1 | Toolchain works; write, compile, debug a trivial program | Present-value calculator for a single cashflow | Time value of money; discounting | `main`, types (`int`, `double`), `iostream`, compile with `g++ -Wall -Wextra -std=c++20`, step through in debugger | (a) Derive PV formula from first principles on paper. (b) Why is `double` not `float` here? (c) What does `-Wall` catch that the compiler would otherwise miss? | Given `FV=1000, r=0.05, n=3`, program prints `863.84` (±0.01). Debugger breakpoint hits on the discount line. |
| 2 | Decompose logic into functions; use loops and conditionals | Bond pricer: sums coupon PVs + par PV given a coupon schedule | Coupon bond pricing; discrete vs. continuous compounding | Functions, parameters by value vs. reference, `for`/`while`, `if`/`else`, header/source split | (a) Re-derive PV from W1 without looking. (b) Why pass `std::vector` by const-ref, not by value? (c) Interleave: what happens to a bond's price when `r` rises? | 5-year 5% annual bond at `r=0.05` prices to 100.00 ±0.01; at `r=0.06` prices below 100. Unit test file runs and passes. |
| 3 | Work with collections; compute summary statistics | Historical returns stats tool: reads hardcoded price series, outputs mean, variance, stdev | Arithmetic vs log returns; sample mean/variance; why n−1 | `std::vector`, range-for, `<numeric>` (`accumulate`, `inner_product`), `<cmath>` | (a) Re-implement W2 bond pricer from scratch (spaced re-derive). (b) When does `accumulate` with `double` lose precision? (c) Why log returns for compounding but simple returns for cross-section? | Matches hand-computed mean/variance on a 10-point series to 1e-9. Handles n=1 without crashing (documented behavior). |
| 4 | **MILESTONE 1**: write, compile, debug Black-Scholes from scratch | Black-Scholes European call/put pricer with Δ, ν (vega) | BS PDE intuition; N(d1), N(d2); put-call parity | Composing functions; `std::erf`/`std::erfc` for normal CDF; basic assert-based unit tests | (a) Without notes, re-derive `d1`, `d2`. (b) Interleave: extend your W2 bond pricer to output yield to maturity numerically. (c) What breaks if `σ=0` or `T=0`? | Call(S=100,K=100,r=0.05,σ=0.2,T=1) ≈ 10.45 ±0.01. Put-call parity holds to 1e-10 across 20 random inputs. |
| 5 | Memory model; pass-by-reference; first RNG | Normal RNG harness: draws N samples, prints histogram, χ² against N(0,1) | Random variables; CLT intuition; standard normal | Pointers vs. references; `const` correctness; `<random>` (`mt19937`, `normal_distribution`); seeding | (a) Re-implement W1 PV calculator from memory (spaced re-derive, week+4). (b) Why seed the RNG explicitly for reproducibility? (c) What's the difference between `T&` and `T*`? | 1M samples: sample mean in [-0.005, 0.005], stdev in [0.995, 1.005]. Same seed reproduces same output byte-for-byte. |
| 6 | Encapsulation with classes; RAII | GBM path simulator → Monte Carlo European option pricer | Geometric Brownian motion; Itô intuition (stated, not derived); MC convergence at O(1/√n) | `class`, constructors/destructors, member vs. free functions, header guards | (a) Interleave: compare MC price at N=10k, 100k, 1M against W4 BS closed form. (b) Why does RAII matter for a file handle or RNG seed? (c) Re-derive put-call parity from W4. | MC call price converges to W4 BS value within 3 × (stdev/√N) at N=100k. Class has no raw `new`/`delete`. |
| 7 | File I/O; parse real data | CSV loader + returns summary on real daily price data (place a SPY-style CSV in `data/`) | Log returns on real series; basic missingness / weekend gaps | `<fstream>`, `std::string`, `std::getline`, simple tokenization, error handling on bad rows | (a) Re-implement W3 stats tool from scratch (spaced, week+4). (b) What goes wrong if you read the file with `>>` into a string? (c) Why do returns, not prices, get analyzed? | Loads a 1000-row CSV, skips/reports malformed rows, outputs mean/stdev matching a reference value computed in Python/Excel to 1e-6. |
| 8 | **MILESTONE 2**: Monte Carlo VaR on real historical data | MC VaR model: historical + parametric + MC at 95% and 99% | VaR definition; historical vs. parametric vs. MC; why tails matter | Composition of W5–W7; separating I/O from compute; writing first proper unit-test file | (a) Without notes, explain the three VaR methods. (b) Interleave: price a deep-OTM call with W6 MC — why does variance blow up? (c) What assumption of parametric VaR does real SPY data violate? | On 2+ years of real data, the three methods agree within documented tolerance bands; 99% VaR > 95% VaR; empirical exceedance frequency on out-of-sample window is reported and sanity-checked. |
| 9 | Pick the right STL container; iterators; `<algorithm>` | Tick-data → OHLC bar aggregator (1-minute bars from a tick CSV) | Time-series bucketing; OHLC semantics; why bar close ≠ last trade in the next bar | `std::map` vs. `unordered_map`, `std::sort`, `std::lower_bound`, iterators, lambdas | (a) Re-implement W5 RNG histogram from scratch (spaced, week+4). (b) When does `unordered_map` beat `map` and vice versa? (c) Interleave: apply W3 stats to bar closes. | Given a synthetic tick stream with known OHLC per minute, output matches exactly for 100 bars. Runs on 1M ticks in < 2 s on your laptop. |
| 10 | Polymorphism via interfaces | Strategy interface + SMA-crossover strategy run on W9 bars | Moving averages; look-ahead bias; signal vs. position | Abstract base class, `virtual`, `override`, `std::unique_ptr` | (a) Interleave: price the underlying of your strategy with W4 BS at each signal date. (b) Why is slicing a bug, not a feature, in C++? (c) Re-derive W4 put-call parity. | Strategy produces deterministic signals on a fixed bar series; replacing SMA with a dummy "always flat" strategy yields zero trades without changing the runner. |
| 11 | Build a limit order book | In-memory LOB with add / cancel / modify / match (price-time priority) | Bid/ask, spread, price-time priority; market vs. limit orders | Nested containers (`std::map<Price, std::list<Order>>`), references into containers, iterator invalidation | (a) Re-implement W7 CSV loader from scratch (spaced, week+4). (b) What breaks if you store `Order*` instead of `Order` in the list? (c) Interleave: compute spread time series using W3 stats. | Scripted sequence of 20 events (adds/cancels/trades) produces exact expected fills and final book state. No iterator-invalidation crashes under fuzz. |
| 12 | **MILESTONE 3**: order-book replay backtester | Replay backtester: feeds historical events → W11 LOB → W10 strategy → P&L | Slippage, fills, basic P&L attribution (realized vs. unrealized) | Event loop, clean separation of data/engine/strategy, `std::chrono` timestamps | (a) Without notes, explain your whole pipeline W9→W10→W11→W12. (b) What's the single biggest source of look-ahead bias in your code? (c) Interleave: apply W8 VaR to the backtest P&L series. | Deterministic output on a fixed event file; swapping the strategy changes P&L but not fill mechanics; a known-bad "peek at next bar" strategy is caught by a look-ahead-bias check. |
| 13 | Performance: measure, then optimize | Optimized W8 MC VaR — benchmark before/after | Big-O applied to MC; variance reduction (antithetic variates) | `std::chrono` timing, `-O2`/`-O3`, move semantics, avoiding unnecessary copies, `reserve()` | (a) Re-implement W9 bar aggregator from scratch (spaced, week+4). (b) Why is "optimize without measuring" an anti-pattern? (c) What does antithetic variates do to variance and why? | ≥2× speedup on same accuracy, documented with before/after timing and flamegraph-or-equivalent notes. Antithetic run achieves same CI width at < half the paths. |
| 14 | Parallelism without breaking correctness | Parallel MC pricer using `std::async` / thread pool | Independent paths = embarrassingly parallel; why RNG seeding matters per thread | `std::thread`, `std::async`, `std::mutex` (and when not to use it), per-thread RNG | (a) Interleave: parallelize W13 VaR. (b) What's a data race and how would you spot one in your code? (c) Re-derive MC convergence rate from W6. | Parallel result matches serial to 1e-10 with deterministic per-thread seeding. Near-linear speedup to the core count of your machine. |
| 15 | Professional polish: build system + tests + repo hygiene | CMake build + test suite covering W4, W8, W12; clean Git history on all three | Regression testing vs. analytic benchmarks; what "done" means | `CMakeLists.txt`, test target, `assert` or GoogleTest, Git basics (branches, meaningful commits) | (a) Without notes, list every public function in your BS pricer and one test for each. (b) Why is CI valuable even for a solo project? (c) Re-implement W11 LOB skeleton from scratch. | `cmake --build && ctest` runs green on a clean clone. README on each project lets a stranger build and run in < 5 minutes. |
| 16 | **MILESTONE 4**: portfolio ready for interviews | 3 polished GitHub repos (BS pricer, MC VaR, LOB backtester) with READMEs, demos, a 200-word rationale each | What makes a quant-dev portfolio credible: reproducibility, correctness checks, honest limits | Repo hygiene; writing READMEs a reviewer can act on; demo scripts | (a) For each repo, pitch it in 90 seconds out loud — record yourself. (b) For each repo, list one known limitation honestly. (c) Interleaving final: answer a mixed quiz of 10 questions drawn randomly from W1–W15. | An outside reader (or Claude acting as Code Reviewer per [AGENTS.md](AGENTS.md) §4) can clone, build, run the demo, and identify the project's purpose within 5 minutes per repo. |

---

## Weekly rhythm (8 hrs/week)

- **Day 1 (2h)** — concept intro + guided derivation on paper.
- **Day 2 (2h)** — first implementation attempt, solo, no Claude code output.
- **Day 3 (1h)** — retrieval-practice prompts, written, closed-book.
- **Day 4 (2h)** — code review with Claude as Code Reviewer (per [AGENTS.md](AGENTS.md) §4); fix blocking issues.
- **Day 5 (1h)** — acceptance-test run, update [TASKS.md](TASKS.md), retrospective in `templates/retrospective-template.md`.

## Next step

Do NOT start teaching Week 1 from this file. When you're ready to begin, say so — I'll switch into Learning Coach mode and run the Week 1 Day 1 concept intro.
