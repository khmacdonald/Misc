#!/usr/local/bin/python

import bisect
import math
import sys

#from "/Users/khmacdonald/code/SVN/trunk/euler/utilities/" import primes
sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve

av = sys.argv
ac = len(av)

def get_dig ( n ):
    dig = []
    while n:
        d = n % 10
        n = n / 10
        dig.append(d)
    return dig

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

def conc ( m, mm ):
    p = m*mm
    xstr = "%d%d%d" % (m,mm,p)
    return int(xstr)

def proj():
    mx = 987654321
    mn = 100000000
    num_mx_dig = 9
    n_max = int(math.ceil(math.sqrt(mx)))
    print(n_max)
    sm = 0
    x = True
    prods = []
    for n in range(1,n_max):
        if not x:
            break
        n_dig = get_dig(n)
        num_dig = len(n_dig)
        diff = num_mx_dig/2-num_dig
        if diff<0:
            break
        kmin = 10**diff
        for k in range(kmin,kmin*100):
            if k<n:
                x = False
                break
            y = conc(n,k)
            if y<mn:
                continue
            if y>mx:
                break
            if is_pan(y):
                p = n*k
                if p not in prods:
                    prods.append(p)
                    sm = sm + p
    print("")
    print(sm)


# ----------------------------------------------------------------------
# This is someone else's code
def is_pan2 ( n, s=9 ):
    n = str(n)
    return len(n)==s and not '1234567890'[:s].strip(n)

def proj2():
    fname = "p0032_out_02.txt"
    fd = open(fname,"w")
    p = set()
    sm = 0
    for k in range(2,60):
        start = 1234 if k<10 else 123
        for m in range(start,10000//k):
            if is_pan2(str(k) + str(m) + str(k*m)):
                prod = k*m
                sm = sm + prod
                fd.write("k = %5d, m = %5d, p = %5d, sum = %d\n" % (k,m,prod,sm))
                p.add(k*m)

    print("Sum of products = ",sum(p))
    print("Length of p is ",len(p))
    print(p)

    fd.close()
# ----------------------------------------------------------------------


if __name__=='__main__':
    #proj2()
    proj()
    #test()

