#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

'''
https://www.hackerrank.com/challenges/ctci-ransom-note/problem
'''

def get_input ( ) :
    lengths = input()
    magazine = input()
    note = input()
    return lengths, magazine, note

def split_inputs ( lengths, magazine, note ) :
    l = lengths.split(' ')
    m = int(l[0])
    n = int(l[1])
    mwords = magazine.rstrip().split(' ')
    nwords = note.rstrip().split(' ')
    return mwords, nwords

def checkMagazine01 ( magazine, note ) :
    for word in note:
        if word not in magazine:
            print("No")
            return
        else:
            magazine.pop(magazine.index(word))
    print("Yes")
    return


def checkMagazine ( magazine, note ) :
    mag_dic = {}
    for word in magazine:
        if word in mag_dic:
            mag_dic[word] += 1
        else:
            mag_dic[word] = 1

    for word in note:
        if word not in mag_dic:
            print("No")
            return
        else:
            if mag_dic[word]==0:
                print("No")
                return
            else:
                mag_dic[word] -= 1
    print("Yes")
    return

def test1 ( ) :
    line1 = "6 4"
    line2 = "give me one grand today night"
    line3 = "give one grand today"
    return line1, line2, line3

def test2 ( ) :
    line1 = "6 5"
    line2 = "two times three is not four"
    line3 = "two times two is four"
    return line1, line2, line3

def test3 ( ) :
    line1 = "7 4"
    line2 = "ive got a lovely bunch of coconuts"
    line3 = "ive got some coconuts"
    return line1, line2, line3



if __name__=='__main__':
    '''
    line1, line2, line3 = test1()
    magazine, note = split_inputs(line1, line2, line3)
    checkMagazine(magazine,note)
    '''
    line1, line2, line3 = test1()
    magazine, note = split_inputs(line1, line2, line3)
    checkMagazine(magazine,note)

    line1, line2, line3 = test2()
    magazine, note = split_inputs(line1, line2, line3)
    checkMagazine(magazine,note)

    line1, line2, line3 = test3()
    magazine, note = split_inputs(line1, line2, line3)
    checkMagazine(magazine,note)

