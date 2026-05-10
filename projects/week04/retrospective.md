# Retrospective: Week 4 — Black-Scholes Pricer (Milestone 1)

**Date:** 2026-05-06
**Cycle covered:** 2026-05-03 → 2026-05-06 (Days 1–5)
**Participants:** Aryaman, Claude

---

## What we set out to do

Build a Black-Scholes European call/put pricer with delta and vega from scratch — compiling clean under `-Wall -Wextra -std=c++20`, passing two acceptance criteria: Call(S=100,K=100,r=0.05,σ=0.2,T=1) ≈ 10.45 ±0.01, and put-call parity holding to 1e-10 across 20 random inputs.

## What actually happened

Both acceptance criteria were green by Day 4. The pricer grew beyond the spec: d1/d2 were extracted into reusable helpers; delta and vega are separately computed and tested; a 20-case table-driven parity test covers ITM, OTM, ATM, and a range of T and σ values. A second artifact, [bond_pricer_ytm.cpp](bond_pricer_ytm.cpp), emerged from the Day 3 retrieval challenge — the bisection method was introduced and implemented from scratch as an interleaved W2 extension. The guard-placement question (main vs. functions) was debated across Days 2–4 and resolved cleanly: assert at the most foundational caller (`compute_d1`) so all four callers are covered automatically.

## What worked

- **Deriving before coding.** Every formula (normal CDF, d1, d2, delta, vega, put-call parity) was derived from first principles before a line of code was written. When bugs appeared (missing `*T`, operator precedence in denominator), the derivation was the reference that caught them.
- **Table-driven testing pattern.** Extending the parity test from 1 case to 20 using a struct array was understood and applied independently in Day 4. The pattern generalises to all future test suites.
- **Python shell for concept exploration.** Plug-and-play numerical examples (log-normal asymmetry: `(e^0.1 + e^-0.1)/2 > 1`) made abstract math tangible without needing visual tools inside the C++ workflow.
- **Guard at the foundational level.** Placing the assert in `compute_d1` rather than four call sites was understood as a principle (functions own their preconditions), not a one-off fix.
- **Bisection as a payoff.** Introducing the YTM solver as a retrieval challenge (W2 bond pricer + new algorithm) made the difficulty feel purposeful rather than arbitrary.

## What didn't work

- **Silent `return 1` anti-pattern persisted from Day 2 to Day 4.** The function returned `1` on bad input — a valid price — which would have poisoned the bisection solver silently. It took a dedicated code review pass to catch it. Lesson: "does it compile and output something" is not "is the error signaling correct."
- **Parity test was under-specified at Day 2.** One test case passed, so it felt done. The curriculum required 20. The gap only surfaced at code review. Better habit: write the full test suite before declaring the implementation done.
- **Visuals absent from concept introduction.** The log-normal asymmetry and σ²/2 correction were understood numerically but would have been clearer with a graph showing the asymmetry of the exponential function. Worth using an external Python/matplotlib session for future weeks with geometric concepts.

## Surprises

- Getting d1 and d2 exactly right from memory on Day 3, unaided, after only one prior recall session. The retrieval-before-implementation structure appears to be working.
- The bisection method clicked faster than expected — the f(r)=0 reformulation needed algebra coaching, but the bracketing and halving logic was grasped in one pass.
- Degrees-of-freedom reasoning for n=1 variance (today's retrieval) came completely unaided after the minimizer property was named — zero prompt needed.

## Decisions to revisit

- **2026-05-05 — Guard placement: main() vs. functions.** Resolved in Day 4: consolidated to `compute_d1` only, `main()` guards removed, covered by the assert that fires on direct calls with bad input. Decision is now closed; no further revisit needed.

## What we'll change next cycle

1. **Write the full acceptance test before starting the implementation**, not after. If the curriculum specifies 20 test cases, scaffold the test array on Day 1 and fill cases as the implementation progresses.
2. **For geometric or distributional concepts, run a parallel Python session with matplotlib.** Text-only explanation of things like the normal distribution or GBM paths loses the shape. The toolchain supports this; use it from W5 onward.
3. **Name the error-signaling mechanism explicitly when adding any guard.** Before writing a guard, decide: assert, NaN, exception, or error code — and write one sentence in a comment only if the choice would surprise a reader. Default is assert for preconditions.

## Open follow-ups

- [ ] W5 TASKS.md entry: install `<random>` harness and write normal RNG histogram before Day 1 concept intro.
- [ ] W5 setup: prepare a matplotlib Python snippet for visualising the normal distribution (for the histogram acceptance test comparison).
- [ ] Jensen's inequality (why σ²/2 appears in d1) — deferred to W6 when GBM paths can be seen empirically. Add to W6 Day 1 plan.
