---
description: Spin up a new project by forking this workspace structure and clearing per-project state.
---

# /new-project

Use this command when starting a new project that should reuse the workspace's structure but not its current state.

## What this does

1. Asks the user for the new project name (and target directory).
2. Copies the workspace to the new location.
3. Clears per-project state files (TASKS.md, DECISIONS.md, ASSUMPTIONS.md, REFERENCE_RESEARCH_QUEUE.md) — keeping only the format header in each.
4. Opens [CONTEXT.md](../../CONTEXT.md) for editing — the user fills in the new project's name, purpose, success criteria, and stakeholders.
5. Reminds the user to skim [CLAUDE.md](../../CLAUDE.md) §2 ("User working style") and adjust if needed.
6. Suggests starting with [templates/project-brief-template.md](../../templates/project-brief-template.md) or invoking the [project-planning skill](../skills/project-planning/SKILL.md).

## Manual fallback

If the slash command isn't wired up, do this by hand:

```
cp -r /path/to/general-workflow-ideation /path/to/new-project
cd /path/to/new-project
# clear per-project state (keep format headers, drop entries):
> TASKS.md
> DECISIONS.md
> ASSUMPTIONS.md
> REFERENCE_RESEARCH_QUEUE.md
# then edit CONTEXT.md
```

## Do not clear

- [CLAUDE.md](../../CLAUDE.md) — durable rules, reuse as-is.
- [WORKFLOW.md](../../WORKFLOW.md), [PROMPTING_PROTOCOL.md](../../PROMPTING_PROTOCOL.md), [AGENTS.md](../../AGENTS.md) — durable.
- [REFERENCES.md](../../REFERENCES.md) — keep verified entries; user may want to prune project-specific ones.
- [templates/](../../templates/), [examples/](../../examples/), [.claude/](../) — reuse as-is.
