# setup.md — Environment Setup for cpp-finance-zero-to-hero

You're non-technical. This file assumes zero. Every jargon term is defined the first time it appears, using a finance/math analogy when one helps.

> **Machine assumptions (flagged — see [ASSUMPTIONS.md](ASSUMPTIONS.md))**
> - macOS (the environment reports Darwin 25.4.0 — macOS).
> - Apple Silicon (M1/M2/M3/M4). If you're on an Intel Mac, the commands still work; I'll flag the one spot it matters.
> - ≥ 8 GB RAM, ≥ 10 GB free disk, reliable internet, admin password for your Mac.
> - If any of these are wrong, stop and tell me before running anything.

---

## Vocabulary (one-time definitions)

- **Terminal** — a text window where you type commands instead of clicking buttons. Think: an Excel formula bar for your whole computer.
- **Shell** — the program inside the terminal that reads your commands. On modern macOS it's `zsh`. Think: the parser that turns `=SUM(A1:A10)` into an answer.
- **Command** — a single instruction you type. Like `=PV(0.05,3,,1000)` but for files and programs.
- **Package manager** — a tool that installs other tools for you, like an app store for developers. We'll use **Homebrew**. Analogy: a Bloomberg terminal's `ADD` function — one command, pulls the data/tool from a trusted source.
- **PATH** — a list of folders the shell searches when you type a command name. If a tool "isn't on your PATH," the shell can't find it even though it's installed. Analogy: a list of sheets Excel will search for a named range.
- **Compiler** — a program that turns human-readable C++ source code into a machine-runnable executable. Analogy: a quant model that takes inputs and produces a priced instrument.
- **Linker** — the last step of compiling. It stitches together separately-compiled pieces into one runnable program. Analogy: consolidating sub-models into one P&L.
- **Header file** — a C++ file (ending `.h` or `.hpp`) that declares "here's what exists." Different from a **source file** (`.cpp`), which defines "here's how it works." Analogy: a term sheet (header) vs. the full legal contract (source).
- **Debugger** — a tool that pauses your program at chosen spots so you can inspect values. Analogy: stepping through a pricing workbook cell-by-cell.
- **Build system** — a tool that runs your compiler on many files in the right order. We'll use **CMake** later. Analogy: the macro that runs all your sub-models in sequence.
- **Repository ("repo")** — a folder whose changes are tracked by **Git**. Analogy: a versioned Dropbox for code with every edit labeled.
- **Version pin** — writing down the exact version of a tool so your code behaves the same later. Analogy: specifying EOD close vs. intraday snap when reproducing a backtest.

---

## TASK 1 — Forward scan of all 16 weeks

Every tool, library, dataset, and account the curriculum touches, pulled from [curriculum.md](curriculum.md) end-to-end.

**Pedagogical/technical claim labels per [REFERENCES.md](REFERENCES.md) §7** — no `[VERIFIED]` entries below yet because I haven't read the official docs in this session. Upgrade to `[VERIFIED]` when you install and confirm.

### Group A — INSTALL NOW (weeks 1–4)

| Tool | Version (pinned / "latest stable") | First used | Why | Cost | macOS notes |
|---|---|---|---|---|---|
| Xcode Command Line Tools | latest stable `[UNVERIFIED PLACEHOLDER]` | W1 | Ships Apple Clang (C++ compiler), `lldb` (debugger), `make`, `git` in one bundle | Free | macOS-only. Not needed on Windows/Linux. |
| Apple Clang (C++20) | whatever CLT ships; target `-std=c++20` | W1 | Compile C++ code. `g++` is a symlink to Clang on macOS so the curriculum's `g++` commands work unchanged. `[UNVERIFIED PLACEHOLDER]` | Free (bundled with CLT) | On Linux, use `g++` from distro; on Windows, use MSYS2/MinGW or WSL. |
| lldb (debugger) | bundled with CLT | W1 | Step through a running program and inspect variables | Free | On Linux use `gdb`; on Windows use MSVC's debugger or `gdb` under MSYS2. |
| git | bundled with CLT | W1 | Track every edit, push projects to GitHub later | Free | Same tool on all three OSes. |
| GitHub account | n/a | W1 (create now, used heavily W15–16) | Host your portfolio repos; recruiters browse GitHub | Free tier fine | Signup at github.com; same on all OSes. |
| Homebrew | latest | W1 (prereq for later tools) | macOS package manager; one-line installs for everything below | Free | macOS/Linux. On Windows use `winget`/`choco`. |
| Visual Studio Code | latest stable | W1 | Text editor with debugger UI, terminal, Git panel in one window | Free | Same app on all OSes. |
| VS Code extension: `ms-vscode.cpptools` (C/C++) | latest | W1 | Syntax highlighting, IntelliSense, build/run tasks for C++ | Free | Same on all OSes. |
| VS Code extension: `vadimcn.vscode-lldb` (CodeLLDB) | latest | W1 | Graphical debugger UI that drives `lldb` under the hood | Free | macOS/Linux. On Windows prefer `ms-vscode.cpptools`'s built-in debugger. |

