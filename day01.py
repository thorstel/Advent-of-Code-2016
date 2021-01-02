# https://adventofcode.com/2016/day/1

from collections import *
from functools import *
import itertools
import re
import sys

def solve(data):
    offsets = [(0, -1), (1, 0), (0, 1), (-1, 0)]
    direction = 0
    x, y = 0, 0
    SEEN = set()
    p2_ans = None
    for cmd in data.split(', '):
        if cmd[0] == 'L':
            direction -= 1
        elif cmd[0] == 'R':
            direction += 1
        else:
            assert False
        direction %= 4
        dx, dy = offsets[direction]
        for _ in range(int(cmd[1:])):
            x += dx
            y += dy
            if (x, y) in SEEN and not p2_ans:
                p2_ans = (x, y)
            SEEN.add((x, y))
    print(abs(x) + abs(y))
    print(abs(p2_ans[0]) + abs(p2_ans[1]))

########################################################################
#                             SETUP STUFF                              #
########################################################################

sample_input = r"""
R8, R4, R4, R8
""".strip()

actual_input = r"""
L1, L3, L5, L3, R1, L4, L5, R1, R3, L5, R1, L3, L2, L3, R2, R2, L3, L3, R1, L2, R1, L3, L2, R4, R2, L5, R4, L5, R4, L2, R3, L2, R4, R1, L5, L4, R1, L2, R3, R1, R2, L4, R1, L2, R3, L2, L3, R5, L192, R4, L5, R4, L1, R4, L4, R2, L5, R45, L2, L5, R4, R5, L3, R5, R77, R2, R5, L5, R1, R4, L4, L4, R2, L4, L1, R191, R1, L1, L2, L2, L4, L3, R1, L3, R1, R5, R3, L1, L4, L2, L3, L1, L1, R5, L4, R1, L3, R1, L2, R1, R4, R5, L4, L2, R4, R5, L1, L2, R3, L4, R2, R2, R3, L2, L3, L5, R3, R1, L4, L3, R4, R2, R2, R2, R1, L4, R4, R1, R2, R1, L2, L2, R4, L1, L2, R3, L3, L5, L4, R4, L3, L1, L5, L3, L5, R5, L5, L4, L2, R1, L2, L4, L2, L4, L1, R4, R4, R5, R1, L4, R2, L4, L2, L4, R2, L4, L1, L2, R1, R4, R3, R2, R2, R5, L1, L2
""".strip()

if len(sys.argv) > 1:
    with open(sys.argv[1], 'r') as f:
        file_input = f.read().strip()
    solve(file_input)
else:
    print('=== SAMPLE ===')
    solve(sample_input)
    print('=== ACTUAL ===')
    solve(actual_input)
