#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)

def test():
    a = 2445
    b = 5424
    if 3==ac:
        a = int(av[1])
        b = int(av[2])
    
    if my_euler.is_permutation(a,b):
        print("%d is a permutation of %d" % (a,b))
    else:
        print("%d is not a permutation of %d" % (a,b))

def proj():
    sv = sieve(10000)
    print("Starting")
    start = 2
    end = 10**6
    tot = 0
    for n in range(start, end+1):
        sys.stdout.write("n = %d\r" % n)
        totn = sv.totient(n)
        tot = tot + totn
        
    print("")
    print("tot = %d" % (tot))


def proj2():
    L = 10**6
    phi = range(L+1)
    for n in range(2,L+1):
        if phi[n]==n: # This means n is prime
            for k in range(n,L+1,n):
                '''
                Need to think about this line to figure out why
                this ends up with the correct answer.
                '''
                phi[k] -= phi[k]//n
    sm = sum(phi)-1
    print("Answer is %d" % sm)

if __name__=='__main__':
    proj2()
    #test()

















