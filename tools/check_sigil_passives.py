#!/usr/bin/env python3
"""Read-only structure checks for Sociedade de Tristram Sigil passives.

These checks do NOT substitute for Win32 compilation, save/load or combat tests.
"""
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[1] / "Sociedade de Tristram" / "TH"
item = (root / "src" / "Item.cpp").read_text(encoding="utf-8-sig")
inv = (root / "src" / "InventoryPanel.cpp").read_text(encoding="utf-8-sig")
tip = (root / "src" / "Tooltip.cpp").read_text(encoding="utf-8-sig")
saving = (root / "src" / "Saving.cpp").read_text(encoding="utf-8-sig")
catalog = (root / "src" / "BaseItems.cpp").read_text(encoding="utf-8-sig")

checks = {
    "solo only": "if( MaxCountOfPlayersInGame == 1 )" in item,
    "fixed Sigil identity": "sigil.baseItemIndex != sigilIds[slot]" in item,
    "five stable Sigil IDs": all(x in item for x in (
        "BI_2504_SIGIL_VEIL", "BI_2505_SIGIL_STEEL", "BI_2506_SIGIL_ARCANE",
        "BI_2507_SIGIL_PACT", "BI_2508_SIGIL_EMBERS")),
    "vein/veil defense and elemental resistance":
        "ACFromItems += 2;" in item and "player.resist[e] += 3;" in item,
    "steel hit and damage": "damagePercent += 3;" in item and "accuracy += 5;" in item,
    "arcane spell scaling": "player.spellPercent[spell] += 4;" in item,
    "pact summons": "summonDamagePercent += 5;" in item,
    "embers fire damage": "player.spellPercent[spell] += 6;" in item
        and "Spells[spell].Element == ET_1_FIRE" in item,
    "recalculation clears derived spell and resistance bonuses":
        "memzero( player.spellPercent );" in item
        and "memzero( player.resist );" in item,
    "bind/unbind recalculation": inv.count("RecalcPlayer(CurrentPlayerIndex, 1);") >= 2,
    "nonempty slots preserved": "if( !SocietySigilSlotEmpty(bound) )" in inv,
    "legacy empty sentinel": "item.FullMagicalItemName[0] == '\\0'" in inv,
    "tooltip shows current powers": tip.count("SocietySigilBonus(item.baseItemIndex)") == 3,
    "old dormant status removed": "Adormecido: aguarda vinculacao" not in tip,
    "binding tab shows bonuses": "Bonus apenas em jogo solo" in inv,
    "existing Player save unchanged": "WriteSaveData( &Players[playerIndex], sizeof(Player) );" in saving,
    "prototype drops remain disabled":
        all(any(line.startswith("{\t" + str(idx) + ",") and ",\t0,\t0,\tITEM_3" in line
                for line in catalog.splitlines()) for idx in range(2504, 2509)),
}
failed = []
for name, ok in checks.items():
    print(("PASS " if ok else "FAIL ") + name)
    if not ok:
        failed.append(name)
if failed:
    print(f"FAILED {len(failed)} checks")
    sys.exit(1)
print("PASS: static Sigil passive checks only; gameplay/compilation still required.")
