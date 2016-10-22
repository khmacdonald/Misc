#!/usr/local/bin/python

import sys

av = sys.argv
ac = len(av)

def circular(n):
    if n<0:
        print("ERROR: %d is not positive" % n)
        sys.exit(-1)
    if n<10:
        return n

    d = n % 10
    n = n/10
    x = 10
    while x<n:
        x *= 10
    return d*x + n

def test_circle ():
    if 2!=ac:
        print("USAGE: %s <integer>" % av[0])
        return False
    n = int(av[1])
    c = circular(n)
    print("%d -> %d" % (n,c))

if __name__=='__main__':
    test_circle()

