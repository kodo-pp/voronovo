#!/usr/bin/env python3
from functools import reduce
factorial = lambda x: reduce(lambda a, b: a * b, range(2, x + 1), 1)
n, k = [int(input()) for i in [0]*2]
print(factorial(n) // factorial(k) // factorial(n-k))
