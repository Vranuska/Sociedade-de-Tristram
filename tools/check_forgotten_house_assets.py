#!/usr/bin/env python3
"""Static checks for the Forgotten House map and entrance preflight.

Run from repository root: python tools/check_forgotten_house_assets.py
Static only: does not access the installed game archives or run the quest.
"""
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[1]
mod = root / "Sociedade de Tristram" / "TH"
file = mod / "res" / "thdata" / "Levels" / "L1Data" / "ForgottenHouse.DUN"
quests = (mod / "src" / "PlayerTrade.cpp").read_text(encoding="utf-8-sig")
installer = (root / "tools" / "install-forgotten-house.ps1").read_text(encoding="utf-8-sig")

checks = {
    "quest map packaged in source tree": file.is_file() and file.stat().st_size == 19588,
    "map path matches quest loader": 'LoadQuestDungeonMainMapChurch("Levels\\\\L1Data\\\\ForgottenHouse.DUN"' in quests,
    "first-time entrance checks resources": quests.count("if( !ForgottenHouseAssetsAvailable() ) return;") == 2,
    "asset preflight checks map": '"Levels\\\\L1Data\\\\ForgottenHouse.DUN"' in quests,
    "asset preflight checks church palette": '"Levels\\\\L1Data\\\\zContrastique.pal"' in quests,
    "preflight uses archived or direct-file access": "SFileOpenFile(asset.path, &handle)" in quests,
    "preflight handles failed read": "fileSize == 0 || fileSize == 0xFFFFFFFF" in quests,
    "installer verifies copied bytes": "Get-FileHash" in installer and "$sourceHash -ne $installedHash" in installer,
    "installer backs up conflicting map": 'Copy-Item -LiteralPath $destination -Destination $backup' in installer,
    "installer does not overwrite archives": "Copy-Item -LiteralPath $source -Destination $destination" in installer,
}
failed = [name for name, ok in checks.items() if not ok]
for name, ok in checks.items():
    print(("PASS " if ok else "FAIL ") + name)
if failed:
    print(f"FAILED {len(failed)} static checks")
    sys.exit(1)
print("PASS: source-level checks only. Windows rebuild and quest test still required.")
