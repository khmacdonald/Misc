#!/usr/bin/python3

import random

def random_sequence ( n ) :
    return [ random.randrange(1000) for k in range(n) ]

def gnomesort ( seq ) :
    k = 0
    while k < len(seq) :
        if 0==k or seq[k-1] <= seq[k] :
            k += 1
        else:
            seq[k],seq[k-1] = seq[k-1], seq[k]
            k -= 1

def mergesort ( seq ) :
    mid = len(seq)//2
    lft, rgt = seq[:mid], seq[mid:]
    if len(lft) > 1 :
        lft = mergesort(lft)
    if len(rgt) > 1 :
        rgt = mergesort(rgt)
    res = []
    while lft and rgt :
        if lft[-1] >= rgt[-1] : 
            res.append(lft.pop())
        else:
            res.append(rgt.pop())
    res.reverse()
    return (lft or rgt) + res

if __name__=='__main__' :
    seq = random_sequence(10)
    print(seq)
    gnomesort(seq)
    print(seq)

    seq = random_sequence(10)
    print(seq)
    seq = mergesort(seq)
    print(seq)
