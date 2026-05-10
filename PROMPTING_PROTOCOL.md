# PROMPTING_PROTOCOL.md — The 5-Part Framework

A practical structure for prompts that produce useful Claude output. Use it as a default skeleton, not a rigid form.

## The five parts

### 1. Identity — *who Claude should be*

The role / lens Claude takes. Defaults to "senior collaborator" if unspecified. Be specific when the task benefits from a sharper lens (e.g., "act as a security reviewer," "act as a hostile QA tester").

> Bad: "You are an AI assistant."
> Good: "You are a senior backend engineer reviewing this migration for production safety."

### 2. Task — *what needs to be done*

The verb-led description of the action. Use measurable verbs ("rewrite," "compare," "list," "explain," "produce"). Avoid vague verbs like "improve," "optimize," or "look at."

> Bad: "Optimize this function."
> Good: "Rewrite this function so the worst-case complexity is O(n log n) instead of O(n²), keeping the public signature unchanged."

### 3. Context — *what Claude needs to know*

The minimum information required to do the task well: relevant files, constraints, prior decisions, user role, environment. Link to durable docs ([CONTEXT.md](CONTEXT.md), [DECISIONS.md](DECISIONS.md)) when applicable.

> Tip: if Claude is asking the same question across sessions, that context belongs in a workspace file, not in every prompt.

### 4. Constraints — *what Claude should avoid*

Explicit guardrails. Things like:
- "Don't introduce new dependencies."
- "Don't change the database schema."
- "Output in plain text — no markdown."
- "Stay under 200 words."
- "Don't speculate about anything not in the file I gave you."

Constraints prevent the most common failure modes — see [examples/bad-output-patterns.md](examples/bad-output-patterns.md).

### 5. Output format — *what the answer should look like*

Specify shape, length, and medium up front. "Bulleted list of 3–5 items," "table with columns name/role/risk," "diff format only," "200-word summary."

> Without this, you'll get whatever shape Claude defaults to — which is usually too long.

---

## When to use all five parts

- **Always for non-trivial work** — anything you'd be annoyed to redo.
- **Skip Identity and Output Format for quick conversational turns.** Keep Task and Constraints.
- **Add Context heavily for the first turn of a new project**; lighter on follow-ups (since prior turns are context).

## Chunking large projects

A 5,000-word document or 30-task project will not produce good output as a single prompt. Chunk it:

1. **Decompose** into independent units (sections, modules, milestones).
2. **Sequence** by dependency. Do the foundation chunks first.
3. **Anchor** each chunk with a stable reference back to the overall plan ("This is chunk 3 of 7. Plan is at TASKS.md.").
4. **Summarize** between chunks. After completing chunk N, write a 3-line summary that becomes context for chunk N+1.

See [.claude/skills/project-planning/SKILL.md](.claude/skills/project-planning/SKILL.md) for the decomposition process.

## Feeding large documents

- **Don't paste 50KB of text into a prompt and hope.** Reference the file path and ask Claude to read it.
- **Pre-summarize** when possible: "Here's a 200-word summary of doc X. Full doc at path/to/doc.md."
- **Section-by-section** beats whole-document for transformation tasks (translation, rewriting, code refactoring).
- **Extract before reasoning:** "First list every claim in section 2, then evaluate each."

## Structuring follow-up prompts

Follow-ups inherit context, so they can be terser:
- Reference previous turns explicitly ("the function you wrote above"), not vaguely ("that thing").
- Point at specific lines: "In your last output, line 14, the `if` branch is wrong because…"
- When pivoting, say so: "Drop the previous approach. New direction: …"

## Turning vague prompts into executable prompts

A vague prompt is one where two reasonable people would produce different outputs. To fix:

1. **Identify the vague verb** — "improve," "help with," "look at."
2. **Replace with a measurable action** — "rewrite," "rank," "list 5 reasons."
3. **Add the missing slot** — usually Constraints or Output Format.
4. **State success criteria** — "I'll consider this done when X is true."

### Weak → Strong examples

> **Weak:** "Help me with my resume."
> **Strong:** "You are a senior recruiter for a backend role at a Series B startup. Review the resume at `resume.md`. Output a numbered list of the top 5 issues, ranked by impact. For each: 1-line problem, 1-line fix. Don't rewrite the resume yet."

> **Weak:** "Make this code better."
> **Strong:** "Refactor `parser.py` to remove the duplicated string-handling logic in `parse_a()` and `parse_b()`. Extract a private helper. Don't change public APIs or add new dependencies. Output the diff only."

> **Weak:** "What do you think about this idea?"
> **Strong:** "Act as a skeptical product strategist. Read `idea.md`. List the 3 strongest reasons this would fail in market, ranked by likelihood. Then list 1 reason it might still be worth pursuing. ≤300 words."

---

## Copy-paste template

```
Identity: [role Claude should take, e.g., "senior X engineer"]

Task: [verb-led, measurable: "rewrite X so Y", "rank N items by Z", "produce a 1-page brief on …"]

Context:
- [relevant file paths]
- [relevant constraints from CONTEXT.md or DECISIONS.md]
- [user role / audience]
- [prior turns or attempts]

Constraints:
- [what NOT to do]
- [scope boundary]
- [length, tone, format limits]

Output format:
- [shape: bullets / table / code block / prose]
- [length: ≤N words / N items]
- [medium: write to file X / inline answer / diff]
```
