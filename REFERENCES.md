# REFERENCES.md — Background Material

Reusable background for the workspace. **Every entry must carry a verification label** — see [CLAUDE.md §7](CLAUDE.md). No fabricated companies, statistics, papers, or "best practices."

**Labels:**
- `[VERIFIED]` — source provided in this workspace, or read directly this session.
- `[UNVERIFIED PLACEHOLDER]` — useful structure / heuristic, source not yet checked.
- `[TO RESEARCH]` — needs external research; queued in [REFERENCE_RESEARCH_QUEUE.md](REFERENCE_RESEARCH_QUEUE.md).

---

## Examples of excellent work

> Strong examples are the fastest way to align Claude's output. Add real ones from your own work as the project progresses.

- `[UNVERIFIED PLACEHOLDER]` Example: Strong design docs typically lead with a one-paragraph problem statement before any solution.
- `[TO RESEARCH]` Example: Public well-regarded engineering RFCs (e.g., from open-source projects) — to be added once links are verified.
- `[VERIFIED]` See [examples/good-output-examples.md](examples/good-output-examples.md) for in-workspace examples across categories.

## Useful frameworks

- `[VERIFIED]` **5-part prompting framework** (Identity, Task, Context, Constraints, Output Format) — fully defined in [PROMPTING_PROTOCOL.md](PROMPTING_PROTOCOL.md).
- `[VERIFIED]` **10-phase project lifecycle** — defined in [WORKFLOW.md](WORKFLOW.md).
- `[UNVERIFIED PLACEHOLDER]` **MoSCoW** prioritization (Must / Should / Could / Won't) — useful for backlog scoring.
- `[UNVERIFIED PLACEHOLDER]` **RICE** scoring (Reach × Impact × Confidence ÷ Effort) — useful for choosing between features.
- `[UNVERIFIED PLACEHOLDER]` **Five Whys** — root-cause technique; useful in debugging and retrospectives.

## Prompting standards

- `[VERIFIED]` Use the 5-part framework for any non-trivial task — see [PROMPTING_PROTOCOL.md](PROMPTING_PROTOCOL.md).
- `[VERIFIED]` Replace vague verbs ("improve," "optimize," "make better") with measurable outcomes.
- `[VERIFIED]` Specify output format up front. "Bulleted list," "table with columns X/Y/Z," "code block with no prose."
- `[VERIFIED]` State what *not* to do explicitly when there's an obvious wrong path.

## Writing standards

- `[VERIFIED]` Lead with the answer. Reasoning second. Caveats last.
- `[VERIFIED]` Cut every sentence that doesn't change the reader's understanding or action.
- `[VERIFIED]` Concrete > abstract. "200ms p95 latency" beats "fast."
- `[VERIFIED]` Active voice unless the actor is irrelevant.
- `[UNVERIFIED PLACEHOLDER]` Aim for ~15-word average sentence length for technical writing.

## Coding standards

- `[VERIFIED]` Smallest diff that solves the problem.
- `[VERIFIED]` No new abstraction without ≥3 concrete uses.
- `[VERIFIED]` No defensive code for cases that can't happen.
- `[VERIFIED]` Comments explain *why*, not *what*. Default to no comment.
- `[UNVERIFIED PLACEHOLDER]` Functions over ~50 lines or ~3 levels of nesting are usually a smell.

## Research standards

- `[VERIFIED]` Cite the source for every factual claim.
- `[VERIFIED]` Distinguish "I read this" from "I'm inferring this."
- `[VERIFIED]` Prefer primary sources over summaries.
- `[VERIFIED]` When sources disagree, surface the disagreement instead of picking one silently.

## Review standards

See [templates/code-review-template.md](templates/code-review-template.md) for the structured form. Core principles:

- `[VERIFIED]` Correctness first, then security, then readability, then performance.
- `[VERIFIED]` Comment on the diff, not the whole file, unless context is required.
- `[VERIFIED]` Distinguish blocking issues from suggestions.
- `[VERIFIED]` Suggest, don't dictate, when style is at stake.

## Useful links

> External links require verification. Add only after confirming the URL resolves and the content matches the description.

- `[TO RESEARCH]` Anthropic prompting documentation.
- `[TO RESEARCH]` Claude Code official documentation.
- `[TO RESEARCH]` Subagent / skill examples from the broader community.

## Notes

- This file should grow as the project does. Resist the urge to pre-fill it with "everything that might be useful" — only what's actually been used.
- Reorganize by topic when a section exceeds ~10 entries.
- When unsure about a label, default to the more cautious one (`[TO RESEARCH]` over `[UNVERIFIED PLACEHOLDER]`).
