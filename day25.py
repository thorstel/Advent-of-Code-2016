# https://adventofcode.com/2016/day/25

from collections import *
from functools import *
import itertools
import re
import sys

def run(prog, init):
    pc = 0
    regs = {'a': init, 'b': 0, 'c': 0, 'd': 0}
    cnt = 0
    def get_val(i):
        if prog[pc][i] in regs:
            return regs[prog[pc][i]]
        else:
            return int(prog[pc][i])
    while pc < len(prog):
        if prog[pc][0] == 'cpy':
            x = get_val(1)
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
        elif prog[pc][0] == 'out':
            print(get_val(1))
            cnt += 1
            pc += 1
            if (cnt > 20):
                return
        else:
            assert False

actual_input = r"""
cpy a d
cpy 9 c
cpy 282 b
inc d
dec b
jnz b -2
dec c
jnz c -5
cpy d a
jnz 0 0
cpy a b
cpy 0 a
cpy 2 c
jnz b 2
jnz 1 6
dec b
dec c
jnz c -4
inc a
jnz 1 -7
cpy 2 b
jnz c 2
jnz 1 4
dec b
dec c
jnz 1 -4
jnz 0 0
out b
jnz a -19
jnz 1 -21
""".strip()
program = [line.split() for line in actual_input.splitlines()]

# The program prints the binary representation of the initial value of
# register a + a predefined offset over and over again. In this case,
# the offset is 2538 (= 9 * 282). The smallest repeating pattern is
# 0xAAA. Hence, the initial value for register a must be 0xAAA - 2538.
run(program, 0xAAA - 2538)
