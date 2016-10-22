#!/usr/local/bin/python

import copy
import sys

av = sys.argv
ac = len(av)

def conj ( z ):
    if 2!=len(z):
        return False
    
    w = [z[0], -z[1]]
    return w


def cmul ( z, w ):
    if 2!=len(z) or 2!=len(w):
        return False
    
    re = z[0]*w[0] - z[1] * w[1]
    im = z[0]*w[1] + z[1] * w[0]

    return [re,im]

def mod2 ( z ):
    if 2!=len(z):
        return False
    
    m = z[0]*z[0] + z[1]*z[1]
    return m

def is_cdiv ( z, w ):
    ww = conj(w)
    a = cmul(z,ww)
    if not a:
        return False
    print("a = (%d,%d)" % (a[1],a[0]))
    m = mod2(w)
    if not m:
        return False
    print("m = %d" % m)

    if 0==(a[0] % m) and 0==(a[1] % m):
        return True
    else:
        return False

def test ( ):
    z = [2,0]
    w = [1,1]
    if is_cdiv(z,w):
        print(z,w)
        print("Divisible");
    else:
        print(z,w)
        print("Not divisible");

if __name__=='__main__':
    test()


