#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

def next_permutation_od (arr):
    # Find non-increasing suffix
    i = len(arr) - 1
    while i > 0 and arr[i - 1] >= arr[i]:
        i -= 1
    if i <= 0:
        return False
    
    # Find successor to pivot
    j = len(arr) - 1
    while arr[j] <= arr[i - 1]:
        j -= 1
    arr[i - 1], arr[j] = arr[j], arr[i - 1]
    
    # Reverse suffix
    arr[i : ] = arr[len(arr) - 1 : i - 1 : -1]
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

def proj():
    a = [0,1,2,3,4,5,6,7,8,9]
    cnt = 0
    mx = 1000000-2
    while next_lex(a):
        cnt = cnt + 1
        sys.stdout.write("%d\r" % cnt)
        if mx<=cnt and cnt<=mx+4:
            print("[%8d] %d%d%d%d%d %d%d%d%d%d" % (cnt,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9]))
        if cnt>mx+4:
            break
    

def test():
    chk = [0,1,2]
    while next_lex(chk):
        print(chk)

if __name__=='__main__':
    #test()
    proj()



'''
# 
# Next lexicographical permutation algorithm (Python)
# by Project Nayuki, 2014. Public domain.
# https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
# 


# -- Basic version --
# 
# Computes the next lexicographical permutation of the specified list in place,
# returning whether a next permutation existed. (Returns False when the argument
# is already the last possible permutation.)
# 
def next_permutation(arr):
    # Find non-increasing suffix
    i = len(arr) - 1
    while i > 0 and arr[i - 1] >= arr[i]:
        i -= 1
    if i <= 0:
        return False
    
    # Find successor to pivot
    j = len(arr) - 1
    while arr[j] <= arr[i - 1]:
        j -= 1
    arr[i - 1], arr[j] = arr[j], arr[i - 1]
    
    # Reverse suffix
    arr[i : ] = arr[len(arr) - 1 : i - 1 : -1]
    return True

# Example:
#   arr = [0, 1, 0]
#   next_permutation(arr)  (returns True)
#   arr has been modified to be [1, 0, 0]


# -- Comparator version --
# 
# Computes the next lexicographical permutation of the specified list in place,
# returning whether a next permutation existed. (Returns False when the argument
# is already the last possible permutation.)
# 
# comp is a comparison function - comp(x, y) returns a negative number if x is considered to be less than y,
# a positive number if x is considered to be greater than y, or 0 if x is considered to be equal to y.
# 
def next_permutation_comp(arr, comp):
    # Find non-increasing suffix
    i = len(arr) - 1
    while i > 0 and comp(arr[i - 1], arr[i]) >= 0:
        i -= 1
    if i <= 0:
        return False
    
    # Find successor to pivot
    j = len(arr) - 1
    while comp(arr[j], arr[i - 1]) <= 0:
        j -= 1
    arr[i - 1], arr[j] = arr[j], arr[i - 1]
    
    # Reverse suffix
    arr[i : ] = arr[len(arr) - 1 : i - 1 : -1]
    return True




'''









