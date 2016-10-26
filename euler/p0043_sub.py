#!/usr/local/bin/python

import bisect
import math
import sys

av = sys.argv
ac = len(av)

g_sum = 0

def check_string ( snum ):
    if 10!=len(snum):
        return False
    pr = [ 2, 3, 5, 7, 11, 13, 17 ]
    idx = 1
    for p in pr:
        x = int(snum[idx:idx+3])
        if 0!=(x%p):
            #print("%d does not divide %d" % (p,x))
            return False
        idx = idx + 1
    return True

def permute ( dig, l, r ):
    if l==r:
        nstr = ''.join(dig)
        if check_string(nstr):
            x = int(nstr)
            global g_sum
            g_sum += x
            print(nstr)
    else:
        for i in range(l,r):
            tmp = dig[l]
            dig[l] = dig[i]
            dig[i] = tmp
            permute(dig,l+1,r);
            tmp = dig[l]
            dig[l] = dig[i]
            dig[i] = tmp

 
def get_pan_nums ( ):
    dig = [ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" ]
    permute(dig,0,10)

def test ( ):
    nstr = "1406357289"
    if check_string(nstr):
        print("%s passes" % nstr);
    else:
        print("%s fails" % nstr);

def main ( ):
    get_pan_nums ( )

if __name__=='__main__':
    main()
    global gsum
    print("Sum = %d" % g_sum)
    #test()


