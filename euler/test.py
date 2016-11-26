#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)

def test01():
    n = 3
    if 2==ac:
        n = int(av[1])
    y = my_euler.fibonacci(n)
    print("fib(%d) = %d" % (n,y))
    cnt = my_euler.count_dig(y)
    print("  has %d digits" % cnt)
    mod = 10**9
    ym = y % mod
    if my_euler.is_pandigital(ym):
        print("Last 9 (%d) is pandigital" % ym)
    else:
        print("Last 9 (%d) is not pandigital" % ym)

def test02():
    n = 3
    if 2==ac:
        n = int(av[1])
    y = my_euler.fibonacci(n)
    cnt = my_euler.count_dig(y)
    if cnt>9:
        shift = cnt-9
    div = 10**shift
    ym = y // div
    if my_euler.is_pandigital(ym):
        print("Last 9 (%d) is pandigital" % ym)
    else:
        print("Last 9 (%d) is not pandigital" % ym)
    

if __name__=='__main__':
    test02()

