#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)


def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def compute ( base, exp ):
    if base==0:
        return 0
    x = math.log(base)
    return exp*x
    
def get_b_e ( line ):
    b, e = 0, 0
    line = line.strip()
    sl = line.split(',')
    if 2==len(sl):
        b = int(sl[0])
        e = int(sl[1])

    return b, e

def test():
    y = 44
    if 2==ac:
        y = int(av[1])

def proj():
    ans = 0

    fname = "p099_base_exp.txt"
    fd = open(fname,"r")

    line = fd.readline()
    b1, e1 = get_b_e(line)
    x1 = compute(b1,e1)

    line = fd.readline()
    b2, e2 = get_b_e(line)
    x2 = compute(b1,e1)
    if x1>x2:
        print("%d**%d > %d**%d" % (b1,e1,b2,e2))
    else:
        print("%d**%d < %d**%d" % (b1,e1,b2,e2))

    fd.close()
    print_project_answer(92,ans)


if __name__=='__main__':
    proj()
    #test()

















