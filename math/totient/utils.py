#!/usr/local/bin/python

fname = "tmp.c"

fd = open(fname,"w")

sqsz = 65536
define = "#define SQUARE_SZ %d" % sqsz
array = "uint32_t square_int[SQUARE_SZ] ="

fd.write("%s\n%s\n{\n    " % (define,array))
for k in range(sqsz-1):
    sq = k*k
    fd.write("%10d, " % sq)
    if 0==((k+1)%8):
        fd.write("\n    ")

sq = (sqsz-1)**2
fd.write("%d\n};" % sq)

fd.close()

