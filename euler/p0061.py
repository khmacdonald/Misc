#!/usr/local/bin/python

import bisect
import decimal
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)


decimal.getcontext().prec = 105

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def proj():
    pnum = 61
    answer = 0

    print("")
    print_project_answer(pnum,answer)
    

def test():
    rng = range(1,7)

    tri = [ my_euler.tri_num(k) for k in rng ]
    print(tri)

    sqr = [ my_euler.sqr_num(k) for k in rng ]
    print(sqr)

    pen = [ my_euler.pen_num(k) for k in rng ]
    print(pen)

    hx = [ my_euler.hex_num(k) for k in rng ]
    print(hx)

    hep = [ my_euler.hep_num(k) for k in rng ]
    print(hep)

    ot = [ my_euler.oct_num(k) for k in rng ]
    print(ot)

if __name__=='__main__':
    test()
    #proj()

