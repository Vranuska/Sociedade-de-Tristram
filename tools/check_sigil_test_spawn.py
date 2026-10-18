#!/usr/bin/env python3
"""Static checks for the Debug-only Sigil test generator hotkey.

Run from the repository root:
    python tools/check_sigil_test_spawn.py

This does not replace a Win32 build or in-game checks.
"""
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[1] / "Sociedade de Tristram" / "TH"
main = (root / "src" / "Main.cpp").read_text(encoding="utf-8-sig")
catalog = (root / "src" / "BaseItems.cpp").read_text(encoding="utf-8-sig")

start = main.find("static bool TryCreateTestSigil(")
end = main.find("int __stdcall GameWindowProc(", start)
section = main[start:end] if start >= 0 and end > start else ""

checks = {
    "one Sigil debug helper": main.count("static bool TryCreateTestSigil(") == 1,
    "Debug-only implementation": "#ifdef _DEBUG" in main[max(0, start - 450):start],
    "actual Shift key state": "GetKeyState(VK_SHIFT) & 0x8000" in section,
    "actual Alt key state": "GetKeyState(VK_MENU) & 0x8000" in section,
    "handles ordinary and system key events": "(msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)" in main
        and "&& TryCreateTestSigil(wParam, lParam)" in main,
    "blocks key repeats": "(1L << 30)" in section,
    "blocks multiplayer": "MaxCountOfPlayersInGame != 1" in section,
    "does not depend on devmode": "DevelopMode" not in section.split("static bool TryCreateTestSigil(", 1)[-1],
    "cycles exactly five Sigils": "nextTestSigil = (nextTestSigil + 1) % 5;" in section,
    "uses correct first base ID": "BI_2504_SIGIL_VEIL + nextTestSigil" in section,
    "creates items on the ground": "SpawnSomething(baseId," in section,
    "reports test activation": 'TESTE SIGILOS: artefato criado perto do personagem.' in section,
    "reports blocked creation": "TESTE SIGILOS: sem espaco livre" in section,
    "no direct save or inventory modification":
        "TalismanSlots" not in section and "InventorySlots" not in section,
    "legacy Alt+S preserved behind CHEATS":
        "#if CHEATS\n                    case VK_83_S_KEY:" in main
        and "SwitchFreeSpell();" in main,
    "normal prototype drop rates unchanged": all(
        any(line.startswith("{\t" + str(i) + ",") and ",\t0,\t0,\tITEM_3" in line
            for line in catalog.splitlines())
        for i in range(2504, 2509)
    ),
}
failed = [name for name, ok in checks.items() if not ok]
for name, ok in checks.items():
    print(("PASS " if ok else "FAIL ") + name)
if failed:
    print(f"FAILED {len(failed)} static check(s)")
    sys.exit(1)
print("PASS: static test-spawn checks only; compilation/gameplay still required.")
