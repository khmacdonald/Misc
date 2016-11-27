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

def plist ( n ):
    sv = my_euler.fast_sieve(n)
    isp = [0]*n
    for p in sv:
        isp[p] = 1
    return sv, isp


def proj():
    pnum = 146
    answer = 0

    mx = 150000000
    mx = 1000000
    sv, isp = plist(mx)
    sm = 0
    for p in sv:
        if 1!=isp[p+2]:
            continue
        if 1!=isp[p+6]:
            continue
        if 1!=isp[p+8]:
            continue
        if 1!=isp[p+12]:
            continue
        if 1!=isp[p+26]:
            continue
        m = int(math.sqrt(p-1))
        if m*m+1==p:
            print(m)
            sm = sm+m


    answer = sm
    print("")
    print_project_answer(pnum,answer)
    

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

