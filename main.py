#!/usr/bin/env python3
from functools import reduce
factorial = lambda x: reduce(lambda a, b: a * b, range(2, x + 1), 1)
print(factorial(int(input())))
