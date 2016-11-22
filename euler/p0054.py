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

def sort_hand ( h ):
    cr = card_rank
    hn = [(cr[cd[0]],cd[1]) for cd in h]
    hn.sort()
    return hn

'''
1 - high card
2 - one pair
3 - two pair
4 - three of a kind
5 - straight
6 - flush
7 - full house
8 - four of a kind
9 - straight flush
'''
def get_kind ( h ):
    '''
    Determines a first pass kind by looking for matches.
    '''
    d = {}
    mx = 0
    for cd in h:
        if cd[0] in d: 
            d[cd[0]] += 1 
        else: 
            d[cd[0]] = 1
        if mx<d[cd[0]]: 
            mx = d[cd[0]]
            cmx = cd[0]
    if 1==mx:
        return 1, d # high card
    elif 2==mx:
        for c in d:
            if c!=cmx and 2==d[c]:
                return 3, d # two pair
        return 2, d # one pair
    elif 3==mx:
        for c in d:
            if c!=cmx and 2==d[c]:
                return 7, d # full house
        return 4, d # three of a kind
    else:
        return 8, d # four of a kind
    
def is_flush ( h ):
    '''
    Determines if all the cards have the same suit
    '''
    return h[0][1]==h[1][1]==h[2][1]==h[3][1]==h[4][1]
    
'''
card_rank = { '2':2, '3':3, '4':4, '5':5,
              '6':6, '7':7, '8':8, '9':9,
              'T':10,'J':11,'Q':12,'K':13,'A':14 }
'''
def is_straight ( h ):
    c = card_rank
    t = [h[0][0],h[1][0],h[2][0],h[3][0],h[4][0]]
    t.sort()
    straight = False
    if t[4]==14:
        if 2==t[0] and 3==t[1] and 4==t[2] and 5==t[3]:
            straight = True
        elif 10==t[0] and 11==t[1] and 12==t[2] and 13==t[3]:
            straight = True
    elif t[0]==t[1]-1 and t[1]==t[2]-1 and t[2]==t[3]-1 and t[3]==t[4]-1:
        straight = True
    return  True

'''
5 - straight
6 - flush
9 - straight flush
'''
def check_straight_n_flush ( h ):
    '''
    Checks for flush, straight, or straight flush
    '''
    k = 1
    flush    = is_flush(h)
    straight = is_straight(h)
    if straight:
        k = 5
    if flush:
        k = 6
    if straight and flush:
        k = 9
    return k

def check_high_card ( h1, h2 ):
    '''
    Staring with the high card (h1 and h2 are all ready sorted), 
    find the first card that's highest.  If highest ranked cards
    are the same, look at the next highest and so forth.
    '''
    length = len(h1)
    for k in range(length-1, -1,-1):
        if h1[k][0]>h2[k][0]:
            return 1, 0
        if h1[k][0]<h2[k][0]:
            return 0, 1
    return 0, 0

# No match
def kind_1 ( h1, d1, h2, d2 ):
    '''
    No mathces were found, so determine if a straight, flush, 
    straight flush, or find high card.
    '''
    w1, w2 = 0, 0
    k1 = check_straight_n_flush(h1)
    k2 = check_straight_n_flush(h2)
    if k1>k2:
        return 1, 0
    if k1<k2:
        return 0, 1
    # If both players have nothing, a straight, a flush, or a
    # straight flush, all that matters is the high card
    return check_high_card(h1,h2)

# One pair
def kind_2 ( h1, d1, h2, d2 ):
    '''
    Check to see which pair is highest.  If they are the same,
    compare the high card of the remaining cards.
    '''
    for c in d1:
        if 2==d1[c]:
            c1 = c
            break
    for c in d2:
        if 2==d2[c]:
            c2 = c
            break
    if c1>c2:
        return 1, 0
    if c1<c2:
        return 0, 1
        
    # Remove the pairs from the hand and compare the high
    # card in the remaining cards.
    for cd in h1:
        if c1==cd[0]:
            h1.remove(cd)
    for cd in h2:
        if c2==cd[0]:
            h2.remove(cd)
    return check_high_card(h1,h2)

