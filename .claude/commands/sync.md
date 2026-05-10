Commit and push all workspace changes to GitHub.

Execute the following steps in order:

1. Run `git status` to check the working tree.
   - If it is already clean, report "Working tree clean — nothing to commit." and stop.

2. Run `git diff --stat HEAD` to summarise what changed.
   Print the summary to the user in one sentence: which file types changed
   (e.g., "notes, TASKS.md, PROGRESS.md, 1 .cpp file").

3. Stage all changes:
   `git add .`
   Do not use `--no-verify` or any flag that bypasses hooks.

4. Commit with a message derived from the staged content.
   Format:
     <week-and-day label if inferable from notes/ changes>: <one-line summary>

   Examples:
     "W5 D5: acceptance test pass + retrospective"
     "W5 D4: code review complete + TASKS.md updated"
     "session close: PROGRESS.md + notes updated"

   Use a HEREDOC so special characters in the message are safe:
   ```
   git commit -m "$(cat <<'EOF'
   <your message here>

   Co-Authored-By: Claude Sonnet 4.6 <noreply@anthropic.com>
   EOF
   )"
   ```

5. Push to origin:
   `git push`

6. Confirm success: run `git log --oneline -1` and `git status`.
   Report the commit hash and confirm the working tree is clean.
   That is "done."

Constraints:
- Never use `--force` or `--no-verify`.
- Never commit files matching .gitignore (compiled binaries, .dSYM, .DS_Store).
- If the push fails (e.g., remote has diverged), report the error and ask
  the user how to resolve it — do not attempt a force push.
- When new compiled binaries appear in projects/ that are not yet in
  .gitignore, add them to .gitignore before staging, then commit both
  the .gitignore update and the session changes together.
