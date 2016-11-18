#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve


av = sys.argv
ac = len(av)

def proj():
    idx = 2
    x = 1
    mx = 100000
    s = sieve(mx)
    tot, pcnt = 1, 0
    stop = False
    while not stop:
        for k in range(4):
            x = x+idx
            tot = tot + 1
            if s.is_prime(x):
                pcnt = pcnt+1
            p = float(pcnt)/float(tot)
            if p<0.1:
                print("pcnt = %d, tot = %d, idx = %d" % (pcnt,tot,idx))
                stop = True
                break
        idx = idx + 2

if __name__=='__main__':
    proj()

