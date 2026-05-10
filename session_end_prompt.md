You are the senior collaborator defined in CLAUDE.md. Execute the closing
sequence below in order. Do not invent content — read every file before
summarizing it. Confirm each step is complete before moving to the next.

───────────────────────────────────────────────
Step 1 — Audit what happened.
───────────────────────────────────────────────
Read TASKS.md and the session notes file (notes/wX_dY.md if it exists,
where X = current curriculum week, Y = session number today).

List in one sentence each:
- What was attempted this session.
- What was completed (acceptance criteria green, code review done, or
  concept fully retrieved).
- What was left unfinished or deferred.

Do not assume anything from prior context. Read the files.

───────────────────────────────────────────────
Step 2 — Update TASKS.md.
───────────────────────────────────────────────
Move completed items from Now → Done with today's date (2026-MM-DD format).
Move the next queued item into Now ONLY if the user confirms they want
to start it next session.
Do not delete anything from Done — it is the audit trail.

───────────────────────────────────────────────
Step 3 — Update PROGRESS.md.
───────────────────────────────────────────────
For every exercise or concept that was fully resolved this session
(acceptance criteria green, OR concept retrieved cleanly at the closing
check):
- Update the week's entry in the "Current state" section with wins.
- Add any new retrieval scores to the rolling table.
- Tag with [FIRST TIME] any concept the user articulated correctly and
  unprompted for the first time — no scaffolding, no hints.

If no exercise was completed and no concept was retrieved cleanly,
write one line stating that and why. Do not leave the section stale.

───────────────────────────────────────────────
Step 4 — Write (or append to) the session notes file.
───────────────────────────────────────────────
File: notes/wX_dY.md (X = active curriculum week, Y = session number
today). If the file already exists, append under a dated header —
do not overwrite prior content.

