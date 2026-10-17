<div align="center">

# SOCIEDADE DE TRISTRAM
### A small Diablo I passion project — built to keep Tristram alive.

**Fan-made expansion · Experimental C++ game modding · Brazilian Portuguese**

**Status: Active development / work in progress**  
[Português (Brasil)](README.pt-BR.md) · [Development roadmap](#development-roadmap) · [Credits](#credits--original-projects)

</div>

> **A personal project, not an official release.** I have played Diablo since 1996. After all these years, I still love its world, atmosphere, and the possibilities hidden in its systems. Sociedade de Tristram is my small, ongoing attempt to build some of the things I always wished I could experience there. I am learning as I go, and I care more about making something thoughtful than claiming it is finished.

## What is this project?

**Sociedade de Tristram** is an experimental gameplay-expansion project for Diablo I, developed **on top of Diablo: The Heaven**, itself derived from **The Hell 4**. It explores new quests, companion mechanics, items and gems, better interfaces, more convenient inventory interactions, and development tools.

This repository is a **workbench**, not a polished mod download. Some work is integrated into `main`, some is isolated in feature branches, and some exists only on the roadmap. Compiling successfully does not imply every feature has been tested in gameplay. Expect changes, incomplete work, and bugs.

### Three distinct workstreams

| Workstream | Purpose | Boundary |
| --- | --- | --- |
| **Sociedade de Tristram — gameplay expansion** | Custom systems, quests, companions, items, UI, and balance experiments | **Changes gameplay** |
| **Portuguese localization — The Hell 3** | Faithful PT-BR translation of the upstream mod | **Translation only: no custom Sociedade de Tristram mechanics** |
| **Portuguese localization — The Heaven** | Faithful PT-BR translation of the upstream mod | **Translation only: no custom Sociedade de Tristram mechanics** |

The two translation-only tracks are **separate localization goals**, not claims that finished independent releases exist in this repository. The Heaven is based on The Hell 4; **The Hell 3 is a separate upstream mod**, not the codebase underneath Sociedade de Tristram.

## What we've started building

These items describe development work visible in the source, not a promise of release-ready behavior.

### 🐾 Original companion system

The companion feature is **an addition made for Sociedade de Tristram**, **not** an original Diablo I feature and **not** something inherited from The Heaven.

- Companion unlocks, selection, and in-game summon/dismiss actions are represented in the code.
- A companion dialogue/menu exists through Farnham, along with an inventory-side control.
- Character-specific data structures cover **experience, levels, affinity, progression/evolution stages**, and bonuses.
- Current companion characters include **Jason Funderburker, Kuroko, Mizuki, Thor, Lord, and Pitty**.
- Long-term direction: a **proper dedicated companion window**, cleaner management, equipable skills, distinctive builds, and meaningful late-game progression.

**Current limitation:** the in-game menu is an early interface; the standalone management window and complete equipable-ability UX remain planned/in development.

### 🧰 Inventory, equipment, and quality of life

- Inventory auto-organization and quick inventory controls have code implementations.
- PT-BR text/tooltip work and review of the correct equipment slots and item categories.
- Work on socketing, gemstone interactions, item behavior, and safe resource/currency handling.
- Ongoing usability work on item grouping, inventory layout, and less intrusive companion controls.

### 📜 Quests and world-building

- Quest availability and quest-generation logic are being investigated and adjusted.
- **The Forgotten House** has a map asset in a **development branch** (`feature/configurable-rates`), but is **not represented as a completed, fully verified quest in `main`**.
- Our ambition is to make exploration and the people of Tristram matter through small, atmospheric stories, rather than just adding more combat.

### 🔬 Testing and developer tools

We are building tools to **make it easier to reproduce problems and test changes responsibly**, especially while experimenting with legacy C++ systems.

- A lightweight diagnostic recorder has been implemented in the **`feature/diagnostics-foundation` branch**, with a bounded in-memory event buffer and a manual `Diagnostics/Session.log` snapshot.
- Win32/MSBuild compilation and diagnostic-log workflows are part of our development process. Some diagnostic batch/PowerShell scripts have been used locally and should **not** be assumed to be published here.
- An **in-game admin/debug command for creating and inspecting test equipment** is on the active development list, along with restoring/stabilizing its shortcut and UI across branches.
- Planned: stronger crash/resource breadcrumbs, map-transition diagnostics, item-generation validation, and repeatable test checklists.

**Note:** the diagnostic groundwork is not being advertised as a complete crash-reporting product. It is a small tool being built alongside the mod.

## Development roadmap

Checkboxes below are **work to complete**, not a list of shipped features. Priorities and designs may change.

### Companions

- [ ] Replace the dialogue-heavy workflow with a dedicated companion window.
- [ ] Make XP, levels, affinity and evolution readable in one place.
- [ ] Finish skill-gem/equipable-ability interactions and skill descriptions.
- [ ] Differentiate companion roles, behavior and scaling in the endgame.
- [ ] Test unlock persistence, summon states, saves, and multiplayer restrictions.

### Items, crafting and UI

- [ ] Stabilize the **admin item creation/testing command**, hotkey and equipment inspector.
- [ ] Complete the item-slot and translation audits (including unique/set/accessory edge cases).
- [ ] Refine inventory organization with useful grouping by type and layout controls.
- [ ] Explore **hybrid gem fusion**: combining *different* gem types for distinct, balanced effects.
- [ ] Separate hybrid fusion from existing **same-gem grade upgrades**; define recipes, costs, UI, and restrictions.
- [ ] Improve socketing, unique-item refinement, quenching safety, and their edge-case tests.
- [ ] Make gameplay rates configurable where practical, with predictable defaults.

### Lore quests — concepts to design and finish

These are **proposed story hooks, not completed quests**. Each should ultimately include dialogue, gameplay triggers, level integration, rewards, and save-state tests.

- [ ] **The Forgotten House** — finish the existing prototype: a sealed home, traces of its missing occupants, and a secret worth uncovering.
- [ ] **Ashes for Adria** — expand Adria's story through an investigation with consequences; consider a persistent character or encounter after completion.
- [ ] **The Letters Never Delivered** — piece together unsent correspondence between townsfolk, with clues distributed across dangerous areas.
- [ ] **The Bell Without a Tower** — discover why a bell is heard beneath Tristram, and who wants its sound forgotten.
- [ ] **Farnham's Last Promise** — a quest anchored in Farnham's memory and guilt, written without flattening his character.
- [ ] **Beneath the Old Cemetery** — reward careful exploration with a hidden location, meaningful lore, and more than an empty room.

**Quest design principle:** curiosity should be rewarded. The stories should feel rooted in Diablo's atmosphere and respect existing lore; ideas above are subject to revision and lore checks.

### Reliability, documentation and packaging

- [ ] Integrate and test appropriate diagnostic components from the feature branch.
- [ ] Make reproducible build/debug instructions match the actual project layout.
- [ ] Add targeted checks for crashes, corrupted states, portal/map transitions, and save compatibility.
- [ ] Consolidate feature branches safely; avoid claiming experimental features are present in `main`.
- [ ] Publish screenshots, examples, clear release notes, and installation instructions **when a tested build is ready**.

## Translation-only projects (PT-BR)

Our localization efforts deserve their **own identity**. The goal is to let Brazilian players enjoy the original mod experience **without adding Sociedade de Tristram's companions, quests, equipment, or gameplay changes**.

### The Hell 3 — PT-BR only
- [ ] Establish a version-specific baseline and inventory of translatable strings.
- [ ] Translate and proofread interfaces, dialogues, quests, item descriptions, and tooltips.
- [ ] Verify text widths, terminology, accents/encoding, and in-game behavior.
- [ ] Package localization-only changes separately; preserve upstream gameplay.

Upstream: [Diablo: The Hell 3 on ModDB](https://www.moddb.com/mods/diablo-the-hell-3).

### The Heaven — PT-BR only
- [ ] Establish a clean upstream The Heaven baseline, **without Sociedade de Tristram alterations**.
- [ ] Isolate PT-BR translation changes from features and balance experiments.
- [ ] Review consistent item names, classes, quests, NPC text, and tooltip formatting.
- [ ] Test and eventually publish translation-only instructions/patches separately.

Upstream: [Diablo: The Heaven](https://github.com/roboserg/diablo-1-the-heaven).

These tracks are localization plans/work in progress; **no completed standalone translation release is implied** by the checklists.

## Source code and development branches

The C++ solution and original upstream documentation are inside [`Sociedade de Tristram/TH/`](Sociedade%20de%20Tristram/TH). The original [The Heaven README](Sociedade%20de%20Tristram/TH/README.md), [build notes](Sociedade%20de%20Tristram/TH/docs/BUILD.md), and [upstream changelog](Sociedade%20de%20Tristram/TH/docs/CHANGELOG.md) are retained for technical reference; **they describe the upstream project and must not be mistaken for a tested Sociedade de Tristram release**.

Selected working branches:
- [`feature/diagnostics-foundation`](../../tree/feature/diagnostics-foundation) — lightweight diagnostic events and snapshots.
- [`feature/configurable-rates`](../../tree/feature/configurable-rates) — experiments including the Forgotten House map asset.
- [`feature/quenching-safety-20261017`](../../tree/feature/quenching-safety-20261017) — crafting/refinement safety work.
- [`feature/unique-refinement-20261017`](../../tree/feature/unique-refinement-20261017) — unique-item refinement work.

There is currently **no claim of a ready-to-install public release**. Please treat the repository as source and experimental development material.

## Credits & original projects

This project is made out of love for Diablo and builds upon a great deal of work by other people. **Their work deserves clear credit**:

1. **Diablo / Diablo I** — Blizzard Entertainment, the original game and world.
2. **The Hell series / The Hell 4** — **Mordor and The Hell team**, for the enormous modding work and systems behind the codebase. [The Hell 4 source and original author notes](https://github.com/roboserg/the-hell-4-src) · [The Hell team](https://www.patreon.com/thmod).
3. **Diablo: The Heaven** — **roboserg**, for the quality-of-life and balance-oriented project on top of The Hell 4 that Sociedade de Tristram uses as its immediate technical base. [The Heaven repository](https://github.com/roboserg/diablo-1-the-heaven).
4. **The Hell 3** — **Mordor / The Hell team**, separately credited for the *translation-only* initiative. [Official mod page](https://www.moddb.com/mods/diablo-the-hell-3).
5. **Sociedade de Tristram** — additional experimental features, new companion mechanics, original quest concepts, localization work, integration, and development by **Vranuska**.

The original source credit files remain at [`res/credits.txt`](Sociedade%20de%20Tristram/TH/res/credits.txt) and [`res/credits1.txt`](Sociedade%20de%20Tristram/TH/res/credits1.txt). Please consult them for individual contributors to The Hell.

This is an **unofficial fan project**, not affiliated with or endorsed by Blizzard Entertainment, The Hell team, or The Heaven's developer. Existing third-party content, code, and acknowledgments remain attributable to their respective creators.

---

<div align="center">

*I'm not trying to replace the Diablo I I fell in love with. I just want to keep finding reasons to return to Tristram.*

**— Vranuska**

</div>
