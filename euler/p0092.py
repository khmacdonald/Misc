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

def sq_sum ( n ):
    sm = 0
    while n:
        d = n % 10
        n = n / 10
        sm = sm + (d*d)
    return sm

def test():
    y = 44
    if 2==ac:
        y = int(av[1])
    x = sq_sum(y)
    print("%d -> %d" % (y,x))

def proj():
    ans = 0

    upper = 10**7
    print("Starting")
    for n in range(2,upper):
        sys.stdout.write("n = %d\r" % n)
        x = n
        while True:
            x = sq_sum(x)
            if 1==x:
                break
            if 89==x:
                ans = ans + 1
                break

    print_project_answer(92,ans)


if __name__=='__main__':
    proj()
    #test()

















