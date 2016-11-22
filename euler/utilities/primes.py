#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

class sieve ( object ):

    def __init__ ( self, n = 10000 ):
        '''
        Computes the sieve
        '''
        max_sieve = 1000000
        if n>max_sieve:
            print("%d is too large to compute sieve" % d)
            sys.exit(-1)

        self.mx = n * n
        self.sieve(n)

    def factor ( self, n ):
        '''
        Factors in into its prime components and their exponents.  Returns
        a list of tuples (p,e), where p is a prime factor and e is the 
        exponent of p.
        '''


        if n>(self.mx):
            print ( "%d is too large to factor. Max size is %d" % (n,mx))
            return False


        # All but possibly one prime factor are less than 
        # the square root of n
        sq = int(math.ceil(math.sqrt(n)))
        m = n
        f = []
        for p in self.plist:
            if p>sq:
                if m>1:
                    # Only one prime factor can be greater than sq
                    f.append((m,1)) 
                    break
            if 0==(m%p):
                # p divides m
                e = 1
                m = m/p

                # determine the exponent of p
                while 0==m%p:
                    e = e+1
                    m = m/p
                f.append((p,e))
        return f

    def is_prime ( self, n ):
        '''
        Determines if a number is prime
        '''
        if n>(self.mx):
            print ( "%d is too large to compute. Max size is %d" % (n,mx))
            return False

        isp = self.isp
        plist = self.plist

        # If small enough, use simple look up table
        if n<len(isp):
            if 1==isp[n]:
                return True
            else:
                return False
        
        plen = len(plist)
        pm = plist[plen-1]
        if n > (pm*pm):
            print ( "%d is too large to compute" % n)
            return False
        sq = math.ceil(math.sqrt(n))
        for p in plist:
            if p>sq:
                return True
            if 0==(n%p):
                return False

    def sieve ( self, n ):
        '''
        Creates a Sieve of Aritosthenes of size n
        '''
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
        self.isp = isp
        self.plist = plist

    def totient ( self, n ):
        '''
        Computes the totient of n.
        '''
        # If n is prime, the phi(n) = n-1
        if self.is_prime(n):
            return n-1

        # phi is multiplicative, i.e., phi(ab) = phi(a)phi(b)
        # where gcd(a,b)=1.
        # Also, phi(p**k) = p**(k-1)*(p-1)
        # So factor n into its prime factors and their exponents
        # and use the above two facts.
        f = self.factor(n)
        tnt = 1
        for a in f:
            p, e = a
            el = p-1
            if e>1:
                el = el * (p**(e-1))
            tnt = tnt * el
        return tnt


def test ():
    if 2!=ac:
        print("Usage: %s <integer>" % av[0])
        print("    Determines if a number is a prime")
    else:
        n = int(av[1])
        sv = sieve(n)
        print(sv.plist[:15])
        print(sv.isp[:15])


if __name__=='__main__':
    test()
