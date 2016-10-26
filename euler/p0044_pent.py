#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def pent_list ( n ):
    return [(k*(3*k-1)/2) for k in range(n+1)]

def pn ( n ):
    return n*(3*n-1)/2

def is_pent ( k ):
    ptest = (math.sqrt(1 + 24.0*k) + 1.0)/6.0
    return ptest.is_integer()

def main ( ):
    mx = 10000
    first = True
    mdiff = 0
    mi, mj = (0,0)
    for i in range(1,mx):
        pi = pn(i)
        for j in range(i+1,mx+1):
            sys.stdout.write("(%d,%d)\r" % (i,j))
            pj = pn(j)
            d = pj - pi
            s = pj + pi
            if is_pent(d) and is_pent(s):
                print("(i,j) = (%d,%d), Diff = %d, Sum = %d" % (i,j,d,s))
                if first:
                    mdiff = d
                    mi = i
                    mj = j
                elif d<mdiff:
                    mdiff = d
                    mi = i
                    mj = j
    print("Min diff = %d" % mdiff)
    print("(i,j) = (%d, %d)" % (mi,mj))


if __name__=='__main__':
    main()
