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

def slow_factor ( n ):
    '''
    Factors n.  Works only for relatively small n, i.e., NOT 10**15.
    Used this to compare to smaller numbers, like 10**5.
    '''
    t = math.sqrt(n)
    f = [1]
    for k in range(2, int(t)+1):
        if 0==(n%k):
            f.append(k)
            f.append(n/k)
    if t == int(t): 
        f.remove(t)
    f.sort()
    fstr = ''
    for x in f:
        fstr = '%s %d' % (fstr,x)
    print("Factors of %d is %s" % (n,fstr))

def fast_factor ( mx2, mx5 ):
    '''
    Know ahead of time that n = (2**mx2) * (5**mx5)
    '''
    two = 1
    five = 1
    n = (2**mx2)*(5**mx5)
    f = [1,n]
    l2 = [2**k for k in range(1,mx2+1)]
    l5 = [5**k for k in range(1,mx2+1)]
    f = f+l2+l5
    for x in range(mx2):
        two = two*2
        five = 1
        for y in range(mx5):
            five = five*5
            f.append(two*five)
    mod = 10**9
    sm = 0
    for x in f:
        y = x*x
        sm = ((sm+y) % mod)
    print("Fast factor = %d" % sm)


def fast_sig2 ( mx2, mx5 ):
    '''
    Computes sig2 of n = (2**mx2) * (5**mx5)
    '''
    mod = 10**9
    sig2 = 1
    c = 1
    for k in range(1,mx2+1):
        c = c*2
        sig2 = ((sig2+c*c) % mod) # Sum all powers of 2 squared
    c = 1
    for k in range(1,mx5+1):
        c = c*5
        sig2 = ((sig2+c*c) % mod) # Sum all powers of 5 squared
    two = 1
    for k in range(mx2):
        two = two*2
        five = 1
        for m in range(mx5):
            five = five*5
            y = two*five # Compute next factor of n
            sig2 = ((sig2+y*y) % mod) # Add the square of that factor and modulo 10**9
    #print("Fast sig2 = %d" % sig2)
    return sig2

def proj():
    pnum = 401
    answer = 0

    # 10**15 has prime factorization (2**15)*(5**15)
    mx2 = 15
    mx5 = 15
    #n = (2**mx2) * (5**mx5)
    #fast_factor(mx2,mx5)
    answer = fast_sig2(mx2,mx5)

    print("")
    print_project_answer(pnum,answer)
    

def test():
    mil = 10**6
    mx = (10**15)
    sqm = int(math.sqrt(mx))
    print(sqm)
    print(my_euler.count_dig(sqm))
    print("Starting")
    sv = my_euler.fast_sieve(sqm)
    print("Factoring")
    f = my_euler.prime_factor(mx,sv)
    print("")
    print("Factors of %d:" % mx)
    print(f)
    print("")

if __name__=='__main__':
    #test()
    proj()

