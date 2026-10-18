#!/usr/bin/env python3
"""Read-only safety check for the reserved Sigils/Talisman inventory.

Run at repository root:
    python tools/check_sigil_foundation.py

This is a structural safety check, NOT an in-game or save-compatibility test.
"""
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "Sociedade de Tristram" / "TH" / "src" / "InventoryPanel.cpp"
SAVING = ROOT / "Sociedade de Tristram" / "TH" / "src" / "Saving.cpp"
STRUCTS = ROOT / "Sociedade de Tristram" / "TH" / "include" / "structs.h"

def get_section(source: str, begin: str, end: str) -> str:
    if begin not in source or end not in source[source.index(begin) + len(begin):]:
        raise ValueError(f"Could not locate function boundaries: {begin}")
    begin_pos = source.index(begin)
    end_pos = source.index(end, begin_pos + len(begin))
    return source[begin_pos:end_pos]

def main() -> int:
    try:
        src = SOURCE.read_text(encoding="utf-8-sig")
        saving = SAVING.read_text(encoding="utf-8-sig")
        structs = STRUCTS.read_text(encoding="utf-8-sig")
    except OSError as exc:
        print(f"ERROR: unable to read project files: {exc}")
        return 2

    failed = []
    if "case IS_Talisman: continue;" not in src:
        failed.append("Reserved Talisman page must remain disabled until a safe implementation exists.")
    for name, begin, end, guard, risky in [
        ("TakeInvItemToCursor", "int __fastcall TakeInvItemToCursor(", "void __fastcall PutCursorItemToInv(",
         "if( slot.id == IS_Talisman ) return -1;", "cursorItem.ItemCode = IC_M1_NONE;"),
        ("PutCursorItemToInv", "void __fastcall PutCursorItemToInv(", "int GetSlotMouseAbove_Inv()",
         "if( slot.id == IS_Talisman ) return;", "player.InvUsedAlt[cell.r][cell.c]"),
        ("GetSlotMouseAbove_Inv", "int GetSlotMouseAbove_Inv()", "void __fastcall",
         "if( slot.id == IS_Talisman ) return -1;", "player.BeltInventory[cell.c]"),
    ]:
        try:
            body = get_section(src, begin, end)
            if guard not in body or risky not in body or body.index(guard) > body.index(risky):
                failed.append(f"{name}: Talisman early guard missing or too late.")
        except ValueError as exc:
            failed.append(str(exc))

    if "TalismanSlots[IS_70_40_Inv_Count]" not in structs or "TalUsedAlt[InvRows][InvCols]" not in structs:
        failed.append("Expected reserved item storage is missing; investigate before adding sigils.")
    if "each(p.TalismanSlots).ItemCode = IC_M1_NONE;" not in saving:
        failed.append("Legacy save initialization for reserved storage was modified.")

    if failed:
        print("SIGILS FOUNDATION CHECK FAILED")
        for err in failed:
            print(" -", err)
        return 1

    print("SIGILS FOUNDATION CHECK PASSED")
    print("Reserved page is disabled and unsafe interactions are guarded.")
    print("Does not verify Sigil drops, effects, persistence, multiplayer, or gameplay.")
    return 0

if __name__ == "__main__":
    sys.exit(main())
