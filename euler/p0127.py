#!/usr/local/bin/python

import bisect
import decimal
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)


decimal.getcontext().prec = 105

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def abc_hit ( a, b, sv ):
    return 0

def proj():
    pnum = 105
    answer = 0

    mx = 1001
    sieve = my_euler.fast_sieve(mx)
    cnt = 0
    for a in range(1,mx-1):
        for b in range(a+1,mx):
            c = a+b
            if 1!=my_euler.gcd(a,b) or \
               1!=my_euler.gcd(a,c) or \
               1!=my_euler.gcd(b,c):
                continue
            cnt += abc_hit(a,b,sieve)

    answer = cnt
    print("")
    print_project_answer(pnum,answer)
    

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

