#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_sieve = []

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
    return isp, plist

def add_2_list ( f, n, m ):
    g = []
    if len(f)==0:
        return [n]
    for e in f:
        x = e*n
        if 0==(m%x) and x<m:
            g.append(x)
    for e in g:
        f.append(e)
    if n<m and n not in f:
        f.append(n)
    f.sort()
    return f

def get_divisors ( n, isp, plist, mx ):
    if n<len(isp):
        if isp[n]:
            return [(n,1)]
    sq = math.floor(math.sqrt(n))
    f = [1]
    m = n
    for p in plist:
        if p>sq:
            if n>1:
                f = add_2_list(f,p,m)
            break
        if 0==(n%p):
            e = 1
            n = n/p
            f = add_2_list(f,p,m)
            t = p
            while 0==n%p:
                t = t*p
                e = e+1
                n = n/p
                f = add_2_list(f,t,m)
    return f

def test():
    y = 12
    mx = 100
    isp, plist = sieve ( mx )
    d = get_divisors(y,isp,plist,mx)
    s = sum(d)
    dstr = ' '.join(str(x) for x in d)
    print("%d -> %s - %d" % (y,dstr,s))

def get_abundant():
    mx = 28130
    #mx = 100
    isp, plist = sieve(mx)    
    abundant = []
    is_abundant = [0] * mx
    for k in range(4,mx):
        d = get_divisors(k,isp,plist,mx)
        if len(d)>1:
            sm = sum(d)
            if sm>k:
                #dstr = ' '.join(str(x) for x in d)
                #print("k=%d, sm=%d, divisors=%s" % (k,sm,dstr))
                abundant.append(k)
                is_abundant[k] = 1
    return abundant, is_abundant

def is_sum ( k, abundant, is_abundant ):
    for a in abundant:
        if a>=k:
            break
        d = k-a
        if 1==is_abundant[d]:
            return True
    return False

def main ( ):
    mx = 28123
    print("Getting abundant")
    abundant, is_abundant = get_abundant()
    sm = 0
    print("Starting")
    for k in range(1,mx):
        sys.stdout.write("%d\r" % k)
        if not is_sum(k,abundant,is_abundant):
            sm = sm + k
    print("")
    print(sm)

def proj ( ):
    if 2!=ac:
        print("Usage: %s <integer>" % av[0])
        print("    Factors an integer")
    else:
        main()

if __name__=='__main__':
    #test()
    main()



















