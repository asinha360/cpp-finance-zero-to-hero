# Retrospective: Week 2 — Functions, Control Flow, Bond Pricer

**Date:** 2026-04-29
**Cycle covered:** 2026-04-23 → 2026-04-29
**Participants:** Aryaman, Claude (Learning Coach + Code Reviewer)

---

## What we set out to do

Week 2 goal: decompose logic into functions, use loops and conditionals, and build a bond pricer that sums discounted coupon cashflows plus a discounted face value. Acceptance criteria: `F=1000, r=0.05, y=0.05, n=5` → `1000.00`; `y=0.06` → below par. Secondary goal: understand the coupon rate (`r`) vs yield (`y`) distinction at a conceptual level, not just in code.

## What actually happened

The bond pricer was implemented and both acceptance criteria passed. Two blocking issues surfaced in code review: a missing `n <= 0` guard (specified on Day 1 but not coded) and WHAT comments that remained despite being flagged as removed in PROGRESS.md. Both were fixed. Retrieval practice on Day 3 confirmed most W1 and W2 concepts were solid; the main gap was C++ vocabulary (zero-overhead principle, syntax vs semantics) rather than conceptual understanding.

## What worked

- `r` vs `y` distinction landed cleanly — derived from the formula on Day 1 and retrieved unaided on Day 3 and again during code review.
- Loop off-by-one (`i < n+1` → `i <= n`) caught and fixed independently without prompting.
- Guard placement logic applied correctly for `y == -1.0`; `n <= 0` guard placed correctly after reading `n`.
- Debugging instinct developing — wrong guard variable (`r` vs `y`) caught from memory during implementation.
- Bond price / yield direction retrieved unaided in one shot on Day 3.

## What didn't work

- WHAT comments recorded as removed in PROGRESS.md but still present in code — session note written before cleanup actually happened, producing a false "done."
- `n <= 0` guard was in the Day 1 spec but not implemented — spec items need explicit tracking during implementation, not just noted at intake.
- Zero-overhead principle vocabulary wasn't retrievable unprompted — concept understood, label not retained after two prompts.

## Surprises

- Bond price / yield direction was retrieved correctly, but the mechanism had a specific inversion error: said "numerator drops" when the correct answer is "denominator grows." Intuition right; formula mapping was off.
- const-ref reasoning needed full scaffolding — expected since it hasn't been written in code yet. Retrieved correctly once framed.

## Decisions to revisit

- None logged in DECISIONS.md this cycle.

## What we'll change next cycle

1. After each session, verify "done" items in PROGRESS.md against the actual file — don't record a win until confirmed in the source.
2. Keep an explicit checklist of spec items during implementation so nothing from the Day 1 spec is silently dropped.

## Open follow-ups

- [ ] Re-test zero-overhead principle vocabulary — due 2026-05-03.
- [ ] Re-test const-ref reasoning once written in W3 code — due 2026-05-02.
- [ ] A key takeaway is that guards must be emphasized in c++ to prevent inaccurate use of meaningless output later in the workflow created by undefined behavior
- [ ] Since values cannot always be stored in binary accurately to the 14th sig fig -> using a tolerance range for comparison operators in guards is best practice
- [ ] Comments should emphasize 'why' never the 'what'
