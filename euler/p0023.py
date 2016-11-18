#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def sum_div ( n ):
    sqn = int(math.sqrt(n))
    sm = 1
    for k in range(2,sqn+1):
        if 0==(n%k):
            sm += (k+n/k)
    if n == sqn*sqn:
        sm = sm - sqn
    return sm 
    
def proj ( ):
    mx = 20162
    sm = 0
    abn = []
    is_abn = [0] * mx
    for number in range(1,mx):
        sys.stdout.write("n = %d\r" % number)
        sdiv = sum_div(number)
        if sdiv>number:
            is_abn[number] = 1
            abn.append(number)
        abn_sum = False
        for a in abn:
            if a>((number//2)+1):
                break
            d = number-a
            if is_abn[d]:
                abn_sum = True
        if not abn_sum:
            sm = sm + number
    print("\nMy answer is %d" % sm)
        




#--- Calculate the sum of proper divisors for n--------------------------------------------------
def d(n):
    s = 1
    t = math.sqrt(n)
    for i in range(2, int(t)+1):
        if n % i == 0: 
            s += i + n/i # both i and n/i are proper divisors of n
    if t == int(t): 
        s -= t    #correct s if t is a perfect square
    return s

def proj2(): 
    L, s = 20162, 0
    abn = set()

    for n in range(1, L):
        sys.stdout.write("n = %d\r" % n)
        dsum = d(n)
        if dsum > n:
            abn.add(n) # n is abundant
        if not any( (n-a in abn) for a in abn ):
            s += n
                                          
    print("")
    print "Project Euler 23 Solution =", s

if __name__=='__main__':
    proj2()
    proj()



















