#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

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



if __name__=='__main__':
    test()
