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
    
def reduce_frac ( n, d ):
    a = gcd(n,d)
    return n/a, d/a

def get_dig ( n ):
    ones = n%10
    tens = n/10
    return tens, ones

def check_nums ( num, den ):
    return False
    
def proj2():
    '''
    Got this code online, but don't know what it's doing.
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

def common_dig ( m, n ):
    m0, m1 = m%10, (m/10)%10
    n0, n1 = n%10, (n/10)%10
    d, x, y = None, None, None
    if not (0==m0 and 0==n0):
        if m0==n0:
            d, x, y = m0, m1, n1
        elif m0==n1:
            d, x, y = m0, m1, n0
        elif m1==n0:
            d, x, y = m1, m0, n1
        elif m1==n1:
            d, x, y = m1, m0, n0
    return d,x,y

def reduced( num, den ):
    d = gcd(num,den)
    rn, rd = num/d, den/d
    return rn, rd

def proj ( ):
    nmx = 98
    dmx = nmx+1
    main_num = 1
    main_den = 1
    for num in range(10,nmx):
        for den in range(num+1,dmx):
            d, nm, dn = common_dig(num,den)
            if d:
                if nm*den==dn*num:
                    print("    %d/%d -> %d/%d" % (num,den,nm,dn))
                    rn,rd = reduced(num,den)
                    main_num = main_num * rn
                    main_den = main_den * rd
    mn, md = reduced(main_num,main_den)
    print("%d/%d" % (mn,md))

if __name__=='__main__':
    proj()



