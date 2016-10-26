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
    
def proj ( ):
    lower = 10
    upper = 100
    for k in range(lower,upper-1):
        if 0==(k%10):
            ten = True 
        else:
            ten = False
        if 0==(k%11):
            eleven = True
        else:
            eleven = False
        for m in range(k+1,upper):
            if (ten and 0==(m%10)) or (eleven and 0==(m%11)):
                continue
            if check_nums(k,m):
                rn, rd = reduce_frac(k,m)
                print("%d/%d -> %d/%d" % (k,m,rn,rd))
    return

def main():
    print("Main")
    proj()

def test ( ):
    n, d = (49,98)
    n, d = (30,50)
    if check_nums(n,d):
        print("Outcome: %d %d pass" % (n,d))
    else:
        print("Outcome: %d %d fail" % (n,d))


if __name__=='__main__':
    main()



