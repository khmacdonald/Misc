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

def sum_decimals ( k ):
    '''
    Sums the first 100 digits in a number
    '''
    sq = decimal.Decimal(k).sqrt()

    sm = 0
    for k in range(100):
        d = int(sq)         # Since k<100, there will always only be one digit here
        sm += d             # sums digit
        sq = (sq-d) * 10    # subtact off integer part

    return sm

def proj():
    pnum = 80
    answer = 0

    squares = [ k*k for k in range(1,11)]
    sm = 0
    for k in range(1,101):
        sys.stdout.write("k = %d\r" % k)
        if k in squares:
            continue
        sm += sum_decimals(k)


    answer = sm
    print("")
    print_project_answer(pnum,answer)
    

def test():
    n = 2
    sm = sum_decimals(n)
    print("%d -> %d" % (n,sm))
    

if __name__=='__main__':
    #test()
    proj()

