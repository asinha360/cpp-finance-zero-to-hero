# ASSUMPTIONS.md

Things I proceeded on without user confirmation. Each entry has a date, the assumption, the blast radius if wrong, and how to confirm or flip it.

---

## 2026-04-18 — Machine assumptions for environment setup

Made while writing [setup.md](setup.md) and [DECISIONS.md](DECISIONS.md).

| # | Assumption | Blast radius if wrong | How to confirm / flip |
|---|---|---|---|
| 1 | Host OS is **macOS** (Darwin 25.4.0 reported by environment). | Entire setup guide is Mac-specific — wrong OS means starting over. | User opens Terminal and runs `uname`; expects `Darwin`. |
| 2 | Mac is **Apple Silicon** (M1/M2/M3/M4), post-2020. | Homebrew default path `/opt/homebrew/bin` vs. Intel's `/usr/local/bin`. Flagged inline in setup.md. | `uname -m` → `arm64` (Apple Silicon) or `x86_64` (Intel). |
| 3 | User has **admin/sudo privileges** on this Mac. | Xcode CLT and Homebrew installs both require the login password. Without it, setup halts at Step 1. | User is prompted for password and it works. |
| 4 | At least **8 GB RAM**, **10 GB free disk**. | Xcode CLT (~3–5 GB) + VS Code + Homebrew formulae will eventually bump this. W14 parallelism benefits from ≥ 4 cores. `[UNVERIFIED PLACEHOLDER]` | `About This Mac` → Memory/Storage. |
| 5 | **Stable internet** for the one-time downloads (CLT, Homebrew, VS Code, extensions). | Step 1 and Step 3 each pull 100 MB–3 GB; intermittent connection causes partial installs that are painful to recover from. | User runs the installs on a reliable network. |
| 6 | User's Mac is running a **recent enough macOS** that Apple Clang supports `-std=c++20`. `[UNVERIFIED PLACEHOLDER]` | If the OS is years old, C++20 features may be missing and the smoke test fails with "unknown argument '-std=c++20'". | `sw_vers -productVersion` — flag if < macOS 12. |
| 7 | User is comfortable entering their **Mac login password** at terminal prompts (it's the same password as their user account). | Non-blocking; user may be surprised the terminal shows no dots while typing. Flagged inline in setup.md. | N/A — just a UX expectation. |
| 8 | User has a **personal email** available for GitHub signup. | GitHub rejects some disposable email domains. | User signs up successfully. |

**Action.** If any of these is wrong, user should stop and tell me before running setup.md.

---

## 2026-04-18 — User has no finance background (correction)

[CONTEXT.md:17-19](CONTEXT.md#L17-L19) describes the user as "finance-curious, mathematically comfortable through undergrad calculus and probability." In session on 2026-04-18 the user clarified explicitly: **no finance background at all**. "Finance-curious" = interested, not informed.

**Blast radius:** Any finance concept (PV, FV, coupon, yield, volatility, VaR, Black-Scholes, etc.) used without derivation lands as jargon, not teaching. Affects pedagogical approach for all 16 weeks.

**How to apply:**
- Derive every finance concept from first principles on first use.
- Math analogies (calculus, probability) are safe; finance analogies are not.
- Do not use phrases like "like pricing a zero-coupon bond" as explanatory analogies.

**How to flip:** User tells me otherwise, or demonstrates recall of a finance concept without lookup.
