# DECISIONS.md

Non-trivial choices, one entry each. Date, decision, reason, what would flip it.

---

## 2026-04-18 — Toolchain picks for the 16-week curriculum

**Context.** User is non-technical on macOS (Apple Silicon assumed — see [ASSUMPTIONS.md](ASSUMPTIONS.md)). Setup needed to be minimal, native, and free. See [setup.md](setup.md) for the full install guide.

**Decisions (one line each):**

- **Compiler: Apple Clang via Xcode Command Line Tools** (not Homebrew GCC). Reason: ships with macOS tooling, supports C++20, provides `g++` alias so curriculum commands work unchanged, bundles `lldb` and `git`. Flip if: we hit a GCC-only feature or Clang bug that blocks a week.
- **Debugger: `lldb` + VS Code CodeLLDB extension** (not `gdb`). Reason: `lldb` is the native Apple debugger; `gdb` needs code-signing workarounds on macOS. Flip if: we switch editors away from VS Code.
- **Editor: VS Code** (not Xcode, CLion, Vim, Emacs). Reason: gentlest learning curve for a non-coder, free, cross-platform, strong C++ + debugger extensions. Flip if: user wants a JetBrains workflow later.
- **Package manager: Homebrew** (not MacPorts, Nix, manual). Reason: de-facto standard on macOS, one-line installs, works on Apple Silicon and Intel. Flip if: we need reproducible builds across machines (then Nix).
- **Build system: plain `g++` invocations weeks 1–14, CMake from W15.** Reason: introducing CMake on day 1 would teach a second tool before the first one makes sense; project artifacts are single-file through W14. Flip if: we cross the multi-file threshold earlier than expected.
- **Test framework: `assert` weeks 1–14, GoogleTest from W15.** Reason: same rationale — one tool at a time. Flip if: we need parameterised tests earlier.
- **C++ standard: C++20** (not C++17 or C++23). Reason: curriculum already specifies `-std=c++20`; modern enough for ranges/concepts if useful; broadly supported by shipping Apple Clang. Flip if: Apple Clang version shipped with user's macOS doesn't fully support C++20 features we need.
- **GitHub (not GitLab/Bitbucket).** Reason: recruiters browse GitHub; milestone-4 portfolio lives there. Free tier is enough.
- **Install Homebrew in Group A** (even though first strict need is W5). Reason: avoids a mid-curriculum install detour and lets us install Python, CMake, etc. with one command later.
- **Group-B tools (Python, CMake, GoogleTest) deferred to just-in-time install.** Reason: minimises upfront friction for a non-technical user; nothing in W1–W4 needs them.

---

## 2026-05-05 — Guard placement in BS pricer: main() vs. inside functions

**Context.** `blackScholesCall`, `blackScholesPut`, `delta`, and `vega` all divide by `sigma * sqrt(T)`. If either is zero, the result is undefined. Guards were placed in `main()` (before user input reaches the functions) and also inside `blackScholesCall` and `blackScholesPut`.

**Decision.** Keep guards in both locations for now. Rationale: the interactive path is protected by `main()`; the function-level guards catch direct calls from tests or future callers.

**What would flip it.** In Day 4 code review: consolidate to function-level only, remove the `main()` guards, and add a test that calls the pricer directly with `sigma=0` to verify the function-level guard fires. This is the cleaner library-style pattern. Deferred because the current code is correct, and Day 2 is not the right moment to refactor.

---

---

## 2026-05-13 — GBMSimulator as local variable vs. member of MCPricer

**Context.** W6 Day 2: user tried to declare `GBMSimulator _simulator` as a private member of `MCPricer`. `GBMSimulator` has no default constructor — it requires S0, r, sigma, T, steps, seed. Also, `N` (number of paths) and `steps` (time steps per path) are different parameters; the user had conflated them.

**Decision.** Create `GBMSimulator` as a local variable inside `price_call()`, hardcoding `steps=252` and `seed=42` for now. Rationale: simplest correct solution at W6 skill level; avoids adding `steps` and `seed` as `MCPricer` constructor parameters before the user understands why they'd need them.

**What would flip it.** If we add variance reduction (W13) or parallel paths (W14), the simulator configuration will need to be more explicit. At that point, promote `steps` and `seed` to constructor parameters and initialize `_simulator` in the member initializer list.

