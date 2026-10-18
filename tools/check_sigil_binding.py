#!/usr/bin/env python3
"""Read-only static regression checks for five Sigil binding slots.

Run from any directory with:
    python tools/check_sigil_binding.py

A passed check does not guarantee Win32 compilation or in-game save safety.
"""
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1] / "Sociedade de Tristram" / "TH"
INV = (ROOT / "src" / "InventoryPanel.cpp").read_text(encoding="utf-8-sig")
PLAYER = (ROOT / "src" / "Player.cpp").read_text(encoding="utf-8-sig")
SAVE = (ROOT / "src" / "Saving.cpp").read_text(encoding="utf-8-sig")
STRUCT = (ROOT / "include" / "structs.h").read_text(encoding="utf-8-sig")

checks = {
    "five binding slots": "static constexpr int SocietySigilSlots = 5;" in INV,
    "each Sigil bound by its stable base ID": "item.baseItemIndex - BI_2504_SIGIL_VEIL" in INV,
    "separate clickable tab": "InventorySigilsButton" in INV,
    "single-player binding guard": "MaxCountOfPlayersInGame > 1" in INV,
    "do not overwrite occupied slots": "bound.baseItemIndex != 0" in INV,
    "only unbind with empty cursor": "if( cursor.ItemCode == IC_M1_NONE )" in INV,
    "item transfer to cursor": "cursor = bound;" in INV,
    "item transfer to reserved slot": "bound = cursor;" in INV,
    "inventory bag hit-testing": "SocietySigilCursorOverBackpack()" in INV,
    "separate Sigil page drawing": "SocietySigilsDrawPage(player);" in INV,
    "GetItemSprites accepts mutable sprite index":
        "int sprite = item.GraphicValue + CM_12_ITEMS_PICS_START;" in INV
        and "const int sprite = item.GraphicValue + CM_12_ITEMS_PICS_START;" not in INV,
    "new characters initialize empty slots":
        "for( auto& item : player.TalismanSlots ) item.ItemCode = IC_M1_NONE;" in PLAYER,
    "existing Player struct remains serialized": "WriteSaveData( &Players[playerIndex], sizeof(Player) );" in SAVE,
    "existing Player struct remains loaded": "ReadSaveData( &p, sizeof(Player) );" in SAVE,
    "reserved Talisman storage exists": "TalismanSlots[IS_70_40_Inv_Count]" in STRUCT,
}
failed = [name for name, valid in checks.items() if not valid]
for name, valid in checks.items():
    print(("OK  " if valid else "FAIL") + " " + name)
if failed:
    print(f"FAILED {len(failed)} structural check(s)")
    sys.exit(1)
print("PASS: structural checks only. Compile and test in single player.")