# two pair
def kind_3 ( h1, d1, h2, d2 ):
    '''
    Compares two hands with two pair. 
    '''
    w1, w2 = 0, 0
    for c in d1:
        if 2==d1[c]:
            c1_1 = c
            break
    del d1[c1_1]
    for c in d1:
        if 2==d1[c]:
            c1_2 = c
            break
    del d1[c1_2]

    for c in d2:
        if 2==d2[c]:
            c2_1 = c
            break
    del d2[c2_1]
    for c in d2:
        if 2==d2[c]:
            c2_2 = c
            break
    del d2[c2_2]

    # Checks to see if one hand had a pair greater than both
    # pairs in other hand
    if (c1_1>c2_1 and c1_1>c2_2) or (c1_2>c2_1 and c1_2>c2_2):
        return 1, 0
    if (c2_1>c1_1 and c2_1>c1_2) or (c2_2>c1_1 and c2_2>c1_2):
        return 0, 1

    # If both pairs are the same in each hand, compare the 
    # remaining card.
    for c in d1:
        c1 = c
    for c in d2:
        c2 = c
    if c1>c2:
        return 1, 0
    if c1<c2:
        return 0, 1
    return w1, w2

# 3 of a kind
def kind_4 ( h1, d1, h2, d2 ):
    '''
    See with three of a kind is of higher value
    '''
    for c in d1:
        if 3==d1[c]:
            c1 = c
            break
    for c in d2:
        if 3==d2[c]:
            c2 = c
            break
    if c1>c2:
        return 1, 0
    else:
        return 0, 1

# Full house check
def kind_7 ( h1, d1, h2, d2 ):
    '''
    See which three of a kind in the full house is of higher value.
    '''
    w1, w2 = 0, 0
    for c in d1:
        if 3==d1[c]:
            c1 = c
            break
    for c in d2:
        if 3==d2[c]:
            c2 = c
            break
    if c1>c2:
        return 1, 0
    else:
        return 0, 1
    
def kind_8 ( h1, d1, h2, d2 ):
    '''
    See which four of a kind is of higher value.
    '''
    w1, w2 = 0, 0
    for c in d1:
        if 4==d1[c]:
            c1 = c
            break
    for c in d2:
        if 4==d2[c]:
            c2 = c
            break
    if c1>c2:
        return 1, 0
    else:
        return 0, 1

'''
1 - high card
2 - one pair
3 - two pair
4 - three of a kind
7 - full house
8 - four of a kind
'''
def same_kind ( h1, d1, h2, d2, k ):
    '''
    If each player has the same type of hand, look deeper at
    the hand for all the special cases of that kind.
    '''
    w1, w2 = 0, 0
    if 1==k:
        return kind_1(h1,d1,h2,d2) # No match (possible straight and or flush)
    if 2==k:
        return kind_2(h1,d1,h2,d2) # One pair
    if 3==k:
        return kind_3(h1,d1,h2,d2) # Two pair
    if 4==k:
        return kind_4(h1,d1,h2,d2) # Three of a kind
    if 7==k:
        return kind_7(h1,d1,h2,d2) # Full house
    if 8==k:
        return kind_8(h1,d1,h2,d2) # Four of a kind
    return w1, w2

def cmp_hands ( h1, h2 ):
    '''
    Compare sorted hands
    '''
    w1, w2 = 0, 0
    k1, d1 = get_kind(h1)
    k2, d2 = get_kind(h2)

    # If kinds are different, which hand is better?
    if k1>k2:
        return 1, 0
    if k1<k2:
        return 0, 1
    
    # If the kinds are the same, look deeper
    return same_kind(h1,d1,h2,d2,k1)

def who_wins ( p1, p2 ):
    '''
    Sort each hand by card value and determine who wins
    '''
    w1, w2 = 0, 0
    s1 = sort_hand ( p1 )
    s2 = sort_hand ( p2 )
    w1, w2 = cmp_hands(s1, s2)
    return s1, w1, s2, w2

def proj():
    fname = "p054_poker.txt"
    fd = open(fname,"r")
    get_next_hand = True
    player1 = 0
    player2 = 0
    total = 0
    while get_next_hand:
        p1, p2 = next_hand(fd)
        if not p1:
            get_next_hand = False
            break
        s1, w1, s2, w2 = who_wins(p1,p2)
        player1 += w1
        player2 += w2
        total   += 1
    fd.close()
    print("Player 1 has %d wins" % player1)
    print("Player 2 has %d wins" % player2)
    print("Total hands played is %d" % total)

if __name__=='__main__':
    proj()

