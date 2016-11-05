#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

test_str = [
["3"],
["7 4"],
["2 4 6"],
["8 5 9 3"]]

main_str = [
["75"],
["95 64"],
["17 47 82"],
["18 35 87 10"],
["20 04 82 47 65"],
["19 01 23 75 03 34"],
["88 02 77 73 07 63 67"],
["99 65 04 28 06 16 70 92"],
["41 41 26 56 83 40 80 70 33"],
["41 48 72 33 47 32 37 16 94 29"],
["53 71 44 65 25 43 91 52 97 51 14"],
["70 11 33 28 77 73 17 78 39 68 17 57"],
["91 71 52 38 17 14 91 43 58 50 27 29 48"],
["63 66 04 68 89 53 67 30 73 16 69 87 40 31"],
["04 62 98 27 23 09 70 98 73 93 38 53 60 04 23"]]

g_tot = 0
g_mx = 0

def create_mat ( lstr ):
    mat = []
    for  r in lstr:
        row = []
        sr = r[0].split(' ')
        for e in sr:
            row.append(int(e))
        mat.append(row)
    return mat

def check_mx ( mat, row, col, sm, mx ):
    global g_tot
    global g_mx
    g_tot = g_tot+1
    sm += mat[row][col] 
    mx = max(sm,mx)
    g_mx = max(sm,g_mx)
    rlen = len(mat)
    clen = len(mat[row])
    if row < (rlen-1):
        mx = check_mx(mat,row+1,col,sm,mx)
        if col < (clen):
            mx = check_mx(mat,row+1,col+1,sm,mx)
    return mx

def mx_sum ( lstr ):
    global g_tot
    global g_mx
    mat = create_mat(lstr)
    mx = 0
    mx = check_mx ( mat, 0, 0, 0, mx )
    print("Max        = %d" % mx)
    print("Global Max = %d" % g_mx)
    print("Paths      = %d" % g_tot);

if __name__=='__main__':
    #mx_sum(test_str)
    mx_sum(main_str)







