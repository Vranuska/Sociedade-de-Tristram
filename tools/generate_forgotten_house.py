"""Reproduce the first Forgotten House DUN using existing church tiles."""
from pathlib import Path
import struct

width = height = 24
coarse = [22] * (width * height)

def tile(row, col, value):
    coarse[col * width + row] = value

for col in range(8, 20):
    for row in range(8, 20):
        tile(row, col, 13)
for x in range(8, 20):
    tile(x, 7, 2)
    tile(x, 20, 2)
    tile(7, x, 1)
    tile(20, x, 1)
for row, col, value in [(7, 7, 3), (20, 7, 6), (7, 20, 7), (20, 20, 4)]:
    tile(row, col, value)
for col in (9, 10, 16, 17):
    tile(14, col, 15)
words = [width, height] + coarse + [0] * (width * height * 16)
path = Path(__file__).resolve().parents[1] / 'Sociedade de Tristram/TH/res/thdata/Levels/L1Data/ForgottenHouse.DUN'
path.parent.mkdir(parents=True, exist_ok=True)
path.write_bytes(struct.pack(f'<{len(words)}H', *words))
print(f'{path.name}: {len(words) * 2} bytes')