### Group B — INSTALL LATER (weeks 5–16)

Installed just-in-time at the start of the week that needs them. Noted here so you're not surprised later.

| Tool | Version | First used | Why | Cost | Notes |
|---|---|---|---|---|---|
| Python 3 | 3.11+ `[UNVERIFIED PLACEHOLDER]` | W7 | Independent reference calculation to verify your C++ stats match | Free | macOS ships one, but install via Homebrew for a cleaner version. |
| Daily price CSV (e.g., SPY) | n/a | W7 | Real historical data to parse | Free | Source: Stooq or Yahoo Finance CSV export `[TO RESEARCH]`. You download once; no API needed. |
| CMake | 3.25+ `[UNVERIFIED PLACEHOLDER]` | W15 (earlier optional) | Build system that scales past a single `g++` command | Free | `brew install cmake`. |
| GoogleTest | latest | W15 | Proper unit-test framework (replacing `assert`) | Free | Vendored via CMake's `FetchContent` — no global install needed. |
| Synthetic tick CSV | n/a | W9 | Input for the OHLC aggregator | Free | Generated by a small script we'll write. |

### Group C — OPTIONAL / NICE-TO-HAVE

| Tool | When it helps | Why | Cost |
|---|---|---|---|
| VS Code extension: `twxs.cmake` + `ms-vscode.cmake-tools` | W15+ | CMake syntax + build buttons inside VS Code | Free |
| VS Code extension: `usernamehw.errorlens` | W1+ | Shows compiler errors inline on the line, not in a separate panel | Free |
| `clang-format` | any time | Auto-format your code to a consistent style | Free (bundled with CLT) |
| `gnuplot` or Python `matplotlib` | W5, W9, W13 | Visualise histograms / P&L curves | Free |
| Apple Instruments (profiler) | W13 | Native macOS profiler for the speedup milestone | Free (ships with Xcode) |

**Deliberately omitted and why (one line each):**
- **Xcode (the full IDE)** — the Command Line Tools are a 3–5 GB subset that gives us everything we need; the full Xcode is ~40 GB and buys us nothing for this project. `[UNVERIFIED PLACEHOLDER]`
- **GCC via Homebrew** — Apple Clang is already installed via CLT, supports C++20, and integrates natively with macOS tooling; adding GCC is a second compiler to maintain for no benefit here.
- **Conan / vcpkg (C++ package managers)** — overkill until we depend on many third-party libraries; GoogleTest via CMake's FetchContent is sufficient for the whole curriculum.
- **Docker** — not needed on a single-developer Mac setup; adds a layer of indirection you'd have to learn.
- **valgrind** — poor/no support on Apple Silicon macOS `[UNVERIFIED PLACEHOLDER]`; we'll use Clang's AddressSanitizer/UndefinedBehaviorSanitizer (`-fsanitize=address,undefined`) instead when needed in W13–14.

---

## TASK 2 — Step-by-step install guide (Group A, in dependency order)

**Ground rules before you start.**
1. Do steps in order. Each step depends on the one above.
2. After every "verify it works" block, **if the output doesn't match, stop and tell me**. Don't move on.
3. When a command says `$ …`, don't type the `$` — that's just the shell's prompt. Type what comes after.
4. Every time you paste a command, read it first. Never run a command from the internet you don't understand.

### Step 0 — Open the Terminal

