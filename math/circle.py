#!/usr/local/bin/python

import sys

av = sys.argv
ac = len(av)

pi = 3.14159265359

def cirumference ( r ):
    return 2 * pi * r

def area ( r ):
    return pi * r * r

if __name__=='__main__':
    r = 1
    if 2==ac:
        r = float(av[1])
    c = cirumference(r)
    a = area(r)
    print("Radius = %f, Circumference = %f, Area = %f" % (r,c,a))
    
