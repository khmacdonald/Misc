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
    
def proj():
    nums = set()
    for n in range(1,10):
        for p in range(1,30):
            np = n**p
            k = len(str(np))
            if k<p:
                break
            if k==p:
                nums.add(np)
    print("There are %d n-digit numbers that are n-powers" % len(nums))
    print(sorted(nums))
    return
            

if __name__=='__main__':
    proj()













