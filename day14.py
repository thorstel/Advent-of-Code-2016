# https://adventofcode.com/2016/day/14

from collections import *
from functools import *
import hashlib
import itertools
import re
import sys

def compute_keys(salt, is_part2):
    target = -1
    i = 0
    cand = []
    keys = []
    while len(keys) < 64 or i < target:
        h = salt + str(i)
        for _ in range(2017 if is_part2 else 1):
            h = hashlib.md5(h.encode('ascii')).hexdigest()
        to_remove = []
        for c in cand:
            if i <= c[0] + 1000:
                if c[1] in h:
                    keys.append(c[0])
                    to_remove.append(c)
                    if len(keys) == 64:
                        target = i + 1000
            else:
                to_remove.append(c)
        for c in to_remove:
            cand.remove(c)
        for x, y, z in zip(h, h[1:], h[2:]):
            if x == y and y == z:
                cand.append((i, ''.join(x for _ in range(5))))
                break
        i += 1
    keys.sort()
    return keys[63]

def solve(salt):
    print(compute_keys(salt, False))
    print(compute_keys(salt, True))

########################################################################
#                             SETUP STUFF                              #
########################################################################

actual_input = r"""
cuanljph
""".strip()

if len(sys.argv) > 1:
    with open(sys.argv[1], 'r') as f:
        file_input = f.read().strip()
    solve(file_input)
else:
    solve(actual_input)
