#!/usr/bin/env python3
"""Static regression checks for the developer-only Sigil test generator.

Run: python tools/check_sigil_test_spawn.py
Does not compile the game or verify runtime behavior.
"""
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[1] / "Sociedade de Tristram" / "TH"
main = (root / "src" / "Main.cpp").read_text(encoding="utf-8-sig")
catalog = (root / "src" / "BaseItems.cpp").read_text(encoding="utf-8-sig")

section_start = main.find("case VK_83_S_KEY: { // Alt+S: spells; Alt+Shift+S:")
section_end = main.find("case VK_90_Z_KEY:", section_start)
section = main[section_start:section_end] if section_start >= 0 and section_end > section_start else ""

checks = {
    "one test hotkey case": main.count("case VK_83_S_KEY: { // Alt+S: spells; Alt+Shift+S:") == 1,
    "Debug-only item creation": "#ifdef _DEBUG" in section,
    "Shift modifier required": "if( IsShiftPressed )" in section,
    "solo session required": "MaxCountOfPlayersInGame != 1" in section,
    "legacy cheat mode remains protected": "#if CHEATS" in section and "SwitchFreeSpell();" in section,
    "no key autorepeat": "(lParam & (1L << 30))" in section,
    "five item variants": "nextTestSigil = (nextTestSigil + 1) % 5;" in section,
    "first Sigil base": "BI_2504_SIGIL_VEIL + nextTestSigil" in section,
    "creates ground drops": "createdIndex = SpawnSomething(baseId," in section,
    "checks creation failures": "createdIndex < 0" in section,
    "no multiplayer messaging": "NetSendCmdDItem" not in section,
    "no player inventory mutation": "InventorySlots" not in section and "TalismanSlots" not in section,
    "prototype drop rates unchanged": all(
        any(line.startswith("{\t" + str(i) + ",") and ",\t0,\t0,\tITEM_3" in line
            for line in catalog.splitlines())
        for i in range(2504, 2509)
    ),
}

failed = [name for name, good in checks.items() if not good]
for name, good in checks.items():
    print(("PASS " if good else "FAIL ") + name)
if failed:
    print(f"FAILED {len(failed)} static checks")
    sys.exit(1)
print("PASS: static test generator checks; Windows compilation and gameplay pending.")
