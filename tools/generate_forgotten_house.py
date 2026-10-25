"""Reproduce the expanded Forgotten House with native church tiles.

The original entrance and four quest objects remain on their original floor cells.
Coarse cells expand to a 2x2 fine grid with a (16, 16) engine offset.
"""
from pathlib import Path
import struct

width = height = 38  # Engine church grid is limited to 40x40.
floor = set()


def room(left, top, right, bottom):
    floor.update((row, col) for row in range(left, right + 1)
                 for col in range(top, bottom + 1))


room(8, 8, 19, 19)     # Original house: preserve clue/save coordinates.
room(2, 8, 5, 19)      # Registry: the three recorded deaths.
room(8, 2, 19, 5)      # Vestibule: the unfinished invitation.
room(24, 8, 35, 19)    # Guest chamber: final arena.
room(8, 24, 19, 35)    # Ash nursery: Maera's shelter.
room(6, 12, 7, 14)
room(12, 6, 14, 7)
room(20, 12, 23, 14)
room(12, 20, 14, 23)

coarse = [22] * (width * height)
for row in range(width):
    for col in range(height):
        if (row, col) in floor:
            value = 13
        else:
            left = (row + 1, col) in floor
            right = (row - 1, col) in floor
            top = (row, col + 1) in floor
            bottom = (row, col - 1) in floor
            value = 1 if left or right else 2 if top or bottom else 22
            if value == 22:
                for dr, dc, corner in ((1, 1, 3), (-1, 1, 6), (1, -1, 7), (-1, -1, 4)):
                    if (row + dr, col + dc) in floor:
                        value = corner
                        break
        coarse[col * width + row] = value

# Connectivity and all fixed fine-grid placements must be valid before writing.
reached = {next(iter(floor))}
queue = list(reached)
for row, col in queue:
    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        cell = row + dr, col + dc
        if cell in floor and cell not in reached:
            reached.add(cell)
            queue.append(cell)
assert reached == floor
placements = [(40, 34), (40, 33), (36, 38), (50, 38), (42, 50), (44, 44),
              (24, 38), (42, 80), (80, 50), (68, 38), (82, 38), (74, 50), (24, 44), (44, 76), (78, 44),
              (24, 36), (26, 48), (36, 24), (48, 24), (36, 70), (50, 82),
              (68, 36), (84, 36), (68, 50), (84, 50),
              (37, 39), (51, 39), (43, 51)]
assert len(set(placements)) == len(placements)
for row, col in placements:
    assert ((row - 16) // 2, (col - 16) // 2) in floor, (row, col)
words = [width, height] + coarse + [0] * (width * height * 16)
path = Path(__file__).resolve().parents[1] / 'Sociedade de Tristram/TH/res/thdata/Levels/L1Data/ForgottenHouse.DUN'
path.parent.mkdir(parents=True, exist_ok=True)
path.write_bytes(struct.pack(f'<{len(words)}H', *words))
print(f'{path.name}: {len(words) * 2} bytes; {len(floor)} connected floor cells')
