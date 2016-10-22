#!/usr/local/bin/python

import sys

av = sys.argv
ac = len(av)

def sum_dig ( x,n ):
    sm = 0
    while x>0:
        d = x%10
        sm = sm + d**n
        x = x/10
    return sm

def dnp ( n ):
    mx = 9**n * n
    print("%d -> %d" % (n,mx))
    tsum = 0
    for k in range(10,mx):
        sm = sum_dig(k,n)
        if sm == k:
            tsum = tsum + k
            # print("%d" %k )
    print("Total sum is %d" % tsum)
    return True

def main():
    dnp(5)

if __name__=='__main__':
    main()
