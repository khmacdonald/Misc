#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_isp = None
g_plist = None

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
    g_isp = isp
    g_plist = plist
    return True

def l2dig ( l ):
    s = ''.join(l)
    n = int(s,10)
    print(s)
    print(n)

def permute ( d, l, r ):
    pass

def get_pan_nums ( ):
    dig = [ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" ]
    l2dig(dig)

def main():
    print("Main")
    get_pan_nums ( )

if __name__=='__main__':
    #main()
    n = 20
    if 2==ac:
        n = int(av[1])
    sieve(n)
    print(g_isp)
