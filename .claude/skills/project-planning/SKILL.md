---
name: project-planning
description: Turn a vague project idea into a concrete, sequenced execution plan. Trigger when the user says "let's plan", "how should we approach X", "I want to build Y but don't know where to start", or whenever scope is fuzzy and effort is non-trivial.
---

# Skill: Project Planning

## Purpose

Transform a vague intent ("I want to build a dashboard," "we should improve onboarding") into an executable plan: concrete scope, sequenced milestones, named unknowns, success criteria.

## When Claude should use this

Use when **all** of:
- The request is project-scale (≥ a few hours of work, multiple files or surfaces).
- Scope is not yet pinned down — the user hasn't already produced a brief.
- The cost of building the wrong thing exceeds the cost of a 20-minute planning conversation.

Skip when:
- It's a single-file edit or trivial change.
- The user has already produced a [project-brief](../../../templates/project-brief-template.md) — go straight to execution.
- The user explicitly says "just do it."

## Inputs needed

Before running this skill, gather (ask if missing):

1. **The goal** in one sentence.
2. **Why now** — what triggered the project.
3. **Hard constraints** — deadlines, stack, dependencies, budget.
4. **Stakeholders** — who cares about the output.
5. **Success criteria** — how the user will know it's done.
6. **Out-of-scope items** — explicit non-goals (often the most useful input).

Missing items 4–6 are common; surface them as part of the skill output rather than blocking.

## Step-by-step workflow

### Step 1 — Restate the goal in one sentence

Mirror back the goal exactly. If you can't write it in one sentence, the goal isn't clear yet — ask.

### Step 2 — Write success criteria

What observable thing is true when this is done? Concrete and checkable. "Users can sign up and reach the dashboard in <30 seconds" beats "improved onboarding."

### Step 3 — Surface unknowns

List what you don't know that materially affects the plan. Tag each:
- `RESOLVE NOW` — blocks planning. Ask the user.
- `RESOLVE EARLY` — first work item should answer this.
- `ACCEPT` — proceed with an assumption, log to [ASSUMPTIONS.md](../../../ASSUMPTIONS.md).

### Step 4 — Decompose into chunks

Break the goal into 3–8 chunks. Each chunk:
- Is independently completable (you could ship it alone).
- Produces a visible artifact.
- Takes roughly 1–4 hours of focused work.

If a chunk is too big, split it. If it's too small, merge.

### Step 5 — Sequence by dependency

Order chunks so each one's prerequisites are done. The first chunk should be the smallest thing that proves the approach works (a "spike" or "walking skeleton").

### Step 6 — Estimate effort and risk

For each chunk:
- **Effort:** S / M / L (loose, not a commitment).
- **Risk:** what's the most likely thing that goes wrong?

If total effort exceeds the user's stated time budget, surface that *now*, not at the end.

### Step 7 — Produce the execution plan

Write the plan in the format below. Either return it inline or, for larger projects, save to a plan file in the workspace.

## Output format

```markdown
# Plan: [Project name]

## Goal (one sentence)
[Restated goal]

## Success criteria
- [Observable outcome 1]
- [Observable outcome 2]

## Out of scope
- [Explicit non-goal 1]
- [Explicit non-goal 2]

## Unknowns
- [RESOLVE NOW] [Question for user]
- [RESOLVE EARLY] [Question first chunk should answer]
- [ACCEPT] [Working assumption — also logged in ASSUMPTIONS.md]

## Chunks (sequenced)

### 1. [Chunk name] — [S/M/L]
- **Produces:** [visible artifact]
- **Risk:** [most likely failure]
- **Steps:** [3–6 bullets]

### 2. [...]

## Total effort estimate
[Sum, with caveat about confidence]

## Next concrete action
[The single next thing to do]
```

## Quality checklist

Before returning the plan, check:

- [ ] Goal sentence would survive a stranger reading it.
- [ ] Success criteria are observable, not aspirational ("ships," not "delights users").
- [ ] At least one explicit out-of-scope item (catches scope creep early).
- [ ] First chunk is a walking skeleton or spike, not the most "valuable" feature.
- [ ] No chunk is "design X" or "research Y" without a deliverable — both should produce a written artifact.
- [ ] Unknowns are tagged with the right action label.
- [ ] Total effort matches the user's apparent budget; if not, said so explicitly.
- [ ] "Next concrete action" is specific enough to start in the next 5 minutes.
