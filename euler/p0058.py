#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def sieve ( n ):
    sq = math.floor(math.sqrt(n))
    isp = [1] * (n+1)
    isp[0] = 0
    isp[1] = 0
    isp_len = len(isp)
    plist = []
    for k in range(2,isp_len):
        if 1==isp[k]:
            plist.append(k)
            m = k+k
            while m < isp_len:
                isp[m] = 0
                m = m+k
    return isp, plist

def is_prime ( n, isp, plist ):
    if n < len(isp):
        if 1==isp[n]:
            return True
    else:
        for p in plist:
            if 0==(n%p):
                return False
    return True

def print_corners ( ):
    mx = 100000
    fd = open("test.txt","w")
    isp, plist = sieve(mx)
    c,idx = (1,2)
    pcnt, tot = (0,0)
    while c<mx*mx:
        d = []
        for k in [0,1,2,3]:
            tot = tot + 1
            c = c + idx
            if is_prime(c,isp,plist):
                pcnt = pcnt + 1
                percent = float(pcnt)/float(tot)
                fd.write("p = %d, pcnt = %d, tot = %d\n" % (c,pcnt,tot))
                if percent<0.1:
                    print("Less than 10%% is %.3f" % percent)
                    print("    idx = %d, c = %d, tot = %d, pcnt = %d" % (idx,c,tot,pcnt))
                    return
        idx = idx + 2
    print("pcnt = %d, tot = %d" % (pcnt,tot))
    fd.close()

def main ( ):
    print_corners()

if __name__=='__main__':
    main()







