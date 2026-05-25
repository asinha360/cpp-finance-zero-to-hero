# cpp-finance-zero-to-hero

A 16-week self-study curriculum: zero coding background to employable-level C++ for quantitative finance.

Every week produces a runnable C++ artifact — a pricer, a backtester, a market-data parser — built from scratch, reviewed as a senior would review it, and tested against acceptance criteria before moving on.

---

## Goal

By week 16: three polished GitHub portfolio projects demonstrating pricing, risk modelling, and market-microstructure topics that could survive a quant developer interview.

By week 4 (complete): write, compile, and debug a Black-Scholes pricer from scratch.

By week 8 (complete): build a Monte Carlo VaR model on real historical data.

---

## Curriculum

| Week | Topic | Artifact | Status |
|------|-------|----------|--------|
| 1 | Toolchain; present-value calculator | [projects/week01/pv.cpp](projects/week01/pv.cpp) | Complete |
| 2 | Functions + control flow; bond pricer | [projects/week02/bond_pricer.cpp](projects/week02/bond_pricer.cpp) | Complete |
| 3 | Collections + summary statistics; returns stats tool | [projects/week03/price_series.cpp](projects/week03/price_series.cpp) | Complete |
| 4 | **Milestone 1** — Black-Scholes pricer with delta and vega | [projects/week04/bs_pricer.cpp](projects/week04/bs_pricer.cpp) | Complete |
| 5 | Memory model (stack/heap, pointers, references); normal RNG harness | [projects/week05/rng_harness.cpp](projects/week05/rng_harness.cpp) | Complete |
| 6 | Classes + RAII; GBM Monte Carlo option pricer | [projects/week06/mc_pricer.h](projects/week06/mc_pricer.h) | Complete |
| 7 | File I/O; CSV loader + returns summary | [projects/week07/csv_loader.cpp](projects/week07/csv_loader.cpp) | Complete |
| 8 | **Milestone 2** — Monte Carlo VaR on real historical data | [projects/week08/var_model.cpp](projects/week08/var_model.cpp) | Complete |
| 9 | STL containers + algorithms; OHLC bar aggregator | — | Not started |
| 10 | Polymorphism; SMA-crossover strategy | — | Not started |
| 11 | Limit order book with matching engine | — | Not started |
| 12 | **Milestone 3** — order-book replay backtester | — | Not started |
| 13 | Performance: profiling + variance reduction | — | Not started |
| 14 | Parallelism; parallel Monte Carlo pricer | — | Not started |
| 15 | CMake + GoogleTest + repo hygiene | — | Not started |
| 16 | **Milestone 4** — 3 polished portfolio repos | — | Not started |

---

## Artifacts built so far

### Week 1 — Present-value calculator
`projects/week01/pv.cpp`

Computes PV = FV / (1+r)^n. Derived from first principles before writing a line of code. Guards against r = -1 (division by zero). Acceptance criteria: compiles clean under `-Wall -Wextra -std=c++20`, prints `863.84` for the spec input, exits with code 1 on bad input.

### Week 2 — Bond pricer
`projects/week02/bond_pricer.cpp`

Prices a fixed-coupon bond: sum of discounted coupon payments plus discounted face value. Distinguishes coupon rate `r` from yield `y`. Guards against degenerate inputs. Acceptance criteria: F=1000, r=0.05, y=0.05, n=5 → 1000.00 (par); y=0.06 → 957.88 (below par).

### Week 3 — Returns statistics tool
`projects/week03/price_series.cpp`

Computes arithmetic and log returns from a price series; calculates mean, sample variance (Bessel-corrected, n−1), and standard deviation. Output verified against a Python reference to 4 decimal places.

Also includes `projects/week04/bond_pricer_ytm.cpp`: YTM solver using bisection — the first numerical root-finding algorithm in the curriculum.

### Week 4 — Black-Scholes pricer (Milestone 1)
`projects/week04/bs_pricer.cpp`

Full Black-Scholes call and put pricer. Includes:
- `compute_d1` / `compute_d2` helpers (no duplication across callers)
- Delta: N(d1)
- Vega: S * sqrt(T) * phi(d1)
- Put-call parity assertion across 20 varied input sets (ITM, OTM, ATM; T from 1 to 20; sigma from 0.1 to 0.9) — all pass at tolerance 1e-10

### Week 5 — Normal RNG harness
`projects/week05/rng_harness.cpp`

Generates N(0,1) samples using `std::mt19937` + `std::normal_distribution`. Acceptance criteria: mean in [-0.005, 0.005], standard deviation in [0.995, 1.005], same seed reproduces byte-for-byte. Both criteria green.

### Week 6 — GBM Monte Carlo option pricer
`projects/week06/mc_pricer.h` / `mc_pricer.cpp` (plus `normal_sampler.h/.cpp`, `gbm_simulator.h/.cpp`)

