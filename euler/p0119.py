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
    print("%s = %d" % (project_output,answer))

def get_dig ( n ):
    dig = []
    while n:
        d = n % 10
        n = n / 10
        dig.append(d)
    return dig

def make_list ( n, mx ):
    mlist = []
    for k in range(2,mx):
        dlist = []
        m = k
        while m<mx:
            dlist.append(m)
            m = m*k
        mlist.append(mlist)
    return mlist

def proj():
    pnum = 96
    answer = 0

    print("")
    print_project_answer(pnum,answer)
    return

def test():
    x = 614656
    d = get_dig(x)
    sm = sum(d)

if __name__=='__main__':
    test()
    #proj()

