#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve

av = sys.argv
ac = len(av)

def test ( ):
    n = 10
    if 2==ac:
        n = int(av[1])
    sv = sieve(100)
    t = sv.totient(n)
    print("phi(%d) = %d" % (n,t))


def proj():
    sv = sieve(10000)
    nmx = 1000000
    mx = 0

    print("Starting")
    for n in range(2,nmx+1):
        sys.stdout.write("n = %d\r" % n)
        ratio = float(n)/float(sv.totient(n))
        if ratio>mx:
            mx = ratio
            mxn = n
    
    print("")
    print("%d results in ratio %f" % (mxn,mx))

if __name__=='__main__':
    proj()
    #test()

