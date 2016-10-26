#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def ten_dig_pow ( n ):
    prod = 1
    mod = 10000000000
    for k in range(n):
        prod = prod * n
        prod = prod % mod
    return prod

def psum ( ):
    sm = 0
    mod = 10000000000
    for k in range(1,1001):
        s = ten_dig_pow(k)
        sm = sm + s
    sm = sm  % mod
    print("Ten dig = %d" % sm)

def main ( ):
    psum()

if __name__=='__main__':
    main()







