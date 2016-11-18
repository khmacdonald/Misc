#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

'''
a+b+c = p
    => c = p-(a+b)
a2+b2 = c2
    => c = sqrt(a2+b2)

->
    sqrt(a2+b2) = p-(a+b)
          a2+b2 = p2-2p(a+b)+(a+b)2
          a2+b2 = p2-2pa-2pb+a2+2ab+b2
              0 = p2-2pa-2pb+2ab
              0 = p2-2pa+b(2a-2p)
       b(2a-2p) = 2pa-p2
              b = (2pa-p2)/(2a-2p)
             
'''
def num_rt ( p ):
    a,b,c = (0,0,0)
    sol = []
    for a in range(1,p):
        num = p*p - 2*a*p
        den = 2*(p-a)
        if den==0:
            continue
        b = num/den
        if b<=0:
            continue
        if num == b*den:
            c = math.sqrt(a*a + b*b)
            if c<a or c<b:
                continue
            if c.is_integer():
                tr = [a,b,int(c)]
                tr.sort()
                if tr not in sol:
                    sol.append(tr)
    return sol

def proj():
    mx = -1
    pmx = 0
    for p in range(5,1001):
        sol = num_rt(p)
        nsol = len(sol)
        if nsol>mx:
            mx = nsol
            pmx = p
    print("There are %d solutions for p = %d" % (mx,pmx))

def test():
    sol = num_rt(120)
    print("Solution has %d elements" % len(sol))
    for tr in sol:
        print(tr)

if __name__=='__main__':
    proj()



















