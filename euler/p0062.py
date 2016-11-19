#!/usr/local/bin/python

import bisect
from itertools import permutations
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
from my_euler import next_lex

av = sys.argv
ac = len(av)

def is_perfect_cube ( x ):
    return int(round(x**(1./3)))**3==x

def dig_list(x):
    # Count how many times each digit occurs in x
    d = {0:0,1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0}
    while x:
        dig = x % 10
        d[dig] = d[dig] + 1
        x   = x / 10
    return d

def get_cube_list ( lo, hi ):
    # Create list of each number and the digits dictionary for its cube
    dlist= []
    for x in range(lo,hi):
        y = x**3
        dlist.append([x, dig_list(y)])
    return dlist

def proj():
    lo, hi = 345, 10000
    # No need to compute the various permutations.  All permutations
    # have the same digits and the same number of digits.  So for each
    # cube between hi and lo, get a dictionary for all 10 digits and 
    # the number of times each digit occurs in each cube
    dlist = get_cube_list(lo,hi) 
    dlen = len(dlist)
    run = 4
    for k in range(dlen-run):
        # Get the number and the digits dictionary for its cube
        num, num_dic = dlist[k][0], dlist[k][1] 
        ncube = num*num*num
        cnt = 0
        for m in range(k+1,dlen):
            # Get the number and the digits dictionary for its cube
            mnum, mnum_dic = dlist[m][0], dlist[m][1]
            # Compare this digit dictionary to the kth dictionary
            if num_dic==mnum_dic:
                cnt = cnt+1

        # If we have exactly the correct number of runs print and break
        if cnt==run:
            print("%d -> %d - cnt = %d" % (num,ncube,cnt+1))
            break
    return
            

if __name__=='__main__':
    proj()