**EXECUTED — 2026-05-14 (W6 Day 4 code review).** The flip was executed earlier than anticipated: the code review revealed the design flaw at W6 (same paths on every `price_call()` call, not just a W13 concern). `steps` and `seed` promoted to `MCPricer` constructor parameters; `_simulator` promoted to persistent member variable initialized in the constructor's member initializer list. Four redundant private fields removed (`_S0`, `_sigma`, `_steps`, `_seed`). See [notes/w6_d4.md](notes/w6_d4.md).

---

## 2026-05-13 — Inline member function bodies in headers at W6

**Context.** W6 Day 2: header/source split introduced. User asked whether to put the full `MCPricer` class (including method bodies) in the header. Convention for large projects is declaration in `.h`, definition in `.cpp`. But at this scale (single-file compilation, small methods), everything inline in the header is simpler and correct.

**Decision.** Full class definition (including method bodies) in the header through at least W14. Rationale: the declaration/definition split is a compilation-speed optimization and a readability aid for large codebases — neither concern applies here. The full split will be introduced naturally with CMake in W15.

**What would flip it.** If any class grows beyond ~50 lines of method body, or if compilation time becomes noticeable, extract method bodies to `.cpp` earlier.

---

---

## 2026-05-14 — Return type for `price_call()`: `std::pair` vs struct vs two methods

**Context.** W6 Day 5 acceptance test requires both the MC price (mean of discounted payoffs) and the stdev of those payoffs. `price_call()` previously returned only a `double`. Three options were available at W6 skill level.

**Options considered:**

1. **`std::pair<double,double>`** — built-in; no new type needed; caller uses structured binding `auto [price, stdev] = ...`.
2. **Named struct** — defines a new type (e.g., `struct PriceResult { double price; double stdev; }`); most readable at call site; requires defining the struct in the header.
3. **Two separate methods** — `price_call()` returns mean; `price_call_stdev()` returns stdev; caller makes two calls, each re-running N paths.

**Decision.** Use `std::pair<double,double>`.

**Reasoning:**
- User has not yet been introduced to struct syntax; introducing it here would be scope creep on a Day 5 admin session.
- Two separate methods would either duplicate the N-path loop (expensive and inconsistent) or require shared mutable state — both are worse designs.
- `std::pair` requires no new concepts beyond what's needed and ships with C++17 structured binding syntax the user already has.

**Consequences:**
- Good: zero new syntax; caller is clean; both values computed in one pass.
- Bad: `first`/`second` field names are opaque if the structured binding is not used; a future reader of the raw pair has no semantic labels.
- Reversibility: cheap — replace return type with a named struct in W15 when code hygiene is the focus.

**Review date:** 2026-11-14

---

## 2026-05-21 — Reuse of price_series stats functions in csv_loader: header vs inline copy

**Context.** W7 Day 4: csv_loader.cpp needs `mean` and `standard_deviation` functions already written in [projects/week03/price_series.cpp](projects/week03/price_series.cpp). User proposed converting price_series.cpp into a header and `#include`-ing it.

**Decision.** Copy the two functions directly into csv_loader.cpp rather than creating a shared header.

**Reasoning:**
- csv_loader.cpp is a standalone program, not a library. No other file needs these functions.
- A shared header would add two new files and a compile step for zero practical benefit at this scale.
- CLAUDE.md rule: "smallest diff that solves the problem; no new abstractions for cases that can't happen."
- The user correctly reasoned to this conclusion independently after one architectural question.

**What would flip it.** When W8 (Monte Carlo VaR) needs the same stats functions and a third file also needs them — at that point extract to a `stats.h` / `stats.cpp` pair. Three callers is the natural threshold for a shared utility.

---

## 2026-05-22 — VaR function interfaces: pre-computed stats vs raw data

**Context.** W8 Day 2: `parametric_VaR` and `monte_carlo_VaR` both need μ and σ. User initially proposed passing both the raw price vector and pre-computed mean/stddev (redundant). Three options existed: (1) pass raw returns, compute stats inside each function; (2) pass pre-computed mean/stddev; (3) pass both (redundant).

**Decision.** Pre-computed mean/stddev passed by caller — signatures `parametric_VaR(double mean, double stddev)` and `monte_carlo_VaR(double mean, double sigma, int N, unsigned int seed)`.

