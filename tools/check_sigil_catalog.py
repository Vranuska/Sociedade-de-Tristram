#!/usr/bin/env python3
"""Static checks for the Society of Tristram's dormant Sigil catalog.

The checks do not replace a Win32 rebuild, gameplay or save round-trip tests.
"""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1] / "Sociedade de Tristram" / "TH"
SOURCE = ROOT / "src"
INCLUDE = ROOT / "include"

IDS = {
    2504: "Sigilo do Veu",
    2505: "Sigilo de Ferro",
    2506: "Sigilo do Arcano",
    2507: "Sigilo do Pacto",
    2508: "Sigilo das Brasas",
}

def main() -> int:
    catalog = (SOURCE / "BaseItems.cpp").read_text(encoding="utf-8-sig")
    item = (SOURCE / "Item.cpp").read_text(encoding="utf-8-sig")
    crafting = (SOURCE / "Crafting.cpp").read_text(encoding="utf-8-sig")
    transmute = (SOURCE / "Transmute.cpp").read_text(encoding="utf-8-sig")
    tooltip = (SOURCE / "Tooltip.cpp").read_text(encoding="utf-8-sig")
    enums = (INCLUDE / "enums.h").read_text(encoding="utf-8-sig")
    failures = []

    for item_id, name in IDS.items():
        row = next((s for s in catalog.splitlines() if re.match(r"\{\s*" + str(item_id) + r"\s*,", s)), None)
        if not row or f'"{name}"' not in row or "MC_0_NONE" not in row or "MC_GEM" in row:
            failures.append(f"Sigil {item_id}: expected name and a non-gem base entry.")
        if str(item_id) not in enums:
            failures.append(f"Sigil {item_id}: missing stable enum identifier.")

    if "Gems[item.baseItemIndex - BI_1238_GEM_RUBY_1]" in item:
        failures.append("Item grade logic still performs unchecked gem-array indexing.")
    if "FindGemInfoByBaseItemIndex(item.baseItemIndex)" not in item:
        failures.append("Item grade logic lacks safe gem lookups.")
    if "FindGemInfoByBaseItemIndex(itemPtr->baseItemIndex)" not in crafting:
        failures.append("Gem crafting does not reject non-gem bases.")
    if "FindGemInfoByBaseItemIndex(item.baseItemIndex)" not in transmute:
        failures.append("Cain's gem recipe does not verify gem bases.")
    if tooltip.count("SocietySigilAspect(item.baseItemIndex)") != 3:
        failures.append("All three tooltip layouts must show Sigil affinity.")
    if tooltip.count("Adormecido: aguarda vinculacao") != 3:
        failures.append("Dormant status missing from a tooltip layout.")

    if failures:
        print("SIGIL CATALOG: FAILED")
        for message in failures:
            print(" -", message)
        return 1
    print("SIGIL CATALOG: STATIC CHECKS PASSED")
    print("Five Sigils retain their IDs and are not treated as gems.")
    print("Gem safeguards and all three informational tooltips are present.")
    return 0

if __name__ == "__main__":
    sys.exit(main())
