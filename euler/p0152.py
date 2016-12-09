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

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d\n\n" % (project_output,answer))

def proj():
    pnum = 96
    answer = 0
    mx = 1000
    sqmx = int(math.sqrt(mx))

    sm = 0
    cnt = 0
    for k in range(1,sqmx):
        n = k
        m = k*k
        tmp = 0
        while m<mx:
            if my_euler.is_palindrome(m):
                tmp = m
            n = n+1
            m = m + (n*n)
        if tmp!=0:
            cnt = cnt+1
            sm = sm+tmp
            print("    [%3d] k = %3d, n = %3d, tmp=%6d, sm = %8d" % (cnt,k,n,tmp,sm))

    answer = sm
    print("")
    print_project_answer(pnum,answer)
    return

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

