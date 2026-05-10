# REFERENCE_RESEARCH_QUEUE.md

> Items that need external research before they can be cited as fact. Anything labeled `[TO RESEARCH]` in [REFERENCES.md](REFERENCES.md) (or anywhere else) belongs here. When verified, move the entry into [REFERENCES.md](REFERENCES.md) with a `[VERIFIED]` label and a real source link.

| Topic | Why it matters | Suggested sources | Status |
|---|---|---|---|
| Anthropic official prompting guide | Anchors the 5-part framework to the canonical reference | docs.anthropic.com (verify URL) | Open |
| Claude Code official documentation | Confirm correct paths/conventions for `.claude/` agents, skills, commands | Anthropic docs | Open |
| Public examples of well-regarded engineering RFCs | Concrete `[VERIFIED]` examples for [REFERENCES.md](REFERENCES.md) "excellent work" section | Open-source project RFC repos | Open |
| MoSCoW prioritization origin & canonical definition | Cited in REFERENCES.md as `[UNVERIFIED]` | Original DSDM publications or reputable PM source | Open |
| RICE scoring origin & formula nuances | Same as above | Intercom blog (original article) or successor sources | Open |
| Five Whys origin (Toyota / Sakichi Toyoda) | Same as above | Toyota production system primary sources | Open |
| Recommended max function length / nesting depth heuristics | Cited as `[UNVERIFIED]` in REFERENCES.md coding standards | Clean Code / Code Complete (with page references) or empirical studies | Open |
| Average sentence-length guidance for technical writing | Cited as `[UNVERIFIED]` in REFERENCES.md writing standards | Style guides (Plain Language, Microsoft Writing Style Guide) | Open |
| Subagent / skill examples from broader Claude Code community | Improve [.claude/skills/](.claude/skills/) and [.claude/agents/](.claude/agents/) sections of this workspace | Anthropic cookbook, community repos (verify before adding) | Open |

**Adding to this queue:** When Claude wants to cite a "fact" but can't verify it this session, add a row here and use a placeholder label in the source file. Don't fabricate.
