#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_isp = None
g_plist = None

def sieve ( n ):
    sq = math.floor(math.sqrt(n))
    isp = [1] * (n+1)
    isp[0] = 0
    isp[1] = 0
    isp_len = len(isp)
    plist = []
    for k in range(2,isp_len):
        if 1==isp[k]:
            plist.append(k)
            m = k+k
            while m < isp_len:
                isp[m] = 0
                m = m+k
    return isp, plist

def is_prime ( n ):
    mx = 10000000
    if n>(mx*mx):
        print ( "%d is too large to compute" % n)
        return False

    isp, plist = sieve(1000000)
    if n<len(isp):
        if isp[n]:
            print("%d is prime" % n)
        else:
            print("%d is not prime" % n)
    else:
        plen = len(plist)
        pm = plist[plen-1]
        if n > (pm*pm):
            print ( "%d is too large to compute" % n)
            return False
        sq = math.ceil(math.sqrt(n))
        for p in plist:
            if p>sq:
                print("%d is prime" % n)
                return True
            if 0==(n%p):
                print("%d is not prime" % n)
                return False
    return None


if __name__=='__main__':
    if 2!=ac:
        print("Usage: %s <integer>" % av[0])
        print("    Determines if a number is a prime")
    else:
        n = int(av[1])
        is_prime(n)
