#!/usr/local/bin/python

import bisect
import math
import sys

#from "/Users/khmacdonald/code/SVN/trunk/euler/utilities/" import primes
sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve

av = sys.argv
ac = len(av)

def is_pan ( n ):
    dig = [1,1,1,1,1,1,1,1,1,1]
    while n:
        d = n % 10
        if 0==d:
            return False
        n = n / 10
        if 0==dig[d]:
            return False
        dig[d] = 0
    return True

def conc ( n, k ):
    m = n
    xstr = ''
    for x in range(1,k+1):
        xstr = '%s%s' % (xstr,n)
        n = n+m
    y = int(xstr)
    return y

def proj():
    mx = 9876543211
    mn = 1234567890
    x = True
    mmx = 1
    fname = "p0038_out.txt"
    fd = open(fname,"w")
    for n in range(1,1000000):
        if not is_pan(n):
            continue
        for k in range(1,10):
            y = conc(n,k)
            if n==9 and k==5:
                print(n,k,y)
            if n==9327:
                print(n,k,y)
            if y > mx:
                break
            if is_pan(y):
                if y>mmx:
                    mmx = y
                    fd.write("MAX n = %5d, k = %5d, y = %d\n" % (n,k,y))

    print(mmx)
    fd.close()
    return
        

def test ( ):
    n = 12345
    if 2==ac:
        n = int(av[1])
    if is_pan(n):
        print("%d is pandigital" % n)
    else:
        print("%d is not pandigital" % n)

def test01 ( ):
    y = conc(9,5)
    print(y)

if __name__=='__main__':
    proj()
    #test01()