This file is the durable record. Write it as if future-Claude has zero
memory of what happened — because it doesn't. Every section is required.
Do not abbreviate or skip.

  4a. Session header.
      Date, curriculum week and day number, role(s) active
      (e.g., Learning Coach + Code Reviewer), estimated time spent,
      what was attempted vs. what was completed.

  4b. Exercises and concepts worked — one block per item.
      For each exercise (code artifact, retrieval drill, or spaced retest):

      - Identifier: weekXX/exercise name or "spaced retest — [topic]".
      - Learning objective: what concept this exercise was supposed to
        lock in (stated in CONTEXT.md or TASKS.md, or derived from the
        session).
      - Approach taken: did the user attempt solo before seeing code?
        What was the first attempt? What needed coaching?
      - Hints given: list each hint verbatim, in order. For each, state:
        which hint-ladder rung (1 = directional nudge, 2 = worked analogy,
        3 = direct answer) and how many minutes into the session it was given.
        Include the "why this direction" fragment per the hint-style memory.
      - Acceptance criteria result (for code exercises):
        - Did it compile clean under -Wall -Wextra -std=c++20?
        - Did the runtime output match the spec (exact values or tolerance
          bands from CONTEXT.md)?
        - If not: what failed, what was the root-cause hypothesis confirmed?
      - Implementation quality notes: any STL idiom issues, guard placement,
        off-by-ones, variable naming, or silent-error anti-patterns flagged
        in review. Note whether the user caught each issue independently,
        after a hint, or only after being told.
      - Complexity note (required for W9+; optional for W1–W8): if Big O
        was discussed, record the claim, whether it was user-derived or
        Claude-given, and the derivation reasoning. Build incrementally;
        never lecture standalone. (Per the Big-O memory: W3, W9, W13 are
        hot spots.)

  4c. Conceptual wins.
      List every concept or pattern the user articulated correctly and
      unprompted this session. These are the things they own now.
      Format: "Concept — what they said that proved they got it."
      Tag with [FIRST TIME] on first clean retrieval without scaffolding.

  4d. Scaffolding log.
      List every place where the user needed help beyond the hint ladder —
      a concept explained outright, an answer given, a misconception
      corrected. For each:
      - What the user believed or tried.
      - What was wrong about it.
      - What was said to correct it.
      - Whether the correction landed (did they paraphrase it back?).

      This log drives next session's spaced retrieval. Write "none" if
      nothing needed scaffolding — do not omit the section.

  4e. Retrieval scores.
      List each retrieval prompt asked this session with the score (0/1/2)
      and one sentence on what the user got right or wrong.
      Include the opening spaced-retest question and the closing check
      from Step 6.

      Score key: 0 = needed scaffolding or answer given; 1 = correct with
      at least one hint; 2 = correct, unaided.

  4f. Momentum and blockers.
      One paragraph. Is the user ahead of pace, on pace, or behind for
      this curriculum week? What specific concept or implementation detail
      is most likely to block them next session? What is the one thing to
      re-test at the very start of next session?

  4g. Next session's contract.
      - First action: one sentence, specific enough to execute without
        reading anything extra (e.g., "Open projects/week05/rng_harness.cpp
        and run the acceptance test; paste the output").
      - The single retrieval question to open with next session.
      - Carry-forward items: unfinished exercises, unresolved failures,
        concepts that scored 0 or 1 this session.

      After writing 4g in the notes file, write the same information into
      the two authoritative state files so the session-start prompt picks
      it up without reading notes/:

      → TASKS.md: replace the contents of the ## Now section with the
        first action from 4g as a single task item. Append carry-forward
        items as additional items under Now. Do not touch Next or Done.

      → PROGRESS.md: overwrite the ## Next session block (create it if
        absent, directly below ## Current state) with exactly three lines:
          **First action:** [first action from 4g]
          **Retrieval question:** [the question, verbatim]
          **Carry-forwards:** [comma-separated list, or "none"]
        Overwrite the entire block each session — it always reflects the
        single most recent contract.

───────────────────────────────────────────────
Step 5 — Log decisions if any were made.
───────────────────────────────────────────────
If a non-trivial choice was made this session (curriculum adjustment,
data-structure selection, approach change, scope change to an artifact's
spec), add an entry to DECISIONS.md using the template at
templates/decision-log-template.md: what, rationale, flip-condition.

If no non-trivial decisions were made, say so and skip this step.

───────────────────────────────────────────────
Step 6 — Closing retrieval check.
───────────────────────────────────────────────
Ask the user the same spaced-retrieval question that opened this session.
Score the answer 0/1/2 and record it in PROGRESS.md's rolling table.
If the score is lower than 2, flag it — re-test it at the very start
of next session and note it in the carry-forwards.

───────────────────────────────────────────────
Step 7 — Commit and push.
───────────────────────────────────────────────
Check whether this directory is a git repository (git status).
If yes: stage all modified workspace files and project artifacts, commit
with a message summarising the session (e.g., "W5 D5: acceptance test
pass + retrospective"), and push to the remote. Do not skip. Do not ask
whether to run it.
If no git repository: flag it explicitly — "No git repo initialised.
Run 'git init && git remote add origin <url>' to enable /sync." Then
list the files that should have been committed so the user can do it
manually.

───────────────────────────────────────────────
Verification (after Step 7).
───────────────────────────────────────────────
Confirm all of the following:
- TASKS.md updated: completed items in Done, Now reflects next action.
- PROGRESS.md updated: current-state wins logged, next-session block
  overwritten, retrieval table has today's scores.
- notes/wX_dY.md written or appended: all seven sections present.
- DECISIONS.md updated or explicitly skipped.
- Git working tree clean and pushed (or blockage explained).
State the commit hash (or explain the blockage). That is "done."

───────────────────────────────────────────────
Constraints.
───────────────────────────────────────────────
- Do not invent content. Read the files; summarise what actually happened.
- Do not mark an exercise Done if its acceptance criteria have not been
  confirmed green in the session or in a prior session's notes.
- Do not skip Step 7 — even if it feels like nothing changed. The working
  tree should be clean at the end of every session.
- Finance terms (PV, VaR, yield, σ, etc.) must be defined if used in
  notes — do not assume the reader knows them.
- Hints in 4b must include the "why this direction" fragment, not just
  the nudge. (See hint-style memory.)
- Big O analysis in 4b is incremental — build on what was said in context;
  never insert a standalone lecture.