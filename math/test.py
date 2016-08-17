#!/usr/local/bin/python

import sys

av = sys.argv
ac = len(av)

if __name__=='__main__':
    x = -2.0
    n = 120
    if 2<=ac:
        x = float(av[1])
    if 3<=ac:
        n = int(av[2])
    k = 1
    sn = 1
    s = 1
    while k<=n:
        sn = sn*x/k
        s += sn
        k += 1
    print(sn)
    print(s)
    
