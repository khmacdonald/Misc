#!/usr/local/bin/python

import sys

av = sys.argv
ac = len(av)

def isq ( ):
    if 2!=ac:
        print("USAGE: %s <out file>" % av[0])
        return False
    fd = open(av[1],"w")
    sz = (1<<18) - 1;
    print("%d" % sz)
    fd.write("#define SQUARE_SZ %d\n\n" % sz)
    fd.write("pr_t square_int[SQUARE_SZ] = \n{\n    \n")
    for k in range(sz):
        fd.write("%10d, " % (k*k))
        sys.stdout.write("%d\r" % k)
        if 0==((k+1)%8):
            fd.write("\n    ")
    fd.write("\n};\n")
    fd.close()
    return True

if __name__=='__main__':
    isq()

