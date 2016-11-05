#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def gcd ( a, b ):
    while b:
        t = a%b
        a = b
        b = t
    return a
    
if __name__=='__main__':
    if 3!=ac:
        print("Usage: %s <integer> <integer>" % av[0])
        print("    Compute the greatest common divisor for two integers")
    else:
        a = int(av[1])
        b = int(av[2])
        d = gcd(a,b)
        print("gcd(%d,%d) = %d" % (a,b,d))
