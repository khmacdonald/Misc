#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)


def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def test():
    y = 44
    if 2==ac:
        y = int(av[1])

def proj():
    ans = 0
    mod = 10**10
    exp = 7830457
    base = 2
    b = base
    print("Starting")
    p = 1
    while exp:
        if exp&1:
            p = p*b
            if p>mod:
                p = p%mod
        b = b*b
        if b>mod:
            b = b%mod
        exp = (exp>>1)

    ans = (28433*p + 1) % mod
    print_project_answer(92,ans)


if __name__=='__main__':
    proj()
    #test()

















