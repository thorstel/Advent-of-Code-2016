# https://adventofcode.com/2016/day/5

from collections import *
from functools import *
import hashlib
import itertools
import re
import sys

def solve(door_id):
    index = 0
    ans1 = ''
    ans2 = [None for _ in range(8)]
    while not all(ans2):
        h = hashlib.md5((door_id + str(index)).encode('ascii')).hexdigest()
        index += 1
        if h.startswith('00000'):
            ans1 += h[5]
            if h[5].isdigit():
                i = int(h[5])
                if i < len(ans2) and not ans2[i]:
                    ans2[i] = h[6]
    print(ans1[:8])
    print(''.join(ans2))

########################################################################
#                             SETUP STUFF                              #
########################################################################

sample_input = r"""
abc
""".strip()

actual_input = r"""
ugkcyxxp
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
