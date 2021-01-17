# https://adventofcode.com/2016/day/12

from collections import *
from functools import *
import itertools
import re
import sys

def solve(data):
    prog = [line.split() for line in data.splitlines()]
    def run(prog, regs):
        pc = 0
        while pc < len(prog):
            if prog[pc][0] == 'cpy':
                x = regs[prog[pc][1]] if prog[pc][1] in regs else int(prog[pc][1])
                regs[prog[pc][2]] = x
                pc += 1
            elif prog[pc][0] == 'inc':
                regs[prog[pc][1]] += 1
                pc += 1
            elif prog[pc][0] == 'dec':
                regs[prog[pc][1]] -= 1
                pc += 1
            elif prog[pc][0] == 'jnz':
                x = regs[prog[pc][1]] if prog[pc][1] in regs else int(prog[pc][1])
                if x != 0:
                    pc += int(prog[pc][2])
                else:
                    pc += 1
            else:
                assert False
        return regs['a']
    print(run(prog, {'a': 0, 'b': 0, 'c': 0, 'd': 0}))
    print(run(prog, {'a': 0, 'b': 0, 'c': 1, 'd': 0}))

########################################################################
#                             SETUP STUFF                              #
########################################################################

sample_input = r"""
cpy 41 a
inc a
inc a
dec a
jnz a 2
dec a
""".strip()

actual_input = r"""
cpy 1 a
cpy 1 b
cpy 26 d
jnz c 2
jnz 1 5
cpy 7 c
inc d
dec c
jnz c -2
cpy a c
inc a
dec b
jnz b -2
cpy c b
dec d
jnz d -6
cpy 18 c
cpy 11 d
inc a
dec d
jnz d -2
dec c
jnz c -5
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