**Reasoning.**
- Each VaR function does one job: compute VaR given statistical parameters — not compute stats + compute VaR.
- Caller (`main`) computes log returns, mean, and stddev once from the loaded data, then passes to all three VaR methods. No repeated computation.
- Consistent with single-responsibility principle at this stage.

**What would flip it.** If VaR functions need to be unit-tested in isolation (without a caller pre-computing stats), add overloads accepting a returns vector. Not a concern until W15 GoogleTest.

---

## 2026-05-22 — No CSVLoader class; free function load_prices() instead

**Context.** W8 Day 2: user asked whether to create a CSVLoader class wrapping the CSV-reading logic.

**Decision.** Free function `load_prices(const std::string& filepath) → std::vector<double>`. No class.

**Reasoning.** A class is appropriate when an object needs to remember state between calls (e.g., `NormalSampler` holds its RNG engine state across draws). `load_prices` has no state to maintain — it opens a file, reads it, and returns data. A class would add abstraction with zero benefit. User arrived at this conclusion after one coaching question ("what state would it hold between calls?").

**What would flip it.** If we needed to stream a large file in chunks, maintaining a buffer and file position between calls — a class would be appropriate. Not applicable at this project scale.

---

## 2026-05-24 — Calibration/out-of-sample split: hardcoded 70/30 at index 350

**Context.** W8 Day 4: `main()` needed to split `log_return_vec` into a calibration window (to compute VaR) and an out-of-sample window (to test exceedance frequency). Split ratio and implementation method needed to be chosen.

**Decision.** Hardcode `split_idx = log_return_vec.begin() + 350`, giving approximately 70% calibration (350 returns) and 30% out-of-sample (remaining ~150 returns).

**Reasoning.**
- 70/30 is a conventional in-sample/out-of-sample split. At 99% confidence, approximately 1.5 exceedances expected in 150 out-of-sample days — enough to observe the frequency meaningfully.
- Hardcoding 350 is simpler than computing `(int)(N * 0.7)` at this stage; the data file is fixed.
- No academic standard mandates a specific split for VaR backtesting; 70/30 is a defensible default.

**What would flip it.** If the data file changes size (different date range loaded), the hardcoded 350 silently becomes the wrong proportion. Fix: compute split index as `static_cast<int>(log_return_vec.size() * 0.7)` and assert that both windows contain enough data for the relevant VaR calculation (calibration needs ≥100 returns; out-of-sample needs ≥100 for 1% exceedance to be observable).

---

**Explicitly deferred / rejected.** Full Xcode IDE, GCC via Homebrew, Conan/vcpkg, Docker, valgrind — reasons noted in [setup.md](setup.md) "Deliberately omitted" section.

---

## 2026-05-25 — Context bloat reduction: PROGRESS.md split into ACTIVE + HISTORY

**Context.** Session-start token cost was growing unsustainably: `PROGRESS.md` (401 lines, ~9,000 tokens) and `setup.md` (310 lines, ~4,500 tokens) were read in full every session by the `/start` skill. `PROGRESS.md` was on track to exceed 1,000 lines by W16. Combined waste: ~13,500 tokens per session, ~65% of total session-start cost.

**Decision.** Split `PROGRESS.md` into two files:
- `PROGRESS_ACTIVE.md` (≤40-line cap) — session-start file; contains current state, next-session block, open retrieval gaps, milestone checklist only.
- `PROGRESS_HISTORY.md` (append-only archive) — full session log, retrieval scores table, week-by-week ledger; never read at session start.

Remove `setup.md` from the `/start` skill read list (one-time install guide; no session-relevant state after W1).

**Deferred.** Graphify (github.com/safishamsi/graphify) — a Claude Code skill that indexes a repo into a queryable knowledge graph — was evaluated and is the right tool for W12+ when three full artifacts exist. Not worth the setup complexity now; current token problem is a file-organisation problem, not a code-indexing problem.

**What would flip it.** If `PROGRESS_ACTIVE.md` consistently overflows the 40-line cap despite the `/end` overflow rule, revisit the cap or consider Graphify earlier. If retrieval gaps from 2+ weeks ago need to be visible during session start (e.g., a re-test schedule spanning many weeks), add a `## Scheduled re-tests` section or expand the cap.
