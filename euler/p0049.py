#!/usr/local/bin/python

import bisect
import math
import sys

#from "/Users/khmacdonald/code/SVN/trunk/euler/utilities/" import primes
sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve

av = sys.argv
ac = len(av)

perm4 = [
    [3,2,1,0],
    [3,2,0,1],
    [3,1,2,0],
    [3,1,0,2],
    [3,0,2,1],
    [3,0,1,2], # 6
    [2,3,1,0],
    [2,3,0,1],
    [2,1,3,0],
    [2,1,0,3],
    [2,0,3,1],
    [2,0,1,3], # 12
    [1,3,2,0],
    [1,3,0,2],
    [1,2,3,0],
    [1,2,0,3],
    [1,0,3,2],
    [1,0,2,3], # 18
    [0,3,2,1],
    [0,3,1,2],
    [0,2,3,1],
    [0,2,1,3],
    [0,1,3,2],
    [0,1,2,3]  # 24
]

def get_dig ( p ):
    d = []
    d.append(p%10)
    p = p / 10
    d.append(p%10)
    p = p / 10
    d.append(p%10)
    p = p / 10
    d.append(p%10)
    return d

def perms ( p, sv ):
    global perm4
    d = get_dig(p)
    cnt = 0
    pm = []
    for perm in perm4:
        w,x,y,z = perm
        ptest = d[w]*1000 + d[x]*100 + d[y]*10 + d[z]
        if ptest in sv.plist:
            pm.append(ptest)
    return pm

def write_primes ( sv ):
    fname = "p0049_prime_list.txt"
    fd = open(fname,"w")

    for k in range(len(sv.plist)):
        fd.write("%6d " % sv.plist[k])
        if 0==((k+1)%8):
            fd.write("\n")

    fd.close()

def proj ( ):
    s = sieve(10000)
    #write_primes(s)
    cnt = 0
    mn_list = []
    for p in s.plist:
        if p<1000:
            continue
        if p>10000:
            break
        pm = perms(p,s)
        if 3==len(pm) and pm[0]>1000 and pm[1]>1000 and pm[2]>1000:
            pm.sort()
            if pm not in mn_list:
                mn_list.append(pm)
    for pm in mn_list:
        d1 = pm[1]-pm[0]
        d2 = pm[2]-pm[1]
        print("%d %d %d : %6d %6d" % (pm[0],pm[1],pm[2],d1,d2))

def test ( ):
    x = 1234
    if 2==ac:
        x = int(av[1])
    perms(x)

if __name__=='__main__':
    proj()
    #test()

