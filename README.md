# General Workflow Workspace

A reusable VS Code workspace that gives Claude **persistent project memory**. Open this folder in Claude Code and Claude will already know who it's working for, what good output looks like, and which workflow to follow — without re-explanation.

## Core principle

> **The folder is memory. The prompt is direction.**

Files in this workspace persist across sessions. Use them to encode anything Claude should know on day 100 that you'd otherwise have to re-explain. Use prompts only for the immediate task.

## File map

| File | Purpose |
|---|---|
| [CLAUDE.md](CLAUDE.md) | Durable, operational rules Claude reads every session. Keep ≤200 lines. |
| [CONTEXT.md](CONTEXT.md) | What this specific project is, who it's for, what success looks like. **Edit this first for new projects.** |
| [PROMPTING_PROTOCOL.md](PROMPTING_PROTOCOL.md) | The 5-part prompting framework (Identity, Task, Context, Constraints, Output Format). |
| [WORKFLOW.md](WORKFLOW.md) | Standard 10-phase project lifecycle. |
| [AGENTS.md](AGENTS.md) | Library of 11 reusable Claude roles (architect, reviewer, debugger, etc.). |
| [REFERENCES.md](REFERENCES.md) | Background material. Every claim labeled VERIFIED / UNVERIFIED / TO RESEARCH. |
| [TASKS.md](TASKS.md) | Lightweight kanban (Backlog / In Progress / Blocked / Done). |
| [DECISIONS.md](DECISIONS.md) | Log of architectural / strategic decisions with reasoning. |
| [ASSUMPTIONS.md](ASSUMPTIONS.md) | Assumptions made during execution, with verification path. |
| [REFERENCE_RESEARCH_QUEUE.md](REFERENCE_RESEARCH_QUEUE.md) | Items needing factual verification before they can be cited. |
| [.claude/skills/project-planning/SKILL.md](.claude/skills/project-planning/SKILL.md) | Example skill: vague idea → executable plan. |
| [.claude/agents/](.claude/agents/) | Drop custom subagent definitions here. |
| [.claude/commands/new-project.md](.claude/commands/new-project.md) | Example slash command for spinning up a new project. |
| [templates/](templates/) | Copy-paste templates for briefs, prompts, reviews, decisions, retros. |
| [examples/](examples/) | What strong Claude outputs look like, and what to avoid. |

## First-time setup (5 min)

1. **Edit [CONTEXT.md](CONTEXT.md)** — fill in project name, purpose, success criteria. This is the most important file.
2. **Skim [CLAUDE.md](CLAUDE.md)** — confirm the rules match how you want to work; edit the "User working style" section.
3. **Read [PROMPTING_PROTOCOL.md](PROMPTING_PROTOCOL.md)** once — it changes how you'll write prompts.
4. **Pick a starting template** from [templates/](templates/) for your first task.

## Forking for a new project

```
cp -r general-workflow-ideation/ my-new-project/
cd my-new-project
# clear per-project state:
> TASKS.md            # blank kanban
> DECISIONS.md        # keep the format header, drop the seed entry
> ASSUMPTIONS.md      # blank
# then edit CONTEXT.md for the new project
```

Or invoke [.claude/commands/new-project.md](.claude/commands/new-project.md) inside Claude Code.

## How to work with Claude Code using this workspace

- For non-trivial tasks, start in **plan mode** — Claude writes a plan, you approve, then it executes.
- Use [templates/task-prompt-template.md](templates/task-prompt-template.md) as your default prompt skeleton.
- When Claude is unsure, it should write to [ASSUMPTIONS.md](ASSUMPTIONS.md) rather than guess silently.
- After meaningful work, update [TASKS.md](TASKS.md) and add anything new to [DECISIONS.md](DECISIONS.md) or [REFERENCE_RESEARCH_QUEUE.md](REFERENCE_RESEARCH_QUEUE.md).
- At project end, fill in [templates/retrospective-template.md](templates/retrospective-template.md).

## What this workspace is not

- Not a code framework — language/stack agnostic.
- Not an agent runtime — it's documentation Claude reads.
- Not a replacement for clear thinking — it's scaffolding for it.
