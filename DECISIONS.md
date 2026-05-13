# DECISIONS.md

Non-trivial choices, one entry each. Date, decision, reason, what would flip it.

---

## 2026-04-18 — Toolchain picks for the 16-week curriculum

**Context.** User is non-technical on macOS (Apple Silicon assumed — see [ASSUMPTIONS.md](ASSUMPTIONS.md)). Setup needed to be minimal, native, and free. See [setup.md](setup.md) for the full install guide.

**Decisions (one line each):**

- **Compiler: Apple Clang via Xcode Command Line Tools** (not Homebrew GCC). Reason: ships with macOS tooling, supports C++20, provides `g++` alias so curriculum commands work unchanged, bundles `lldb` and `git`. Flip if: we hit a GCC-only feature or Clang bug that blocks a week.
- **Debugger: `lldb` + VS Code CodeLLDB extension** (not `gdb`). Reason: `lldb` is the native Apple debugger; `gdb` needs code-signing workarounds on macOS. Flip if: we switch editors away from VS Code.
- **Editor: VS Code** (not Xcode, CLion, Vim, Emacs). Reason: gentlest learning curve for a non-coder, free, cross-platform, strong C++ + debugger extensions. Flip if: user wants a JetBrains workflow later.
- **Package manager: Homebrew** (not MacPorts, Nix, manual). Reason: de-facto standard on macOS, one-line installs, works on Apple Silicon and Intel. Flip if: we need reproducible builds across machines (then Nix).
- **Build system: plain `g++` invocations weeks 1–14, CMake from W15.** Reason: introducing CMake on day 1 would teach a second tool before the first one makes sense; project artifacts are single-file through W14. Flip if: we cross the multi-file threshold earlier than expected.
- **Test framework: `assert` weeks 1–14, GoogleTest from W15.** Reason: same rationale — one tool at a time. Flip if: we need parameterised tests earlier.
- **C++ standard: C++20** (not C++17 or C++23). Reason: curriculum already specifies `-std=c++20`; modern enough for ranges/concepts if useful; broadly supported by shipping Apple Clang. Flip if: Apple Clang version shipped with user's macOS doesn't fully support C++20 features we need.
- **GitHub (not GitLab/Bitbucket).** Reason: recruiters browse GitHub; milestone-4 portfolio lives there. Free tier is enough.
- **Install Homebrew in Group A** (even though first strict need is W5). Reason: avoids a mid-curriculum install detour and lets us install Python, CMake, etc. with one command later.
- **Group-B tools (Python, CMake, GoogleTest) deferred to just-in-time install.** Reason: minimises upfront friction for a non-technical user; nothing in W1–W4 needs them.

---

## 2026-05-05 — Guard placement in BS pricer: main() vs. inside functions

**Context.** `blackScholesCall`, `blackScholesPut`, `delta`, and `vega` all divide by `sigma * sqrt(T)`. If either is zero, the result is undefined. Guards were placed in `main()` (before user input reaches the functions) and also inside `blackScholesCall` and `blackScholesPut`.

**Decision.** Keep guards in both locations for now. Rationale: the interactive path is protected by `main()`; the function-level guards catch direct calls from tests or future callers.

**What would flip it.** In Day 4 code review: consolidate to function-level only, remove the `main()` guards, and add a test that calls the pricer directly with `sigma=0` to verify the function-level guard fires. This is the cleaner library-style pattern. Deferred because the current code is correct, and Day 2 is not the right moment to refactor.

---

---

## 2026-05-13 — GBMSimulator as local variable vs. member of MCPricer

**Context.** W6 Day 2: user tried to declare `GBMSimulator _simulator` as a private member of `MCPricer`. `GBMSimulator` has no default constructor — it requires S0, r, sigma, T, steps, seed. Also, `N` (number of paths) and `steps` (time steps per path) are different parameters; the user had conflated them.

**Decision.** Create `GBMSimulator` as a local variable inside `price_call()`, hardcoding `steps=252` and `seed=42` for now. Rationale: simplest correct solution at W6 skill level; avoids adding `steps` and `seed` as `MCPricer` constructor parameters before the user understands why they'd need them.

**What would flip it.** If we add variance reduction (W13) or parallel paths (W14), the simulator configuration will need to be more explicit. At that point, promote `steps` and `seed` to constructor parameters and initialize `_simulator` in the member initializer list.

---

## 2026-05-13 — Inline member function bodies in headers at W6

**Context.** W6 Day 2: header/source split introduced. User asked whether to put the full `MCPricer` class (including method bodies) in the header. Convention for large projects is declaration in `.h`, definition in `.cpp`. But at this scale (single-file compilation, small methods), everything inline in the header is simpler and correct.

**Decision.** Full class definition (including method bodies) in the header through at least W14. Rationale: the declaration/definition split is a compilation-speed optimization and a readability aid for large codebases — neither concern applies here. The full split will be introduced naturally with CMake in W15.

**What would flip it.** If any class grows beyond ~50 lines of method body, or if compilation time becomes noticeable, extract method bodies to `.cpp` earlier.

---

**Explicitly deferred / rejected.** Full Xcode IDE, GCC via Homebrew, Conan/vcpkg, Docker, valgrind — reasons noted in [setup.md](setup.md) "Deliberately omitted" section.
