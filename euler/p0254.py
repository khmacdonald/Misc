#!/usr/local/bin/python

import bisect
import decimal
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler
import arr_p0254

av = sys.argv
ac = len(av)

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d\n\n" % (project_output,answer))

def proj():
    pnum = 152
    answer = 0

    print("")
    print_project_answer(pnum,answer)
    return

def fn ( n ):
    sm = 0
    while n:
        d = n % 10
        n = n / 10
        sm = sm + arr_p0254.fac_dig[d]
    return sm

def test_sf():
def test_f():
    label = 'f'
    lo, hi = 1, 1023
    s = '%s = [\n    %8d' % (label,0)
    for k in range(lo,hi+1):
        y = fn(k)
        if 0==(k%16):
            s = '%s,\n    %8d' % (s,y)
        else:
            s = '%s,%8d' % (s,y)
    print("%s]" % s)

def test_old():
    s = '[0'
    for k in range(1,10):
        y = my_euler.factorial(k)
        s = '%s,%d' % (s,y)
    print("fac_dig = %s]" % s)
        

if __name__=='__main__':
    test()
    #proj()

