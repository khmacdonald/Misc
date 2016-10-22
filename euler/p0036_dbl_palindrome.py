#!/usr/local/bin/python

import copy
import sys

av = sys.argv
ac = len(av)

def dig10 ( x ):
    d = []
    while x:
        a = x % 10
        d.append(a)
        x = x / 10
    return d

def dig2 ( x ):
    d = []
    while x:
        if x&1:
            d.append(1)
        else:
            d.append(0)
        x = x>>1
    return d

def test():
    if 2!=len(sys.argv):
        print("USAGE: %s <integer>" % sys.argv[0])
        return False

    x = int(sys.argv[1])

    d10 = dig10(x)
    d10r = copy.copy(d10)
    d10r.reverse()
    d2  = dig2(x)
    d2r = copy.copy(d2)
    d2r.reverse()

    print(x)
    print(d10)
    print(d10r)
    print(d2)
    print(d2r)
    if d10==d10r and d2==d2r:
        print("Good")
    else:
        print("Not good")
    return True

def p36 ( ):
    sm = 0
    for k in range(1,1000000):

        d10 = dig10(k)
        d10r = copy.copy(d10)
        d10r.reverse()
        d2  = dig2(k)
        d2r = copy.copy(d2)
        d2r.reverse()
        if d10==d10r and d2==d2r:
            sm = sm + k
    
    print("Sum = %d" % sm)


if __name__=='__main__':
    p36()