1. Press `⌘ + Space` → type `Terminal` → press Return.
2. A window opens with a prompt ending in `%` or `$`.
3. Type `echo hello` and press Return.

**Verify it works.** Expected output:
```
hello
```
**If you see something different:** stop and tell me; don't proceed.

---

### Step 1 — Xcode Command Line Tools (ships the compiler + debugger + git)

**What this gives you:** `clang` (C++ compiler, aliased as `g++`), `lldb` (debugger), `git`. One install, three tools.

Run:
```
xcode-select --install
```

**What you should see on screen:**
- A macOS popup appears with a button "Install".
- Click **Install**, then **Agree** to the licence.
- A progress bar downloads ~1–3 GB. Takes 5–30 minutes depending on internet. `[UNVERIFIED PLACEHOLDER]`
- When done, the popup closes.

**Common failure + fix.** If the popup says "Can't install the software because it is not currently available from the Software Update server", your Mac's Software Update catalog is confused. Fix: open **System Settings → General → Software Update**, install any pending OS update, reboot, retry.

**Verify it works.** In the terminal:
```
clang --version
git --version
lldb --version
```
Expected (versions will differ; the point is each command prints a version line, not an error):
```
Apple clang version 15.x.x (or later)
git version 2.x.x (Apple Git-...)
lldb-1500.x.x.x (or later)
```
**If any command says "command not found":** stop and tell me.

---

### Step 2 — Create a GitHub account (takes 2 minutes, blocks later weeks)

1. Go to `https://github.com/signup` in a browser.
2. Sign up with your email. Pick a professional username — this becomes part of your portfolio URL.
3. Verify your email.

**Verify it works.** You can log in at `https://github.com` and see a homepage with "Create repository" available. No command to run yet — we'll connect Git to GitHub in a later week.

**Common failure + fix.** GitHub blocks some throwaway email domains. Use a real personal email, not a temporary one.

---

### Step 3 — Homebrew (the package manager we'll use for everything else)

**Why now:** even though no Group-A tool strictly needs Homebrew, we'll need it repeatedly from W5 onward. Installing it now avoids a detour later.

Run the official install command `[UNVERIFIED PLACEHOLDER]` (copy it from `https://brew.sh` to be safe — only run the one command shown on that page; don't copy from anywhere else):
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**What you should see on screen:**
- It prints "This script will install..." and lists folders it will create.
- Asks for your Mac login password (you'll type it — the terminal won't show dots; that's normal).
- Downloads and installs for 2–5 minutes. `[UNVERIFIED PLACEHOLDER]`
- Near the end it prints a "Next steps" block with **two lines to run**, something like:
  ```
  echo >> /Users/<you>/.zprofile
  echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/<you>/.zprofile
  eval "$(/opt/homebrew/bin/brew shellenv)"
  ```
  **Run exactly the two lines Homebrew prints**, not what I wrote above. They put `brew` on your PATH (remember PATH = list of folders your shell searches).

> **Intel Mac note.** On an Intel Mac the path is `/usr/local/bin/brew` instead of `/opt/homebrew/bin/brew`. Homebrew's installer prints the right path for your Mac — trust its output over mine.

**Verify it works.** Close and reopen the terminal window (important — PATH updates take effect in a new shell), then:
```
brew --version
```
Expected:
```
Homebrew 4.x.x
```
**If you see "command not found":** the PATH step didn't take. Stop and tell me.

---

### Step 4 — Visual Studio Code (your editor + debugger UI)

**Why VS Code and not Xcode / Sublime / Vim:** VS Code has the gentlest learning curve for a non-coder, has a first-class C++ extension, runs the debugger visually, and works identically on Mac/Windows/Linux if you ever switch. One line to justify the pick.

Install via Homebrew (cleaner than dragging the `.app` from a download):
```
brew install --cask visual-studio-code
```

**What you should see on screen:**
- Terminal prints "Downloading..." then "Installing Cask visual-studio-code" then "was successfully installed!".

**Verify it works.**
```
code --version
```
Expected (three lines — VS Code version, a commit hash, and your architecture):
```
1.x.x
<commit-hash>
arm64          (or x64 on Intel Mac)
```
Also: open VS Code from Applications or by typing `code` in the terminal. Window opens. **If `code` says "command not found":** in VS Code press `⌘ + Shift + P`, type `Shell Command: Install 'code' command in PATH`, press Return. Then reopen the terminal and retry.

---

### Step 5 — VS Code C++ extensions

In VS Code, open the Extensions pane (`⌘ + Shift + X`). Install these two, one at a time:

1. **C/C++** (publisher: Microsoft, extension ID `ms-vscode.cpptools`). This is the only extension strictly required. It provides IntelliSense (autocomplete), error underlines, and a build/run task.
2. **CodeLLDB** (publisher: Vadim Chugunov, extension ID `vadimcn.vscode-lldb`). This gives you the graphical debugger UI that drives `lldb`. Needed for the W1 acceptance test ("Debugger breakpoint hits on the discount line").

**What you should see on screen:** the Install button for each turns into a gear/"Manage" icon, confirming it's active.

**Verify it works.** Restart VS Code. In the bottom status bar of any C++ file you'll eventually see an IntelliSense indicator. We'll fully verify this in the end-to-end smoke test below.

---

### Step 6 — Create a project folder on disk

Your curriculum already has a workspace folder. Make a sub-folder for your weekly code so we don't clutter the root.

```
cd ~/my-first-workspace/cpp-finance-zero-to-hero
mkdir -p projects/week01
```

**Vocabulary.** `cd` = "change directory" (walk into a folder). `mkdir -p` = "make directory, including parents if missing; don't error if it already exists."

**Verify it works.**
```
ls projects
```
Expected:
```
week01
```

---

### Step 7 — End-to-end smoke test

This proves the full toolchain works: editor → compiler → linker → executable → terminal output.

1. In VS Code: **File → Open Folder…** → pick `~/my-first-workspace/cpp-finance-zero-to-hero`.
2. In the VS Code file tree, right-click `projects/week01/` → **New File** → name it `hello.cpp`.
3. Paste exactly:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, finance" << std::endl;
    return 0;
}
```

4. Save with `⌘ + S`.
5. Open VS Code's built-in terminal: **View → Terminal** (or `` Ctrl + ` ``). A shell opens at the project root.
6. In that terminal:

