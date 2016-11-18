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
        if ptest in sv.plist and ptest not in pm:
            pm.append(ptest)
    return pm

def get_dig_cnt ( n ):
    d = {}
    while n:
        dig = n%10
        n   = n/10
        if dig in d:
            d[dig] = d[dig]+1
        else:
            d[dig] = 1
    return d

def is_perm ( m, n ):
    dm = get_dig_cnt(m)
    dn = get_dig_cnt(n)
    for d in dm:
        if d not in dn:
            return False
        if dm[d]!=dn[d]:
            return False
    return True

def write_primes ( sv ):
    fname = "p0049_prime_list.txt"
    fd = open(fname,"w")

    for k in range(len(sv.plist)):
        fd.write("%6d " % sv.plist[k])
        if 0==((k+1)%8):
            fd.write("\n")

    fd.close()

def proj():
    s = sieve(10000)
    not_found = True
    for p in s.plist:
        if p<1400:
            continue
        if p>=10000:
            break
        b, c = p+3330, p+6660
        if s.is_prime(b) and s.is_prime(c) and is_perm(p,b) and is_perm(p,c):
            not_found = False
            print("%d %d %d" % (p,b,c))
            print("    %d%d%d" % (p,b,c))
    if not_found:
        print("Nothing found")
    
def proj_old ( ):
    s = sieve(10000)
    #write_primes(s)
    cnt = 0
    mn_list = []
    for p in s.plist:
        if p<1000:
            continue
        if p>10000:
            break
        strp = str(p)
        if '0' in strp:
            continue
        pm = perms(p,s)
        if 3==len(pm):
            pm.sort()
            pm_str = str(pm[0]) + str(pm[1]) + str(pm[2])
            if pm_str not in mn_list:
                mn_list.append(pm_str)
    for pm in mn_list:
        x1, x2, x3 = (int(pm[:4]),int(pm[4:8]),int(pm[8:]))
        d1 = x2 - x1
        d2 = x3 - x2
        if d1==d2:
            print("    This one:")
        print("%d %d %d, %4d %4d" % (x1, x2, x3, d1, d2))

def test ( ):
    pass

if __name__=='__main__':
    proj()
    #test()

