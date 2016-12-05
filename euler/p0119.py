#!/usr/local/bin/python

import bisect
import decimal
import math
import sys

sys.path.append("/Users/khmacdonald/code/SVN/trunk/euler/utilities/")
from primes import sieve
import my_euler

av = sys.argv
ac = len(av)


def print_project_answer( pnum, answer ):
    project_output = "Project Euler %d answer is" % pnum
    print("")
    print("%s = %d" % (project_output,answer))

def proc_pline ( line ):
    line = line.strip()
    l = []
    for c in line:
        l.append(int(c))
    return l

def get_next_puzzle ( fd ):
    line = fd.readline()
    puzzle = None
    if line and "Grid" in line:
        puzzle = []
        for k in range(9):
            line = fd.readline()
            l = proc_pline(line)
            puzzle.append(l)
    return puzzle

def solve_puzzle ( p ):
    pass

def proj():
    pnum = 96
    answer = 0
    fname = "p096_sudoku.txt"
    fd = open(fname,"r")

    cnt = 0
    p = get_next_puzzle(fd)
    while p:
        cnt = cnt+1
        p = get_next_puzzle(fd)
    print("There are %d puzzles" % cnt)

    fd.close()
    print("")
    print_project_answer(pnum,answer)
    return

def test():
    pass

if __name__=='__main__':
    #test()
    proj()

