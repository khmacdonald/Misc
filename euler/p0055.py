#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def rev ( x ):
    r = 0
    while x:
        d = x % 10
        r = r*10 + d
        x = x / 10
    return r

def is_pal ( x ):
    s = '%d' % x
    n = len(s)
    ret = True
    for k in range(n/2):
        if s[k] != s[n-1-k]:
            return False
    return ret

def l_iter ( x ):
    return x + rev(x)

def lychrel_test ( x ):
    mx = 50
    for k in range(mx):
        x = l_iter(x)
        if is_pal(x):
            return True
    return False

def test ( ):
    x = 2345
    if 2==ac:
        x = int(av[1])
    if not lychrel_test(x):
        print("%d is Lychrel" % x)

def proj ( ):
    count = 0
    nl = 0
    for k in range(1,10000):
        sys.stdout.write("%d\r" % k)
        if lychrel_test(k):
            count = count + 1
        else:
            nl = nl + 1
    print("")
    print("Count = %d" % count)
    print("nl = %d" % nl)


def main ( ):
    proj()

if __name__=='__main__':
    main()


















