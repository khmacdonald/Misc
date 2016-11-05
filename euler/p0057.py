#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def gcd ( a, b ):
    while b:
        t = a%b
        a = b
        b = t
    return a

def add ( a, b, c, d ):
    if b==d:
        num = a+c
        den = b
    else:
        den = b*d
        num = a*d + b*c
    dd = gcd(num,den)
    return num/dd, den/dd

def num_dig ( x ):
    dig = 0
    while x:
        dig = dig + 1
        x = x / 10
    return dig

def recurse ( n ):
    a, b = (2,1)
    c, d = (1,2)
    for k in range(n-1):
        num, den = add(a,b,c,d)
        c = den
        d = num
    num, den = add(1,1,c,d)
    return num, den

def test ( ):
    n = 2
    if 2==ac:
        n = int(av[1])
    num, den = recurse(n)
    nd = num_dig(num)
    dd = num_dig(den)
    print ("[%d] -> %d/%d" % (n,num,den))
    print ("    %d -> %d" % (num,nd))
    print ("    %d -> %d" % (den,dd))
    
def proj ( ):
    count = 0
    print("Here")
    for k in range(1,1000):
        sys.stdout.write("%d\r" % k)
        num, den = recurse(k)
        # Could be faster by putting the add 1 here
        nd = num_dig(num)
        dd = num_dig(den)
        if nd>dd:
            count = count + 1

    print("")
    print("Count = %d" % count)

def main ( ):
    proj()

if __name__=='__main__':
    main()


















