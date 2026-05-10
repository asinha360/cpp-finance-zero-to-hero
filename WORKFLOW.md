# WORKFLOW.md — Standard Project Lifecycle

A repeatable 10-phase lifecycle Claude follows for non-trivial work. Skip phases when they obviously don't apply (a typo fix doesn't need a research phase), but never skip silently — note in [TASKS.md](TASKS.md) that you skipped and why.

Each phase has the same structure:
- **Purpose** — what this phase exists to produce
- **Claude's responsibilities**
- **User's responsibilities**
- **Expected output**
- **Common failure modes**

---

## 1. Intake

**Purpose:** Capture the raw request without distortion.

**Claude:**
- Read the request literally before interpreting.
- Note exact wording of the goal in your own working memory or [TASKS.md](TASKS.md).
- Do not start solving yet.

**User:**
- State the goal in plain language. Don't pre-design.

**Expected output:** A one-sentence restatement of the goal, captured under "In Progress" in [TASKS.md](TASKS.md).

**Failure modes:**
- Skipping straight to a solution.
- Restating the goal in a way that quietly narrows or widens scope.

---

## 2. Clarification

**Purpose:** Resolve genuine ambiguity before investing effort.

**Claude:**
- Identify ambiguities with materially different outcomes.
- Batch questions; ask 2–4 sharp ones, not 8 fragmented ones.
- Skip when context resolves the ambiguity (then proceed and document via [ASSUMPTIONS.md](ASSUMPTIONS.md)).

**User:**
- Answer directly. "I don't care, you pick" is a valid answer that should be logged as an assumption.

**Expected output:** A shared, written understanding of scope and out-of-scope.

**Failure modes:**
- Asking obvious questions to look thorough.
- Accepting a vague answer and proceeding as if it were clear.

---

## 3. Planning

**Purpose:** Choose an approach before building.

**Claude:**
- Produce a plan: 3–8 bullets for small work, a plan-mode plan for larger work.
- Surface 1–2 alternatives only if the choice is non-obvious; otherwise commit.
- Identify files that will be touched.

**User:**
- Approve, redirect, or ask for alternatives.

**Expected output:** A plan the user has approved (explicitly or implicitly via "go").

**Failure modes:**
- Plan-of-a-plan: planning the planning instead of solving.
- Listing alternatives the user obviously doesn't want, to seem balanced.
- Committing to a plan without identifying which files change.

---

## 4. Research

**Purpose:** Fill in the unknowns the plan depends on.

**Claude:**
- Read existing code/docs before searching the web.
- Apply the labeling rules from [REFERENCES.md](REFERENCES.md) to anything cited.
- Anything you can't verify goes to [REFERENCE_RESEARCH_QUEUE.md](REFERENCE_RESEARCH_QUEUE.md).

**User:**
- Provide internal sources Claude can't reach (private docs, screenshots, links).

**Expected output:** A short note in the plan or [TASKS.md](TASKS.md) listing what was learned and what's still unknown.

**Failure modes:**
- Inventing a "fact" because the search came back empty.
- Researching beyond what the plan needs ("while I'm here, let me also check…").

---

## 5. Execution

**Purpose:** Do the work.

**Claude:**
- Read each file before editing it.
- Make the smallest diff that solves the problem.
- Use parallel tool calls where independent.
- Update [TASKS.md](TASKS.md) as items complete; don't batch.

**User:**
- Stay available for blockers; let Claude work otherwise.

**Expected output:** Working changes, with the plan steps reflected in commits or staged edits.

**Failure modes:**
- Drive-by refactors outside the planned scope.
- Editing files that weren't read first.
- Reporting "done" before verifying.

---

## 6. Review

**Purpose:** Catch problems before testing.

**Claude:**
- Re-read the diff as if you're someone else.
- Check against the plan: did anything sneak in or drop out?
- Run the [code-review-template](templates/code-review-template.md) lens for code work.

**User:**
- Skim the diff. Trust but verify.

**Expected output:** A short self-review: "matches plan / found X / fixed Y."

**Failure modes:**
- Self-review as a formality (no actual reading).
- Reviewing only what you wrote, not how it interacts with what's already there.

---

## 7. Testing or validation

**Purpose:** Verify behavior, not just compilation.

**Claude:**
- Run tests if they exist. Add tests if the change warrants and the user wants them.
- For UI work: open in a browser, click through, watch for regressions.
- For research/writing: re-read the output cold; does it answer the question?

**User:**
- Confirm acceptance criteria are met from their perspective.

**Expected output:** Evidence: test output, screenshot, manual reproduction notes.

**Failure modes:**
- "Tests pass" with no actual run.
- Asserting feature correctness from type-checks alone.
- Skipping the negative case (what happens with bad input).

---

## 8. Documentation

**Purpose:** Make the change discoverable for future-you.

**Claude:**
- Update [DECISIONS.md](DECISIONS.md) for non-trivial choices.
- Update [REFERENCES.md](REFERENCES.md) only if a new durable pattern emerged.
- Update inline `README.md` or per-feature docs *only if asked or clearly needed*.

**User:**
- Tell Claude when documentation is required for stakeholders.

**Expected output:** Decisions logged; no spec drift between code and docs.

**Failure modes:**
- Writing docs nobody asked for.
- Forgetting to log decisions, then re-debating them in two weeks.

---

## 9. Retrospective

**Purpose:** Learn from the cycle.

**Claude:**
- Use [templates/retrospective-template.md](templates/retrospective-template.md).
- Honest about what didn't work — vague retros are useless.

**User:**
- Add things only the user can see (frustration points, time spent).

**Expected output:** A short retro entry. One concrete change for next cycle.

**Failure modes:**
- Generic retros ("communication could be better"). Be specific or skip it.
- Skipping retros after the rough projects, when they matter most.

---

## 10. Next actions

**Purpose:** Hand off cleanly.

**Claude:**
- Update [TASKS.md](TASKS.md): move items to Done, add follow-ups to Backlog.
- Surface anything blocked.
- State the *single most useful next thing*.

**User:**
- Decide whether to continue, pause, or pivot.

**Expected output:** A 1–3 line summary + the next concrete action.

**Failure modes:**
- "Let me know what you'd like next!" — no recommendation.
- Burying blockers in prose instead of flagging them.
