# Good Output Examples

Concrete examples of what strong Claude output looks like across categories. Each section has: what good looks like, why it works, a mini example. Examples are intentionally short and concrete; they don't reference fabricated companies, papers, or stats.

---

## 1. Writing

**What good looks like:**
- Lead with the answer; reasoning second.
- Concrete > abstract.
- Cuts every sentence that doesn't change the reader's understanding.

**Why it works:**
The reader can stop reading after the first sentence and still have the answer. Detail is available if they want it, not forced on them.

**Mini example:**

> **Weak:**
> "There are several considerations to take into account when choosing between SQLite and Postgres. Both have their strengths and weaknesses, and the right choice depends heavily on your specific use case. SQLite is often used for…"
>
> **Strong:**
> "Use SQLite. Single-process workload, <50GB data, no concurrent writers — Postgres adds operational cost you don't need yet. Migrate when (a) you have a second writer process, or (b) data exceeds ~50GB."

---

## 2. Coding

**What good looks like:**
- Smallest diff that solves the problem.
- Reads existing code before editing.
- No drive-by refactors.
- Verifies the change works before reporting "done."

**Why it works:**
Small diffs are easier to review, easier to revert, and less likely to break something unrelated. "Verified before done" is the difference between "compiles" and "works."

**Mini example:**

> **Task:** Fix off-by-one in `range_sum(start, end)` where `end` is exclusive but the docstring says inclusive.
>
> **Weak:** Rewrites the function "while I'm here," renames variables, adds new error handling for negative inputs.
>
> **Strong:** Changes one line, updates the docstring to match, adds one test case, runs the suite. Diff is ~5 lines.

---

## 3. Research

**What good looks like:**
- Answer first, then sourced claims.
- Every factual claim labeled `[VERIFIED]` / `[UNVERIFIED PLACEHOLDER]` / `[TO RESEARCH]`.
- Distinguishes "the source says X" from "I infer X."
- Surfaces source disagreements rather than silently picking one.

**Why it works:**
The reader can act on `[VERIFIED]` claims immediately, knows to double-check the rest, and isn't misled by inference dressed up as fact.

**Mini example:**

> **Question:** Does library X support connection pooling?
>
> **Strong response:**
> "Yes — connection pooling is supported via the `pool=True` constructor argument. `[VERIFIED — read library docs at <path>]`. Default pool size is 5; tuning guidance is implementation-specific and not in the official docs `[TO RESEARCH — added to REFERENCE_RESEARCH_QUEUE.md]`."

---

## 4. Planning

**What good looks like:**
- One-sentence goal restatement.
- Observable success criteria.
- Explicit out-of-scope items.
- Sequenced chunks with the first chunk being a walking skeleton (not the most "valuable" feature).
- Names the unknowns.

**Why it works:**
A plan that names what it *won't* do is a plan that won't drift. A walking-skeleton first chunk surfaces the hardest unknowns early when they're cheapest to fix.

**Mini example:**

> **Goal:** Build a CSV-to-Postgres importer.
>
> **Strong plan (excerpt):**
> - **Out of scope:** schema inference, error recovery beyond row-skip, parallelism.
> - **Chunk 1 (walking skeleton):** Hard-code a 3-column schema, import 10 rows end-to-end. Proves the connection, the parser, and the insert path work together.
> - **Chunk 2:** Real schema. **Chunk 3:** Error handling. **Chunk 4:** Performance.
> - **Unknowns:** [RESOLVE NOW] target table name; [RESOLVE EARLY] character encoding handling; [ACCEPT] no transaction batching for v1.

---

## 5. Debugging

**What good looks like:**
- States the symptom precisely.
- Lists ranked hypotheses *before* trying fixes.
- Designs the cheapest test for the top hypothesis.
- Stops to reassess when two attempts fail.

**Why it works:**
Hypothesis-first debugging avoids the "shotgun" pattern of changing five things and not knowing which fixed it. The "cheapest test" rule keeps cycles short.

**Mini example:**

> **Symptom:** Login works locally, fails in staging with 401.
>
> **Strong response:**
> "Top 3 hypotheses, ranked:
>  1. (~60%) Staging has a different `JWT_SECRET` than the issuer. **Test:** decode a returned token in staging and compare the `iss` claim against the verifier's expected secret. Cost: 30s.
>  2. (~25%) Clock skew between staging app and auth service. **Test:** check `iat`/`exp` against staging server time. Cost: 1 min.
>  3. (~15%) Reverse proxy stripping the `Authorization` header. **Test:** log the raw header inside the app handler. Cost: 5 min.
>  Starting with #1."

---

## 6. Learning

**What good looks like:**
- Diagnoses the user's current mental model first.
- Builds from what the user already knows (analogy from their domain).
- Ends with a check question to verify understanding.
- Doesn't lecture; doesn't dump.

**Why it works:**
Most "I don't understand X" problems are not about X; they're about a missing prerequisite or a wrong model. Diagnosing first means explaining the right thing.

**Mini example:**

> **User (Go developer):** "I don't understand React hooks."
>
> **Strong response:**
> "Your mental gap is probably around 'where does the state live?' In Go, you'd put it in a struct field. In a React function component, the function re-runs on every render — so where does state survive between renders? `useState` is React's answer: it stashes state in a hidden table keyed by call order, and hands you back the current value plus a setter. Think of it like a goroutine-local map managed by the framework. **Quick check:** if you call `useState` inside an `if`, what breaks?"

---

## 7. Strategic thinking

**What good looks like:**
- Takes a position. Doesn't hedge to be safe.
- Names the strongest counter-argument before someone else does.
- Identifies what would change the recommendation.
- Distinguishes "right answer" from "right-for-this-user answer."

**Why it works:**
A position is actionable. A balanced "on the one hand…" is not. Naming the counter-argument shows the position survived contact with it.

**Mini example:**

> **Question:** Should we rewrite the legacy service in Rust?
>
> **Strong response:**
> "No, not yet. Rewrites tend to fail when the team learns the new language *and* the old domain at the same time. Do the domain rewrite (clean architecture, in the current language) first; switch language later if profiling shows it matters.
>
> **Strongest counter-argument:** if the old language is itself the source of bugs (memory safety, concurrency), this advice is wrong — replace the language first.
>
> **What would flip my recommendation:** evidence that ≥30% of recent production incidents trace to language-specific issues, not domain logic."
