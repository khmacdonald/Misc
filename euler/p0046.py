#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_max = 0
g_len = 0
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
    global g_isp
    global g_plist
    global g_len
    global g_max
    g_isp = isp
    g_plist = plist
    g_len = len(g_isp)
    g_max = g_len*g_len
    return True

def is_prime ( n ):
    global g_isp
    global g_plist
    global g_len
    global g_max
    if not g_isp or not g_plist:
        print("is_prime needs sieve")
        sys.exit(-1)
    if n>g_max:
        print("%d is too larg.  Must be smaller than %d." % (n,g_max))
        return False
    if n<g_len:
        if 1==g_isp[n]:
            return True
    for p in g_plist:
        if 0==(n%p):
            return False
    return True

def goldbach ( n ):
    global g_plist
    nsq = int(math.sqrt(n))
    for p in g_plist:
        if p>=n:
            return False
        b = (n-p)/2
        sq = math.sqrt(b)
        if sq.is_integer():
            return True

    return False

def proj():
    pass

def test():
    mx = 10000
    sieve(mx)
    n = 1
    not_found = True
    pp = 0
    while n<mx and not_found:
        sys.stdout.write("Testing %d\r" % n)
        if not is_prime(n):
            if not goldbach(n):
                not_found = False
                pp = n
        n = n+2
    print("")
    if not_found:
        print("Nothing found")
    else:
        print("Found %d" % pp)

if __name__=='__main__':
    #proj()
    test()
