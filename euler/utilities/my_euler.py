#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def rational_add ( a, b ):
    x = a[0] * b[1] + a[1] * b[0]   # Compute the numerator
    y = a[1] * b[1]                 # Compute the denominator
    return [x,y]

def count_dig ( n ):
    cnt = 0
    while n :
        cnt = cnt + 1
        n = n/10
    return cnt

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

def fast_sieve ( n ):
    '''
    Returns a list of all primes less than n.  (Uses xrange for speed)
    '''
    sieve = [True] * (n/2)
    for i in xrange(3,int(n**0.5)+1,2):
        if sieve[i/2]:
            sieve[i*i/2::i] = [False] * ((n-i*i-1)/(2*i)+1)
    return [2] + [2*i+1 for i in xrange(1,n/2) if sieve[i]]

def fibonacci ( n ):
    if 1==n or 1==2:
        return 1
    x1, x2 = 1, 1
    for k in range(3,n+1):
        xn = x1+x2
        x1 = x2
        x2 = xn
    return x2

def fibonacci_exp ( n ):
    s5 = math.sqrt(5)
    x = (1 + s5)/2.0
    y = 1-x
    fn = (x**n - y**n) / s5
    return fn

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

def hep_num ( n ):
    return n * ( 5 * n - 3 ) / 2

def hex_num ( n ):
    hx = n * ( 2 * n - 1 ) 
    return hx

def is_palindrome ( a ):
    n = str(a)
    return n==n[::-1]

def is_pandigital ( n, m=9 ):
    dig = [1]*(m+1)
    while n:
        d = n % 10
        if d>(m):
            return False
        if 0==d:
            return False
        n = n / 10
        if dig[d]==0:
            return False
        dig[d] = 0
    return True

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

def oct_num ( n ):
    return n * ( 3 * n - 2 )

def pen_num ( n ):
    return n * ( 3 * n - 1 ) / 2

def prime_factor ( n, sv ):
    sqn = int(math.sqrt(n))
    fac = []
    m = n
    for p in sv:
        if p>sqn:
            break
        if 0==(m%p):
            m = m/p
            e = 1
            while 0==(m%p):
                e = e+1
                m = m/p
            fac.append((p,e))
    if m>1:
        fac.append((m,1))
    return fac

def reduce_frac ( a, b ):
    d = gcd(a,b)
    return a/d, b/d

def sqr_num ( n ):
    return n * n 

def sum_fac ( n ):
    s = 1
    t = sqrt(n)
    for i in range(2, int(t)+1):
        if n % i == 0: 
            s += i + n/i
    if t == int(t): 
        s -= t    #correct s if t is a perfect square
    return s

def sum_fac_sq ( n ):
    s = 1
    t = sqrt(n)
    for i in range(2, int(t)+1):
        if n % i == 0: 
            f2 = n/i
            s += (i*i + f2*f2)
    if t == int(t): 
        s -= (t*t)    #correct s if t is a perfect square
    return s

def tri_num ( n ):
    return n * ( n + 1 ) / 2

if __name__=='__main__':
    test()












