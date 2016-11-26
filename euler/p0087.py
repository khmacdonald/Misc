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

def get_lists(mx):
    sv_max = int(math.sqrt(mx))
    primes = my_euler.fast_sieve(mx)
    squares = []
    cubes = []
    fourth = []
    for p in primes:
        a = p*p
        if a>mx:
            break
        squares.append(a)
        a = a*p
        if a<mx:
            cubes.append(a)
            a = a*p
            if a<mx:
                fourth.append(a)
    return squares, cubes, fourth

def proj():
    pnum = 80
    answer = 0

    mx = 50 * (10**6)
    sq, cu, fu = get_lists(mx)
    print(sq)
    print(cu)
    print(fu)
    sums = set()
    for s in sq:
        for c in cu:
            if mx<s+c:
                break
            for f in fu:
                a = s+c+f
                if a<mx:
                    sums.add(a)

    answer = len(sums)
    print("")
    print_project_answer(pnum,answer)
    

def test():
    mx = 50
    sq, cu, fu = get_lists(mx)
    sums = set()
    for s in sq:
        for c in cu:
            if mx<s+c:
                break
            for f in fu:
                a = s+c+f
                if a<mx:
                    sums.add(a)
    print(sums)
    print(len(sums))
    

if __name__=='__main__':
    #test()
    proj()

