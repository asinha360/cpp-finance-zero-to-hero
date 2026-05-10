# Code Review Template

> Structured review for any non-trivial diff. Use the Code Reviewer role from [AGENTS.md](../AGENTS.md). Reference issues with `path/to/file.ext:line` format.

---

## Review of: [PR title / commit / branch]

**Reviewer:** [name / "Claude as Code Reviewer"]
**Date:** [YYYY-MM-DD]
**Scope:** [what's in the diff]
**Out of scope:** [what's intentionally not being changed]

---

## Summary

[One sentence: does this look ready to merge, ready with changes, or needs significant rework?]

---

## Blocking issues

> Things that must be fixed before merge. If there are none, write "None."

- **[file.ext:line]** — [Issue]. [Why it's blocking.] [Suggested fix.]

## Suggestions (non-blocking)

> Improvements that would be nice but aren't merge-blockers.

- **[file.ext:line]** — [Suggestion]. [Reason.]

---

## Detailed checklist

### Correctness
- [ ] Logic matches the intended behavior described in the PR / task.
- [ ] Edge cases (empty input, null, boundary, concurrent) are handled or explicitly out-of-scope.
- [ ] Error paths fail safely (no silent swallowing, no leaking partial state).
- [ ] No off-by-one / loop-bound / type-coercion bugs.

### Security
- [ ] No user input flows to a sink unsanitized (SQL, shell, file paths, eval, HTML, redirects).
- [ ] No secrets or credentials introduced or logged.
- [ ] Authentication / authorization checks are in the right place (not bypassable).
- [ ] Dependencies added (if any) are reputable and version-pinned.

### Readability
- [ ] Names communicate intent.
- [ ] Functions stay focused; no functions that "do everything."
- [ ] Comments are present *only* where the why isn't obvious from the code.
- [ ] No dead code, no commented-out blocks, no `// TODO` without an issue number.

### Performance
- [ ] No obvious N+1 / quadratic loops on inputs that grow.
- [ ] No unnecessary allocations / re-computations in hot paths.
- [ ] No new blocking I/O in async paths (or vice versa).

### Tests
- [ ] Behavior is covered by tests proportional to risk.
- [ ] Tests assert behavior, not implementation details.
- [ ] Negative cases tested where they matter.
- [ ] Tests actually run (not skipped, not flaky).

### Style / conventions
- [ ] Matches surrounding code's style.
- [ ] No drive-by reformatting unrelated to the change.

---

## Notes for the author

[Anything contextual: tradeoffs they should know about, related work that might be affected, things to watch in production after merge.]
