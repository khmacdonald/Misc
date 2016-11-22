#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def gcd ( a, b ):
    '''
    Returns the greatest common divisor of a and b, using the
    Euclidean algorithm.
    '''
    while b:
        t = a%b
        a = b
        b = t
    return a

def factorial ( n ):
    '''
    Returns n!
    '''
    if n<0:
        return 0
    elif 1==n or 0==n:
        return 1

    if n>20:
        print("%d is too large to compute the factorial" % n)
        return None
    
    fn = 1
    m = n
    while m>1:
        fn * m
        m = m-1
    return fn

def is_palindrome ( a ):
    n = str(a)
    return n==n[::-1]

def is_permutation ( a, b ):
    return sorted(str(a))==sorted(str(b))

def next_lex ( a ):
    '''
    Returns the next lexicographic permutation.
    I copied this from somewhere.
    '''
    i = len(a)-2
    while not ( i<0 or a[i] < a[i+1]):
        i = i-1
    if i<0:
        return False

    j = len(a)-1
    while not ( a[j]>a[i] ):
        j = j-1
    tmp = a[i]
    a[i] = a[j]
    a[j] = tmp
    a[i+1:] = reversed(a[i+1:])
    return True

def fast_sieve ( n ):
    '''
    Returns a list of all primes less than n.  (Uses xrange for speed)
    '''
    sieve = [True] * (n/2)
    for i in xrange(3,int(n**0.5)+1,2):
        if sieve[i/2]:
            sieve[i*i/2::i] = [False] * ((n-i*i-1)/(2*i)+1)
    return [2] + [2*i+1 for i in xrange(1,n/2) if sieve[i]]

if __name__=='__main__':
    test()












