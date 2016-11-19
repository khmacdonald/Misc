#!/usr/local/bin/python

import bisect
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve

av = sys.argv
ac = len(av)

card_rank = { '2':2, '3':3, '4':4, '5':5,
              '6':6, '7':7, '8':8, '9':9,
              'T':10,'J':11,'Q':12,'K':13,'A':14 }

def next_hand ( fd ):
    line = fd.readline().strip()
    sl = line.split(' ')
    if 10!=len(sl):
        return None, None
    return sl[:5], sl[5:]

def get_kind( h ):
    knd = 0
    hd = {}
    mx = 0
    for cd in h:
        t, s = cd[0], cd[1]
        if t in hd:
            hd[t] = hd[t] + 1
        else:
            hd[t] = 1
        mx = max(mx,hd[t])
    if 4==mx:
        return 8 # Four of a kind
    elif 3==mx:
        for t in hd:
            if 2==hd[t]:
                return 7 # Full house
        return 4 # 3 of a kind
    elif 2==mx:
        cnt = 0
        for t in hd:
            if 2==hd[t]:
                cnt = cnt+1
        if 2==cnt:
            return 3 # two pair
        else:
            return 2 # 2 of a kind
    return 1 # no match

def is_flush ( h ):
    return h[0][1]==h[1][1]==h[2][1]==h[3][1]==h[4][1]

def is_straight ( h ):
    c = card_rank
    t = [c[h[0][0]],c[h[1][0]],c[h[2][0]],c[h[3][0]],c[h[4][0]]]
    t.sort()
    return t[0]==t[1]-1 and t[1]==t[2]-1 and t[2]==t[3]-1 and t[3]==t[4]-1

def hand ( h ):
    k = get_kind(h)
    flush = False
    straight = False
    if 1==k: # No pairs means a possible flush, straight, or straight flush
        straight = is_straight(h)
        flush = is_flush(h)
        if straight:
            k = 5
        if flush:
            k = 6
        if straight and flush:
            k = 9
    return k

def high_card ( p1, p2 ):
    c = card_rank
    h1 = [c[p1[0][0]],c[p1[1][0]],c[p1[2][0]],c[p1[3][0]],c[p1[4][0]]]
    h2 = [c[p2[0][0]],c[p2[1][0]],c[p2[2][0]],c[p2[3][0]],c[p2[4][0]]]
    m1 = max(h1)
    m2 = max(h2)
    while m1==m2:
        h1.remove(m1)
        h2.remove(m2)
        m1 = max(h1)
        m2 = max(h2)

    print("m1=%d, m2=%d, (%s,%s)" % (m1,m2,m1>m2,m1<m2))
    if m1>m2:
        w1, w2 = 1, 0
    elif m1<m2:
        w1, w2 = 0, 1
    else:
        w1, w2 = 0, 0

    print(w1,w2)
    return w1, w2

def check_pair ( p1, p2 ):
    pass

def check_eq_hand ( h1, p1, h2, p2 ):
    w1, w2 = 0, 0
    if 1==h1: # High card
        w1, w2 = high_card(p1,p2)
    elif 2==h1: # One pair
        pass
    elif 3==h1: # Two pair
        pass
    elif 4==h1: # three of a kind
        pass
    elif 5==h1: # straight
        pass
    elif 6==h1: # flush
        pass
    elif 7==h1: # full house
        pass
    elif 8==h1: # four of a kind
        pass
    else:       # straight flush
        pass

    return w1, w2

def who_wins ( p1, p2 ):
    w1, w2 = 0, 0
    h1 = hand(p1)
    h2 = hand(p2)
    if h1>h2:
        return 1, 0
    elif h1<h2:
        return 0, 1
    else:
        w1, w2 = check_eq_hand ( h1, p1, h2, p2 )

    return w1, w2

def proj():
    fname = "p054_poker.txt"
    fd = open(fname,"r")
    p1, p2 = next_hand(fd)
    w1, w2 = who_wins(p1,p2)
    print(w1,p1)
    print(w2,p2)
    fd.close()

if __name__=='__main__':
    proj()

