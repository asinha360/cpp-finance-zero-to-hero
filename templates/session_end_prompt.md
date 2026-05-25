End session. Read these files in order, then run the closing sequence:

1. TASKS.md — current Now/Next/Done state
2. PROGRESS_ACTIVE.md — current state, next session block, open retrieval gaps
3. notes/wX_dY.md — today's log if it exists (X = curriculum week, Y = session number today)
4. DECISIONS.md — choices logged this session

After reading, execute each step in order. Do not summarise from memory — read the files.

Step 1 — Audit. State in one sentence each: what was attempted, what was completed, what was deferred.

Step 2 — Update TASKS.md. Move completed items to Done with today's date. Promote the next queued item to Now only if the user confirms.

Step 3 — Update PROGRESS_ACTIVE.md. Overwrite the ## Next session block with exactly three lines:
  **First action:** [one sentence; executable without reading anything extra]
  **Retrieval question:** [closing question, verbatim]
  **Carry-forwards:** [comma-separated, or "none"]
Update ## Open retrieval gaps: add any new gaps, remove any that scored 2/2 this session.
Update ## Current state: today's date, session count, today's artifact.
After writing, verify PROGRESS_ACTIVE.md is ≤40 lines. If over, move the oldest session-wins content to PROGRESS_HISTORY.md.

Step 3b — Append to PROGRESS_HISTORY.md. Under a header "## Session YYYY-MM-DD (WX DY)", append:
- Retrieval scores from this session (every prompt, 0/1/2 scored, with topic)
- Session wins (2–6 bullets: what was completed, bugs caught, concepts that landed, [FIRST TIME] tags)
Do not duplicate content already in the notes file — write the structured log only.

Step 4 — Write or append notes/wX_dY.md. If it exists, append under a dated header; never overwrite prior content.
Write as if future-Claude has zero memory of this session. All seven sections required; do not abbreviate:
- Session header: date, week/day, roles active, time, attempted vs completed.
- Exercises worked: identifier, objective, solo attempt?, hints given (rung + time + "why this direction" fragment), acceptance criteria result, implementation quality notes, Big O if discussed.
- Conceptual wins: what they said that proved they got it; tag [FIRST TIME] on first clean retrieval without scaffolding.
- Scaffolding log: what they believed, what was wrong, what was said, whether it landed. Write "none" if clean.
- Retrieval scores: every prompt this session, scored 0 (scaffolded) / 1 (hinted) / 2 (unaided).
- Momentum and blockers: pace vs schedule, next-session risk, one thing to re-test first.
- Next session's contract: first action, retrieval question, carry-forwards — then write the same into TASKS.md Now and PROGRESS_ACTIVE.md ## Next session.

Step 5 — Log decisions. If a non-trivial choice was made, add to DECISIONS.md using templates/decision-log-template.md. State explicitly if none.

Step 6 — Closing retrieval check. Ask the same question that opened this session. Score 0/1/2 and record in PROGRESS_ACTIVE.md ## Open retrieval gaps. If score < 2, add to carry-forwards.

Step 7 — Commit and push. Stage all modified workspace files. Commit with a message summarising the session
(e.g., "W5 D5: acceptance test pass + retrospective"). Push — no confirmation needed.
If no git repo: say so and list the files that should have been committed.

Confirm all of: TASKS.md updated, PROGRESS_ACTIVE.md updated, PROGRESS_HISTORY.md appended, notes file written, DECISIONS.md updated or explicitly
skipped, git tree clean. State the commit hash. That is "done."

Constraints:
- Do not invent content. Read the files; summarise what actually happened.
- Do not mark an exercise Done unless its acceptance criteria were confirmed green this session or in prior notes.
- Finance terms in notes must be defined on first use — do not assume the reader knows them.
- Hints in notes must include the "why this direction" fragment per the hint-style memory, not just a nudge.
- Do not skip Step 7 even if it feels like nothing changed.

Close.