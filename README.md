# cpp-finance-zero-to-hero

A 16-week self-study curriculum: zero coding background to employable-level C++ for quantitative finance.

Every week produces a runnable C++ artifact — a pricer, a backtester, a market-data parser — built from scratch, reviewed as a senior would review it, and tested against acceptance criteria before moving on.

---

## Goal

By week 16: three polished GitHub portfolio projects demonstrating pricing, risk modelling, and market-microstructure topics that could survive a quant developer interview.

By week 4 (already done): write, compile, and debug a Black-Scholes pricer from scratch.

---

## Curriculum

| Week | Topic | Artifact | Status |
|------|-------|----------|--------|
| 1 | Toolchain; present-value calculator | [projects/week01/pv.cpp](projects/week01/pv.cpp) | Complete |
| 2 | Functions + control flow; bond pricer | [projects/week02/bond_pricer.cpp](projects/week02/bond_pricer.cpp) | Complete |
| 3 | Collections + summary statistics; returns stats tool | [projects/week03/price_series.cpp](projects/week03/price_series.cpp) | Complete |
| 4 | **Milestone 1** — Black-Scholes pricer with delta and vega | [projects/week04/bs_pricer.cpp](projects/week04/bs_pricer.cpp) | Complete |
| 5 | Memory model (stack/heap, pointers, references); normal RNG harness | [projects/week05/rng_harness.cpp](projects/week05/rng_harness.cpp) | Complete |
| 6 | Classes + RAII; GBM Monte Carlo option pricer | [projects/week06/mc_pricer.h](projects/week06/mc_pricer.h) | In progress (Day 4 complete) |
| 7 | File I/O; CSV loader + returns summary | — | Not started |
| 8 | **Milestone 2** — Monte Carlo VaR on real historical data | — | Not started |
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

### Week 6 — GBM Monte Carlo option pricer (in progress)
`projects/week06/mc_pricer.h` / `mc_pricer.cpp`

Three classes:
- `NormalSampler` — wraps `mt19937` + `normal_distribution`; seeded at construction
- `GBMSimulator` — simulates one GBM path: S(t+dt) = S(t) · exp((r − σ²/2)·dt + σ·√dt·Z). GBM (geometric Brownian motion) is the standard model for stock price paths under the Black-Scholes assumptions.
- `MCPricer` — runs N paths, computes mean discounted payoff max(S_T − K, 0). At N=100,000: price 10.4384 vs Black-Scholes closed form 10.45 — within convergence band.

All three headers compile clean under `-Wall -Wextra -std=c++20`. No raw `new`/`delete` (RAII throughout).

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
