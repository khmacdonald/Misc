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

def get_k ( n ):
    y = 1+2*n*(n-1)
    k = (1+math.sqrt(y))/2.0
    #print("%d: %f -> %d" % (n,k,int(k)))
    #return int(math.floor(k))
    return k

def comp_check ( n, k ):
    return 2*k*(k-1) - n*(n-1)

def proj2():
    b, n, L = 85, 120, 10**12
    while n<=L:
        b, n = 3*b + 2*n - 2, 4*b + 3*n - 3
        print("    b = %d, n = %d\r" % (b,n))
    print("")
    print("Total disks          = %d (%f)" % (n,math.log(n,10)))
    print("Number of blue disks = %d (%f)" % (b,math.log(b,10)))

def proj():
    pnum = 100
    answer = 0
    start = 10**12
    #start = 1 070 379 110 497
    start = 1070379000000
    number = 10**8
    end = start+number
    keep_going = True
    '''
    print("%d -> %f" % (known,math.log(known,10)))
    if number<known:
        print("Less")
    else:
        print("Greater")
    return
    '''
    known = 756872327473
    n = start
    b = 0
    while keep_going:
        k = get_k(n)
        sys.stdout.write("    %d -> n = %d, k = %d\r" % (known,n,k))
        '''
        if k.is_integer():
            kp = int(k)
            if b!=0:
                diff = kp-b
                print("\nDifference is %d" % diff)
            b = kp
        '''
        k = int(math.floor(k))
        if 0==comp_check(n,k):
            keep_going = False
            answer = k
            break
        if 0==comp_check(n,k+1):
            keep_going = False
            answer = k+1
            break
        n = n+1
        if n>end:
            print("    Too large")
            break
    print("")
    print("n=%d, k=%d" % (n,k))
    print_project_answer(pnum,answer)
    

def test():
    n = 1
    if 2==ac:
        n = int(av[1])
    k = get_k(n)
    check(n,k)
    a = comp_check(n,k)
    print("n=%d, k=%d, a=%d" % (n,k,a))

if __name__=='__main__':
    #test()
    proj()
    #proj2()

