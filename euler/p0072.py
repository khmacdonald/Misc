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
    nmn = 2
    nmx = 10**7
    mn = nmx

    found = False
    print("Starting")
    for n in range(nmn,nmx+1):
        sys.stdout.write("n = %d\r" % n)
        totn = sv.totient(n)
        if not my_euler.is_permutation(n,totn):
            continue
        ratio = float(n)/float(sv.totient(n))
        if ratio<mn:
            found = True
            mn = ratio
            minn = n
        
    print("")
    if found:
        print("%d results in ratio %f" % (minn,mn))
    else:
        print("Nothing found")

def proj2 ():
    '''
    Way faster
    '''
    num = 10**7
    numsq = int(1.2*math.ceil(math.sqrt(num)))
    print("numsq = %d" % numsq)
    primes = my_euler.fast_sieve(numsq)
    k = 0
    minn = num
    mn = num
    found = False
    answer = 8319823
    print("Max Prime = %d" % (primes[len(primes)-1]))
    for p1 in primes:
        k = k+1
        for p2 in primes[k:]:
            n = p1*p2
            if n==answer:
                print("")
                print("Here n = %d" % n)
            if n>num:
                break
            sys.stdout.write("n = %d\r" % n)
            phi = (p1-1)*(p2-1)
            ratio = n/float(phi)
            if n==answer:
                print("")
                print("phi(%d) = %d, %f" % (n,phi,ratio))
            if my_euler.is_permutation(n,phi):
                if ratio<mn:
                    found = True
                    mn = ratio
                    minn = n
        
    print("")
    if found:
        print("%d results in ratio %f" % (minn,mn))
    else:
        print("Nothing found")

    print("  Answer should be %d" % answer)



if __name__=='__main__':
    proj2()
    #test()

















