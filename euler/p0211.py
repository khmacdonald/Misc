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

def sig2 ( n ):
    pass

def proj():
    pnum = 105
    answer = 0


    print("")
    print_project_answer(pnum,answer)
    

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

