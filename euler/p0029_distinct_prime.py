#!/usr/local/bin/python

import sys

av = sys.argv
ac = len(av)

def distinct_primes ( x, y ):
    if x<2 or y<2:
        print("a = %d and b = %d both need to be greater than 2" % (x,y))
        return False

    aa, bb = (x,y)
    a = 2
    l = []
    while a<=aa:
        b = 2
        while b<=bb:
            z = a**b
            if z not in l:
                l.append(z)
            z = b**a
            if z not in l:
                l.append(z)
            b = b+1
        a = a+1
    
    print("2<=a<=%d and 2<=b<=%d has %d distinct numbers" % (x,y,len(l)))
    return True

def main():
    if 3!=ac:
        print("USAGE: %s <a> <b>" % av[0])
        return False
    a = int(av[1])
    b = int(av[2])
    distinct_primes(a,b)

if __name__=='__main__':
    main()
