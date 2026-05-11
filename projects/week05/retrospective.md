# Retrospective: Week 5 — Memory Model + First RNG

**Date:** 2026-05-11
**Cycle covered:** 2026-05-07 → 2026-05-11 (Days 1–5)
**Participants:** Aryaman, Claude

---

## What we set out to do

Build a normal RNG harness that draws 1M samples, prints a text histogram, and passes two acceptance criteria: sample mean in [-0.005, 0.005] and sample stdev in [0.995, 1.005], with the same hardcoded seed reproducing output byte-for-byte. Along the way, gain a working mental model of C++'s memory system — pointers, references, `const&`, and the stack/heap distinction — as the foundation for W6 classes and RAII.

## What actually happened

All three acceptance criteria passed on the Day 5 run (mean 0.00179, stdev 0.99992, seed reproducibility confirmed in Day 2). The harness grew beyond the minimum spec: `mean()`, `sample_variance()`, and `standard_deviation()` were implemented as reusable functions with `assert`-based guards; the histogram was built from scratch in Day 4 using a pre-initialized bin vector and a two-phase index loop. The memory model covered more ground than the W5 curriculum entry strictly required: stack vs heap, vector internals (control block on stack, data on heap), memory leaks, and RAII motivation were all introduced in Day 3 as the necessary setup for W6. A spaced re-derive of the W1 PV calculator was completed from scratch in Day 3, compiling and running correctly on first attempt after one bug fix.

## What worked

- **Seeding rationale reasoned from first principles.** The purpose of seeding (reproducibility, debugging, auditability) was articulated without being told the term — the first time this reasoning arrived unprompted. The derive-before-name approach is working.
- **Three roles of `*` all three unaided.** Declaration, read-dereference, and write-dereference were recalled cleanly in Day 3 — the first time all three arrived without prompting. The three-row table from Day 1 gave the confusion a structure to resolve against.
- **W1 PV spaced re-derive (week+4).** Formula recalled, coded, compiled, and output verified correctly. One bug (`setprecision` without parentheses) was self-diagnosed after a single hint about function-call syntax. The spaced re-derive schedule is producing clean recalls.
- **const-ref vs by-value (W2 spaced retest).** Retrieved correctly unaided in Day 1 — the first time no scaffolding was needed. Prior session (2026-04-29) required prompting.
- **Silent-sentinel anti-pattern caught on code review.** `return 0.0` in `mean()` and `sample_variance()` was identified and replaced with `assert` after one prompt connecting it to W4's `return 1` bug. The pattern is now recognised across contexts.
- **Stack/heap vector internals.** After labels were corrected (initially swapped), the control-block-on-stack / data-on-heap model was understood unprompted and held correctly for the rest of the session. This is the exact mental model W6 classes and RAII require.

## What didn't work

- **`const int& x` type error in range-for recurred.** Applied correctly after correction in `mean()` and `sample_variance()`, then reverted to `const int&` in the histogram counting loop. The correct element type (the vector's declared type) is not yet automatic — it still requires a prompt to self-correct.
- **`push_back` vs pre-initialized increment.** In the histogram, `counts.push_back(bin_index)` was written instead of `counts[bin_index]++`. The conceptual error: reaching for growth (append a new element) when the task required mutation (increment an existing slot). Scored 0 at Day 4 closing; cleared in Day 5 retrieval with a cleaner articulation of the mechanism.
- **σ asymmetry dropped under closing pressure.** The one-sentence distillation of why higher σ raises a call price was stated cleanly during Day 4 but omitted when asked explicitly at session close. The concept was present; the compressed, on-demand version was not. Re-tested clean at Day 5 open.

## Surprises

- Stack and heap labels were swapped on first encounter — user called the stack "heap" and vice versa. This resolved quickly once the lifetime rule was stated (stack = tied to function, heap = persists until freed), but the initial confusion was unexpected given how precisely the pointer model had been understood.
- σ asymmetry is a robust example of the gap between "understands when prompted" and "retrieves under pressure" — the concept was genuinely grasped in Day 2, retrieved unaided in Day 4, but still dropped at Day 4's closing check. One extra short retrieval at session close appears to be the consolidation step that's currently missing.

## Decisions to revisit

- **No open decisions from W5 to revisit.** The `assert`-over-sentinel pattern is now established across two weeks (W4 `return 1`, W5 `return 0.0`) — no further discussion needed; the behaviour is the rule.

## What we'll change next cycle

1. **State the element type explicitly before writing any range-for loop.** Before the opening brace, write one line: "elements are `const T&` where T is \_\_\_." The type error has now recurred in three contexts; making the type explicit before writing prevents the slip.
2. **Before writing any loop over a collection, decide: growth or mutation?** Growth = `push_back`. Mutation = `operator[]`. State this out loud before writing the loop body. The `push_back` vs `counts[i]++` error will recur in W6 when class member vectors appear.
3. **End each session with a one-sentence written compression of the day's hardest concept.** The σ asymmetry drop at closing suggests that the concept is there but not yet compressed into a retrievable sentence. Writing it explicitly at session end, even one line, is the consolidation step.

## Open follow-ups

- [ ] W6 Day 1: Jensen's inequality — why σ²/2 appears in d1 — deferred from W4 Day 3; introduce now that GBM paths can be seen empirically.
- [ ] Re-test due 2026-05-12: stack vs heap labels + vector internals; memory leak mechanism + RAII motivation.
- [ ] Re-test due 2026-05-14: `push_back` vs pre-initialized increment.
- [ ] Re-test due 2026-05-15: three roles of `*`; T& vs T* distinctions; PV re-derive.
- [ ] Re-test due 2026-05-17: BS inputs + directions (5/5); σ asymmetry one-sentence; range-for vs index loop.
