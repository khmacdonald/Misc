#!/usr/local/bin/python

import bisect
import sys

av = sys.argv
ac = len(av)

def get_list():
    pr_list = []
    fname = "pandig_prime.txt"
    fd = open(fname,"r")
    count = 0
    tcnt = 0
    tot_list = []
    for line in fd.readlines():
        count = count + 1
        if 100000 == count:
            count = 0
            tcnt = tcnt + 1
            print("tcnt = %d" % tcnt)
            tot_list.append(pr_list)
            pr_list = []
        sys.stdout.write("%d\r" % count)
        if "INFO" in line:
            continue
        line = line.strip()
        n = int(line)
        if n not in pr_list:
            bisect.insort_left(pr_list,n)
    fd.close()
    return tot_list

def main ():
    pr_list = get_list()
    fname = "pandig_prime_dedupe.txt"
    fd = open(fname,"w")
    for n in pr_list:
        fd.write("%d\n" % n)
    fd.close()

def main_02 ( ):
    tlist = get_list()
    main_list = []
    cnt = 0
    for plist in tlist:
        cnt = cnt + 1
        print("pcnt = %d" % cnt)
        for x in plist:
            if x not in main_list:
                bisect.insort_left(main_list,x)
    fname = "pandig_prime_dedupe.txt"
    fd = open(fname,"w")
    print("Writing to %s" % fname )
    for x in main_list:
        fd.write("%d\n" % x)
    fd.close()

if __name__=='__main__':
    main_02()

