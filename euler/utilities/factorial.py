#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def factorial ( n ):
    if n<0:
        return 0
    elif 1==n or 0==n:
        return 1
    else:
        return n * factorial(n-1)

if __name__=='__main__':
    if 2!=ac:
        print("Usage: %s <integer>" % av[0])
        print("    Computes the factorial of an integer")
    else:
        n = int(av[1])
        f = factorial(n)
        print("%d! = %d" % (n,f))




