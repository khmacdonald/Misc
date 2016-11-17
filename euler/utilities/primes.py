#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

class sieve ( object ):

    def __init__ ( self, n = 10000 ):
        self.mx = n * n
        self.sieve(n)

    def sieve ( self, n ):
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
        self.isp = isp
        self.plist = plist

    def is_prime ( self, n ):
        if n>(self.mx):
            print ( "%d is too large to compute. Max size is %d" % (n,mx))
            return False

        isp = self.isp
        plist = self.plist

        if n<len(isp):
            if isp[n]:
                return True
            else:
                return False
        else:
            plen = len(plist)
            pm = plist[plen-1]
            if n > (pm*pm):
                print ( "%d is too large to compute" % n)
                return False
            sq = math.ceil(math.sqrt(n))
            for p in plist:
                if p>sq:
                    return True
                if 0==(n%p):
                    return False

def test ():
    if 2!=ac:
        print("Usage: %s <integer>" % av[0])
        print("    Determines if a number is a prime")
    else:
        n = int(av[1])
        sv = sieve(n)
        print(sv.plist[:15])
        print(sv.isp[:15])


if __name__=='__main__':
    test()
