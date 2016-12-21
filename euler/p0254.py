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

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d\n\n" % (project_output,answer))

def proj():
    pnum = 152
    answer = 0

    print("")
    print_project_answer(pnum,answer)
    return

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

