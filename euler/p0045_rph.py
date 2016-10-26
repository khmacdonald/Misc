#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)


def is_pent ( k ):
    ptest = (math.sqrt(1.0 + 24.0 * k) + 1.0)/6.0
    return ptest.is_integer(), int(ptest)

def is_hex ( k ):
    ptest = (math.sqrt(1.0 +  8.0 * k) + 1.0)/4.0
    return ptest.is_integer(), int(ptest)

def pnum ( n ):
    return n * (3 * n-1) / 2

def hnum ( n ):
    return n * (2*n-1)

def tnum ( n ):
    return n * (n+1) / 2

def test ( ):
    tn = tnum(285) 
    pn = pnum(165)
    hn = hnum(143)
    print("t(285) = %d, p(165) = %d, h(143) = %d" % (tn,pn,hn))

    pb, ipn = is_pent(pn)
    hb, ihn = is_hex(pn)
    print("iP(%d) = %d, iH(%d) = %d" % (tn,ipn,tn,ihn))

def proj ( ):
    for k in range(284,1000000):
        tn = tnum(k)
        tp, ptp = is_pent(tn)
        th, pth = is_hex(tn)
        if tp and th:
            print(tn)

if __name__=='__main__':
    proj()












