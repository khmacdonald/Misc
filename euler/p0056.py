#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def dig_sum ( x ):
    sm = 0
    while x:
        d = x % 10
        sm = sm + d
        x = x / 10
    return sm

def proj ( ):
    mx = 0
    m = 0
    for a in range(1,100):
        for b in range(1,100):
            x = a**b
            sm = dig_sum(x)
            if sm>mx:
                mx = sm
                m = x
                am = a
                bm = b
    print("Max sum is %d" % mx)
    print("Max sum from a = %d, b = %d" % (am,bm))
    print("Max sum from %d" % m)

def main ( ):
    proj()

if __name__=='__main__':
    main()


















