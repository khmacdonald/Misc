#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)

def test():
    pass

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def frac_num ( den ):
    ans = 0
    num = den//2
    if num/float(den)==1.0/2.0:
        num = num-1
    for x in range(num,0,-1):
        if float(x)/den<=1/float(3):
            break
        if 1==my_euler.gcd(x,den):
            #print(" %d/%d " % (x,den))
            ans = ans+1
        num = num-1
    return ans

def proj():
    ans = 0
    upper = 12000
    for d in range(2,upper+1):
        sys.stdout.write("d = %d\r" % d)
        ans = ans + frac_num(d)
    
    print_project_answer(73,ans)


if __name__=='__main__':
    proj()
    #test()

















