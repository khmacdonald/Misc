#!/usr/bin/python3

iname1 = "climb_the_leaderboard_test08.txt"
iname2 = "climb_the_leaderboard_test08_expected.txt"

oname = "climb_the_leaderboard_test08.c"

def get_oline ( sl ) :
    oline = ''
    for k in range(len(sl)) :
        if 0==(k%8) :
            oline += "\n    "
        oline += f"{sl[k]:>8}, "
    oline += "\n};\n\n"
    return oline

with open(oname,"w") as ofd :

    with open(iname1,"r") as fd :
        lines1 = fd.readlines()

    scnt = lines1[0].strip()
    sl1 = lines1[1].strip().split(' ')
    ofd.write(f"const int scnt = {scnt};\n")
    ofd.write("int scores[scnt] = {")
    oline = get_oline(sl1)
    ofd.write(oline)

    scnt = lines1[2].strip()
    sl1 = lines1[3].strip().split(' ')
    ofd.write(f"const int acnt = {scnt};\n")
    ofd.write("int alice[acnt] = {")
    oline = get_oline(sl1)
    ofd.write(oline)

    
    with open(iname2,"r") as fd :
        expected = fd.readlines()
    ofd.write("int expected[acnt] = {")
    for k in range(len(expected)) :
        if 0==(k%8) :
            ofd.write("\n    ")
        ex = expected[k].strip()
        ofd.write(f"{ex:>8}, ")
    ofd.write("\n};\n\n")



