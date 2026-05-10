# Task Prompt Template

> Direct application of the 5-part framework from [PROMPTING_PROTOCOL.md](../PROMPTING_PROTOCOL.md). Copy, fill in placeholders, paste into Claude Code. Delete sections that genuinely don't apply (rare).

---

```
Identity:
You are [a senior X engineer / a skeptical product strategist / the role from AGENTS.md].

Task:
[Verb-led, measurable. Examples:
 - "Refactor `src/parser.py` to remove the duplication between parse_a() and parse_b()."
 - "Rank these 5 options by likelihood of working in production."
 - "Produce a 1-page brief comparing approach A and approach B."]

Context:
- Project: see [CONTEXT.md].
- Relevant files: [paths]
- Prior decisions: [DECISIONS.md entries by title, if relevant]
- What I've already tried: [list]
- Audience for the output: [who reads this]

Constraints:
- Don't [introduce new dependencies / change public APIs / modify the schema].
- Stay within [scope boundary].
- [Tone / length limits]
- [Anything else that's a hard "no"]

Output format:
- [Shape: bulleted list / table / code block / diff / prose]
- [Length: ≤ N words / N items]
- [Where to put it: inline / write to file X / open a PR draft]
```

---

## Quick variants

### One-liner for trivial tasks

> Skip the template. Just say: "[verb] [target]: [constraints]." Example: "Rename `getCwd` → `getCurrentWorkingDirectory` across the repo. Don't touch tests."

### Follow-up turns

> Drop Identity and Context (inherited). Keep Task and Constraints. Reference prior turn explicitly: "In your last output, line N, …"

### When you don't know what role to specify

> Default to: "You are a senior collaborator: planner, builder, and reviewer." Then move on to the Task.
