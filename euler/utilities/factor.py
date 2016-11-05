#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_sieve = []

def sieve ( n ):
    isp = [1] * n
    plist = []
    sq = math.floor(math.sqrt(n))
    isp_len = len(isp)
    for k in range(2,isp_len):
        if 1==isp[k]:
            plist.append(k)
            m = k+k
            while m < isp_len:
                isp[m] = 0
                m = m+k
    return isp, plist

def factor ( n ):
    mx = 1000000
    if n > mx*mx:
        print("%d is too large to factor"  % n)
        return None
    isp, plist = sieve(mx)    
    if n<len(isp):
        if isp[n]:
            return [(n,1)]
    sq = math.floor(math.sqrt(n))
    f = []
    for p in plist:
        if p>sq:
            if n>1:
                f.append((n,1))
            break;
        if 0==(n%p):
            e = 1
            n = n/p
            while 0==n%p:
                e = e+1
                n = n/p
            f.append((p,e))
    return f

def print_factor ( n, f ):
    e = f[0]
    fac = '%d**%d' % (e[0],e[1])
    for e in f[1:]:
        fac = '%s * %d**%d' % (fac,e[0],e[1])
    print("%d factors as (%s)" % (n,fac))


    

if __name__=='__main__':
    if 2!=ac:
        print("Usage: %s <integer>" % av[0])
        print("    Factors an integer")
    else:
        n = int(av[1])
        f = factor(n)
        print(f)
        if f:
            print_factor(n,f)





















