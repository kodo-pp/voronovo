#!/usr/bin/env python3

def unbase(s, base):
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
    return l

a, b, c = [input() for i in [0]*3]


for start in range(11):
    try:
        unbase(a, start)
        unbase(b, start)
        unbase(c, start)
        break
    except ValueError:
        continue


def sign(z):
    return -1 if z < 0 else 1 if z > 0 else 0


def f(z):
    return unbase(a, z) + unbase(b, z) - unbase(c, z)


def check(z):
    if f(z) == 0:
        raise IndexError(('FOUND!!1!', z))
    return sign(f(z)) == sign(f(start))

try:
    if f(start) == 0:
        print(start)
    else:
        z = binsearch(start, 10**9, check)
        if f(z-1) == 0:
            print(z-1)
        elif f(z) == 0:
            print(z)
        elif f(z+1) == 0:
            print(z+1)
        else:
            print(0)
except IndexError as e:
    print(e.args[0][1])
