#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_max = 0
g_len = 0
g_isp = None
g_plist = None

def sieve ( n ):
    sq = math.floor(math.sqrt(n))
    isp = [1] * (n+1)
    isp[0] = 0
    isp[1] = 0
    isp_len = len(isp)
    plist = []
    for k in range(2,isp_len):
        if 1==isp[k]:
            plist.append(k)
            m = k+k
            while m < isp_len:
                isp[m] = 0
                m = m+k
    global g_isp
    global g_plist
    global g_len
    global g_max
    g_isp = isp
    g_plist = plist
    g_len = len(g_isp)
    g_max = g_len*g_len
    return True

def is_prime ( n ):
    global g_isp
    global g_plist
    global g_len
    global g_max
    if not g_isp or not g_plist:
        print("is_prime needs sieve")
        sys.exit(-1)
    if n>g_max:
        print("%d is too larg.  Must be smaller than %d." % (n,g_max))
        return False
    if n<g_len:
        if 1==g_isp[n]:
            return True
    for p in g_plist:
        if 0==(n%p):
            return False
    return True


def get_ndic ( n ):
    d = {}
    for k in range(1,n+1):
        dic[k] = 1
    return dic

def is_npan( number, n ):
    if n>9:
        n = 9
    dd = {}
    for k in range(1,n+1):
        dd[k] = 1
    while number:
        d = number % 10;
        number = number / 10
        if d not in dd:
            return False
        if dd[d]==0:
            return False
        dd[d] = 0
    return True

def next_lex ( a ):
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


def list_2_num ( a ):
    num = 0
    for d in a:
        num = num * 10 + d
    return num


def factorial ( n ):
    if n<0:
        return 0
    if n==1:
        return 1
    return n*factorial(n-1)

def is_pan ( n, m ):
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

def is_pan_prime ( n ):
    if not is_pan(n,len(str(n))):
        return False
    if is_prime(n):
        return True
    return False
    

def proj():
    n = 987654321
    n = 87654321
    mx = int(math.ceil(math.sqrt(n)))
    sieve(mx)
    found = False
    print("    Starting at %d" % n)
    while n:
        sys.stdout.write("Testing %d\r" % n)
        if 0==(n%1000000):
            print("")
        if is_pan_prime(n):
            found = True
            pp = n
            break
        n = n-2
    
    print("")
    if not found:
        print("Did not find a pandigital prime")
    else:
        print("%d is the largest pandigial prime" % pp)

def test():
    sieve(100)
    n = 4231
    if is_pan_prime(n):
        print("%d is a pandigital prime" % n)
    else:
        print("%d is not a pandigital prime" % n)

if __name__=='__main__':
    proj()
    #test()
