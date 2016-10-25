#!/usr/local/bin/python

import bisect
import sys

av = sys.argv
ac = len(av)

def get_words ( ):
    fname = "p042_words.txt"
    fd = open(fname,"r")
    data = fd.read()
    fd.close()
    sline = data.split(',')
    words = []
    for word in sline:
        w = word.replace('"','')
        words.append(w)
    return words

def get_tnums ():
    tnums = []
    for k in range(1,100):
        n = k*(k+1)
        n = n/2
        tnums.append(n)
    return tnums

def get_wval ( w ):
    alpha = {"A" : 1,
             "B" : 2,
             "C" : 3,
             "D" : 4,
             "E" : 5,
             "F" : 6,
             "G" : 7,
             "H" : 8,
             "I" : 9,
             "J" : 10,
             "K" : 11,
             "L" : 12,
             "M" : 13,
             "N" : 14,
             "O" : 15,
             "P" : 16,
             "Q" : 17,
             "R" : 18,
             "S" : 19,
             "T" : 20,
             "U" : 21,
             "V" : 22,
             "W" : 23,
             "X" : 24,
             "Y" : 25,
             "Z" : 26
            }
    sm = 0
    for c in w:
        if c in alpha:
            sm += alpha[c]
    return sm
    
def count_twords ( words, tnums ):
    cnt = 0
    for w in words:
        v = get_wval(w)
        if v in tnums:
            cnt += 1
    print(cnt)

def main():
    words = get_words()
    tnums = get_tnums ()
    mx = max(tnums)
    print("Max  = %d" % mx)
    count_twords(words,tnums)

if __name__=='__main__':
    main()