```
cd projects/week01
g++ -Wall -Wextra -std=c++20 hello.cpp -o hello
./hello
```

**What the commands mean (non-obvious once, then you know forever):**
- `g++` — invoke the compiler.
- `-Wall -Wextra` — turn on the compiler's warnings (it'll tell you about suspicious code).
- `-std=c++20` — use the 2020 version of the C++ language.
- `hello.cpp -o hello` — compile this source file; name the resulting executable `hello`.
- `./hello` — run the executable in the current folder (`./` means "here").

**Verify it works.** Expected output:
```
Hello, finance
```

**If you see `Hello, finance`** — toolchain confirmed. Everything from Groups A is working end-to-end. Stop here and tick the checklist below.

**Common failure modes + fixes.**
- `g++: command not found` → Step 1 (Xcode CLT) didn't complete. Re-run `xcode-select --install`.
- `error: unknown argument '-std=c++20'` → your Clang is too old. Run `xcode-select --install` to refresh, or `softwareupdate --install -a` to update macOS.
- `./hello: No such file or directory` → `g++` reported errors and didn't produce the binary. Read the error above `./hello` in the terminal; fix the source file.
- `Permission denied` running `./hello` → almost never happens in the project folder; if it does, run `chmod +x hello` and retry.

---

## TASK 3 — Pre-flight checklist

Tick every box before Week 1 begins. If any one fails, stop and tell me.

- [ ] Terminal opens and `echo hello` prints `hello`
- [ ] `clang --version` prints an Apple clang version
- [ ] `git --version` prints a git version
- [ ] `lldb --version` prints an lldb version
- [ ] GitHub account exists and I can log in
- [ ] `brew --version` prints a Homebrew version in a **new** terminal window
- [ ] `code --version` prints three lines (version, commit, architecture)
- [ ] VS Code has **C/C++** and **CodeLLDB** extensions installed
- [ ] `projects/week01/` folder exists under the project root
- [ ] Smoke test: `./hello` prints exactly `Hello, finance`

---

**Ready for Week 1 once setup.md checklist is complete. Tell me when you've ticked every box.**