Three classes across a header/source split:
- `NormalSampler` — wraps `mt19937` + `normal_distribution`; seeded at construction; RNG state persists across calls
- `GBMSimulator` — simulates one GBM path: S(t+dt) = S(t) · exp((r − σ²/2)·dt + σ·√dt·Z). GBM (geometric Brownian motion) is the standard model for stock price paths under the Black-Scholes assumptions.
- `MCPricer` — runs N paths, returns `std::pair<double,double>` (discounted mean payoff, discounted stdev). At N=100,000: price 10.4384 inside 3-SE band [10.2802, 10.5609] containing BS closed form 10.4502.

Zero warnings under `-Wall -Wextra -std=c++20`. No raw `new`/`delete` (RAII throughout). Acceptance criteria: MC price inside 3-SE convergence band, exit 0 — both green.

### Week 7 — CSV loader + returns summary
`projects/week07/csv_loader.cpp`

Reads a CSV of `date,price` rows from disk, skips malformed rows (missing comma, non-numeric price), accumulates valid prices into a `std::vector<double>`, and computes mean price, log returns, and standard deviation. Key mechanisms:
- `std::ifstream` + `std::getline` as a loop condition (stream-to-bool conversion); `find`/`substr` tokenization
- `std::stod` for string-to-double conversion; `try/catch` on `std::invalid_argument` per row so one bad row does not abort the parse
- Empty-vector guard: `if (!price_vec.empty())` before division; bad rows reported to `std::cerr`

Output verified against a Python reference to 7 significant figures (mean 0.000932505, stdev 0.0143042). Zero warnings under `-Wall -Wextra -std=c++20`.

### Week 8 — Monte Carlo VaR model (Milestone 2)
`projects/week08/var_model.cpp` / `var_model.h`, `csv_loader.h/.cpp`, `normal_sampler.h`

Three-method VaR (Value at Risk) implementation on real historical price data. VaR answers: "what is the minimum loss that will be exceeded only X% of the time?"

- **Historical simulation** — sorts actual log returns, reads off the percentile index directly. No distribution assumption; bounded by what actually happened.
- **Parametric VaR** — models returns as N(μ, σ) and computes μ + z·σ where z = −1.645 (95%) or −2.326 (99%). Closed-form; underestimates tail risk for real equity data because equity returns have fat tails.
- **Monte Carlo VaR** — draws 100,000 samples from N(μ, σ) using the `NormalSampler` from Week 6, sorts, reads off percentile index.

Calibrated on 350 returns (70%); tested on the remaining 150 out-of-sample returns.

**Calibration-window VaR thresholds at 95%/99%:**
| Method | 95% VaR | 99% VaR |
|---|---|---|
| Historical | −0.02591 | −0.03470 |
| Parametric | −0.02390 | −0.03431 |
| Monte Carlo | −0.02390 | −0.03438 |

**Out-of-sample exceedance frequencies (target: 5.0% / 1.0%):**
| Method | 95% | 99% |
|---|---|---|
| Historical | 4.6% | 1.2% |
| Parametric | 6.2% | 1.2% |
| Monte Carlo | 6.2% | 1.2% |

Parametric overshoots at 95% (fat tails — normal distribution sets the threshold too shallow). Historical undershoots at 95% (calibration window was more volatile than the test window; threshold is too conservative).

Acceptance tests (assert-based): 99% VaR more negative than 95% VaR for all three methods ✓; all exceedance rates within [0%, 15%] ✓. Zero warnings under `-Wall -Wextra -std=c++20`.

Defensive guards (added in code review): `load_prices` asserts on file-open failure before any stream reads with the actual filepath in the error message; VaR index arithmetic uses signed `int` (not `size_t`) to prevent unsigned wrap on small inputs.

---

## Method

**Project-based.** Every week ends with a runnable artifact, not a worksheet.

**Retrieval practice.** Concepts are re-tested from memory at spaced intervals (48h, 1 week, 1 month). Scores are logged in [PROGRESS.md](PROGRESS.md). If it can't be recalled without the notes, it doesn't count as learned.

**Derive before implement.** The math behind each tool — PV formula, bond pricing, Black-Scholes — is worked out on paper first. Code is written to express a derivation, not to copy a template.

**Reviewed as production code.** Each artifact goes through a code review before the week closes: silent error returns, duplication, guard placement, test coverage. Bugs are fixed before moving on.

---

## Compile any artifact

All files use the same flags:

```bash
g++ -Wall -Wextra -std=c++20 projects/weekNN/artifact.cpp -o artifact && ./artifact
```

No external dependencies. Standard library only through week 15.

---

## Workspace structure

| File | Purpose |
|---|---|
| [CONTEXT.md](CONTEXT.md) | Project purpose, success criteria, what to avoid |
| [TASKS.md](TASKS.md) | Current task board (now / next / done / blocked) |
| [PROGRESS.md](PROGRESS.md) | Week-by-week ledger, milestones, retrieval-practice scores |
| [DECISIONS.md](DECISIONS.md) | Log of non-trivial choices with reasoning |
| [ASSUMPTIONS.md](ASSUMPTIONS.md) | Assumptions flagged during execution |
| [CLAUDE.md](CLAUDE.md) | Durable operating rules for the AI collaborator |
| [notes/](notes/) | Per-session learning notes |
| [projects/](projects/) | Weekly artifacts (source + compiled binaries) |
| [templates/](templates/) | Retrospective, task-prompt, decision templates |
