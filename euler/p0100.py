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

    mx = 0
    lines = fd.readlines()
    fd.close()
    for k in range(len(lines)):
        b, e = get_b_e(lines[k])
        x = compute(b,e)
        if x>mx:
            ml = k
            mx = x
            mb = b
            me = e

    ans = ml+1
    print_project_answer(92,ans)


if __name__=='__main__':
    proj()
    #test()

















