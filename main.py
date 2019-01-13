#!/usr/bin/env pypy

input = raw_input

def base_to_int(s, base):
    for i in s:
        if int(i) >= base:
            raise ValueError('CTF{Y0U_F0UND_4_FL4G}')
    return sum([base ** i * v for i, v in enumerate(reversed(list(map(int, s))))])

def binsearch(l, r, f):
    while r - l > 1:
        m = (r + l) // 2
        if f(m):
            l = m
        else:
            r = m

a, b, c = [input() for i in [0]*3]


for start in range(11):
    try:
        base_to_int(a, start)
        base_to_int(b, start)
        base_to_int(c, start)
        break
    except ValueError:
        continue

def check(z):
    return base_to_int(a, z) + base_to_int(b, z) == base_to_int(c, z)

try:
    for i in range(start, 100000):
        if check(i):
            print(i)
            raise Exception(':)')
    print(0)
except Exception:
    pass
