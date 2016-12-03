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
    pnum = 401
    answer = 0
    mx = 10**6

    print("This is a poorly designed problem")
    sv = my_euler.fast_sieve(mx)

    print("")
    print_project_answer(pnum,answer)
    

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

