#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def factor ( n ):
    if n<0:
        return 0
    elif 1==n or 0==n:
        return 1
    else:
        return n * factor(n-1)

def get_fdic ( ):
    d = {}
    sm = 0
    for k in range(10):
        f = factor(k)
        d[k] = f
        sm = sm + f
    return d
    
def get_dig ( n, fdic ):
    sm = 0
    while n:
        d = n % 10
        n = n / 10
        fd = fdic[d]
        sm = sm + fd
    return sm

def dig_fac ( ):
    fdic = get_fdic()
    mx = fdic[9] * 10
    dlist = []
    cnt = 0
    tot = 0
    for k in range(10,mx+1):
        sm = get_dig(k,fdic)
        if k==sm:
            print(k)
            tot = tot + k
            cnt = cnt + 1

    print("There are %d such numbers" % cnt)
    print("Sum = %d" % tot)
    return True


def main():
    print("Main")
    dig_fac( )

def test ( ):
    n = 2
    if 2==ac:
        n = int(av[1])
    k = factor(n)
    print("%d! = %d" % (n,k))

if __name__=='__main__':
    main()





