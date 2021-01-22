# https://adventofcode.com/2016/day/17

from collections import *
from functools import *
import hashlib
import itertools
import re
import sys

def door_open(c):
    return c in ['b', 'c', 'd', 'e', 'f']

def solve(passcode):
    Q = deque()
    Q.append((0, 0, ''))
    SEEN = set()
    SEEN.add((0, 0, ''))
    valid_paths = []
    while len(Q) > 0:
        x, y, path = Q.popleft()
        if x == 3 and y == 3:
            valid_paths.append(path)
            continue
        hash = hashlib.md5((passcode + path).encode('ascii')).hexdigest()
        if y > 0 and door_open(hash[0]):
            pos = (x, y - 1, path + 'U')
            if not pos in SEEN:
                SEEN.add(pos)
                Q.append(pos)
        if y < 3 and door_open(hash[1]):
            pos = (x, y + 1, path + 'D')
            if not pos in SEEN:
                SEEN.add(pos)
                Q.append(pos)
        if x > 0 and door_open(hash[2]):
            pos = (x - 1, y, path + 'L')
            if not pos in SEEN:
                SEEN.add(pos)
                Q.append(pos)
        if x < 3 and door_open(hash[3]):
            pos = (x + 1, y, path + 'R')
            if not pos in SEEN:
                SEEN.add(pos)
                Q.append(pos)
    print(valid_paths[0])
    print(max(map(len, valid_paths)))

########################################################################
#                             SETUP STUFF                              #
########################################################################

sample_input = r"""
kglvqrro
""".strip()

actual_input = r"""
pxxbnzuo
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
