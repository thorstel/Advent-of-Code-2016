# https://adventofcode.com/2016/day/23

from collections import *
from functools import *
import itertools
import re
import sys

def run(prog, regs, optimize):
    toggle = { 'inc': 'dec', 'dec': 'inc', 'tgl': 'inc', 'cpy': 'jnz', 'jnz': 'cpy' }
    pc = 0
    def get_val(i):
        if prog[pc][i] in regs:
            return regs[prog[pc][i]]
        else:
            return int(prog[pc][i])
    while pc < len(prog):
        if optimize and pc == 3:
            regs['a'] = regs['d'] * regs['b']
            regs['c'] = 0
            regs['d'] = 0
            pc = 10
        elif prog[pc][0] == 'cpy':
            x = get_val(1)
            if prog[pc][2] in regs:
                regs[prog[pc][2]] = x
            pc += 1
        elif prog[pc][0] == 'inc':
            regs[prog[pc][1]] += 1
            pc += 1
        elif prog[pc][0] == 'dec':
            regs[prog[pc][1]] -= 1
            pc += 1
        elif prog[pc][0] == 'jnz':
            x = get_val(1)
            if x != 0:
                y = get_val(2)
                pc += y
            else:
                pc += 1
        elif prog[pc][0] == 'tgl':
            x = pc + get_val(1)
            if 0 <= x < len(prog):
                prog[x][0] = toggle[prog[x][0]]
            pc += 1
        else:
            assert False
    return regs['a']

program = r"""
cpy a b
dec b
cpy a d
cpy 0 a
cpy b c
inc a
dec c
jnz c -2
dec d
jnz d -5
dec b
cpy b c
cpy c d
dec d
inc c
jnz d -2
tgl c
cpy -16 c
jnz 1 c
cpy 98 c
jnz 91 d
inc a
inc d
jnz d -2
inc c
jnz c -5
""".strip()

print(run([instr.split() for instr in program.splitlines()], {'a': 7, 'b': 0, 'c': 0, 'd': 0}, False))
print(run([instr.split() for instr in program.splitlines()], {'a': 12, 'b': 0, 'c': 0, 'd': 0}, True))
