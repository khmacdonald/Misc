#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)

df = {0:1, 1:1, 2:2, 3:6, 4:24, 5:120, 6:720, 7:5040, 8:40320, 9:362880}

def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def dig_fac ( n ):
    sm = 0
    while n:
        d = n % 10
        n = n / 10
        sm = sm + df[d]
    return sm

def cycle_cnt ( n ):
    l = [n]
    x = n
    cnt = 1
    while True:
        y = dig_fac(x)
        if y in l:
            break
        l.append(y)
        cnt = cnt + 1
        x = y
    return cnt
    
def test():
    y = 69
    if 2==ac:
        y = int(av[1])
    ln = cycle_cnt(y)

def proj():
    ans = 0
    upper = 10**6
    cnt = 0
    for x in range(2,upper):
        sys.stdout.write("  x = %d\r" % x)
        if 60==cycle_cnt(x):
            cnt = cnt+1

    ans = cnt
    print_project_answer(74,ans)


if __name__=='__main__':
    proj()
    #test()

















