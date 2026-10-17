# Quenching safety pass (2026-10-17)

This work is based on `feature/configurable-rates` and intentionally does not merge
the independent diagnostics branch.

## Behavior
- Griswold's quenching service accepts identified weapons, armor, rings and amulets
  (or ordinary items of these types).
- Ineligible items such as potions and quest objects cannot be deposited.
- The button is inactive for invalid items or an unsupported quenching affix.
- A purchase calculates its discounted gold cost before updating the item.
- The previous item is restored and no gold is charged if item recreation does not
  produce the expected quenching effect.
- Existing tiers, affix types, prices, save data and unrelated game systems are unchanged.
- Firearms are not added.

## Manual Windows Debug|Win32 regression checks (not yet executed)
1. Confirm a healing potion, gold stack and unidentified magic item are rejected by the quenching slot.
2. Confirm identified weapon, armor, ring and amulet are accepted.
3. Try quenching without enough gold: no tier increase and no deduction.
4. Upgrade an eligible weapon once: bonus appears after reopening the item tooltip, and gold decreases exactly by the displayed price.
5. Repeat for armor and jewelry, then save/reload to confirm tier and effect persist.
6. Confirm a full-affix item does not charge if there is no room for the quench effect.
7. Confirm class-specific bonuses (Trapper/Bombardier, spellcasters, summoners) still work.
8. Recheck the companion UI, inventory organization, Cain transmutation and Griswold crafting for regressions.

Build and gameplay verification require a Windows toolchain and an in-game test; this commit has only been checked structurally.
