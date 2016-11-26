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


def is_b9_pan ( n ):
    cnt = my_euler.count_dig(n)
    if cnt<9:
        return False
    mod = 10**9
    b9 = n%mod
    return my_euler.is_pandigital(b9)

def is_t9_pan ( n ):
    cnt = my_euler.count_dig(n)
    if cnt<9:
        return False
    shift = cnt-9
    div = 10**shift
    t9 = n//div
    return my_euler.is_pandigital(t9)

def top9 ( n ):
    # log(phi)
    lp = 0.2089876402499787344524407
    # log(1/sqrt(5))
    li = -0.3494850021680093732356909
    t = n*lp + li
    t = int((pow(10,t-int(t)+8)))
    return t

def proj():
    pnum = 100
    answer = 0

    x1, x2 = 1, 1
    cnt = 2
    keep_going = True
    mod = 10**9
    tot = 0
    while keep_going:
        cnt = cnt+1
        xn = (x1+x2) % mod
        x1, x2 = x2, xn
        if cnt<2749:
            continue
        sys.stdout.write(" cnt = %d\r" % (cnt))
        if my_euler.is_pandigital(xn):
            if my_euler.is_pandigital(top9(cnt)):
                answer = cnt
                break
        if cnt>10**6:
            print("Didn't find anything")
            keep_going = False

    print("")
    print_project_answer(pnum,answer)
    

def test():
    s5 = math.sqrt(5)
    phi = (1+s5)/2.0
    lphi = math.log(phi,10)
    linv = math.log(1/s5,10)
    print("phi        =  %.25f" % phi)
    print("log10(phi) =  %.25f" % lphi)
    print("log10(inv) = %.25f" % linv)

if __name__=='__main__':
    #test()
    proj()

