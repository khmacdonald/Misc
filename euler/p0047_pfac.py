#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_sieve = []

def is_good( f1, f2, f3 ):
    S1 = set(f1) & set(f2)
    S2 = set(f1) & set(f3)
    S3 = set(f2) & set(f3)
    if len(S1)>0 or len(S2)>0 or len(S3)>0:
        return False
    else:
        return True


def sieve ( n ):
    isp = [1] * n
    plist = []
    sq = math.floor(math.sqrt(n))
    isp_len = len(isp)
    for k in range(2,isp_len):
        if 1==isp[k]:
            plist.append(k)
            m = k+k
            while m < isp_len:
                isp[m] = 0
                m = m+k
    global g_sieve
    g_sieve = plist

def factor ( n ):
    global g_sieve
    sq = math.floor(math.sqrt(n))
    f = []
    for p in g_sieve:
        if p>sq:
            if n>1:
                f.append(n)
            break;
        if 0==(n%p):
            n = n/p
            f.append(p)
            while 0==n%p:
                n = n/p
    return f


def test():
    n = 1849
    if 2==ac:
        n = int(av[1])
    f = factor(n)
    print("The factors of %d are:" % n)
    print(f)

def main ():
    # 490 = 2*3*5*7
    pass

if __name__=='__main__':
    sieve(100000)    
    test()

