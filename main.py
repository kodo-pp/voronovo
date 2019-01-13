#!/usr/bin/env python3

a, b, c = [input() for i in [0]*3]

def check(z):
    return int(a, z) + int(b, z) == int(c, z)

start = 2

for i in a + b + c:
    start = max(start, int(i) + 1)

for i in range(start, 37):
    if check(i):
        print(i)
        exit()
print(0)
