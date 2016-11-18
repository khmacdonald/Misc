#!/usr/local/bin/python

import bisect
import math
import sys

#from "/Users/khmacdonald/code/SVN/trunk/euler/utilities/" import primes
sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve

av = sys.argv
ac = len(av)

def proj():
    pass

def proj2():
    '''
    '''
    d = 1
    for i in range(1,10):
        for j in range(1,i):
            a = 9*j*i
            b = 10*j-i
            q,r = divmod(a,b)
            if not r and q<=9:
                d *= i/float(j)
                print("    This one:")
            print("%4d = %2d * %2d + %2d" % (a,b,q,r))
    print("Project Euler 33 Solution = %s"  % d)

if __name__=='__main__':
    proj2()
    #test()

