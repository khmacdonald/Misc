#!/usr/bin/python3

# --------------------------------------------------
# Different types of graphs

def graph_test_sets ( ) :
    a, b, c, d, e, f, g, h = range(8) 
    # Adjacency is represented by sets
    N = [
        { b, c, d, e, f },  # a
        { c, e },           # b
        { d },              # c 
        { e },              # d
        { f },              # e 
        { c, g, h },        # f
        { f, h },           # g
        { f, g }            # h
    ]
    print(N)

def graph_test_lists ( ) :
    a, b, c, d, e, f, g, h = range(8) 
    # Adjacency is represented by lists
    N = [
        [ b, c, d, e, f ],  # a
        [ c, e ],           # b
        [ d ],              # c 
        [ e ],              # d
        [ f ],              # e 
        [ c, g, h ],        # f
        [ f, h ],           # g
        [ f, g ]            # h
    ]
    print(N)

def graph_test_lists_nested ( ) :
    a, b, c, d, e, f, g, h = range(8) 
    # Adjacency is represented by lists
    N = [
        [ 0, 1, 1, 1, 1, 1, 0, 0], # a
        [ 0, 0, 1, 0, 1, 0, 0, 0], # b
        [ 0, 0, 0, 1, 0, 0, 0, 0], # c
        [ 0, 0, 0, 0, 1, 0, 0, 0], # d
        [ 0, 0, 0, 0, 0, 1, 0, 0], # e
        [ 0, 0, 1, 0, 0, 0, 1, 1], # f
        [ 0, 0, 0, 0, 0, 1, 0, 1], # g
        [ 0, 0, 0, 0, 0, 1, 1, 0], # h
    ]
    print(N)

def graph_test_dics_sets ( ) :
    a, b, c, d, e, f, g, h = range(8) 
    # Adjacency is represented by lists
    N = {
        'a' : set('bcdef'),  # a
        'b' : set('ce'),     # b
        'c' : set('d'),      # c 
        'd' : set('e'),      # d
        'e' : set('f'),      # e 
        'f' : set('cgh'),    # f
        'g' : set('fh'),     # g
        'h' : set('fg')      # h
    }
    print(N)

def graph_test_dics ( ) :
    a, b, c, d, e, f, g, h = range(8) 
    # Adjacency is represented by dictionaries
    # The keys are the edge, which can be associated with some
    # value, like a weight.
    N = [
        { b: 2, c: 1, d: 3, e: 9, f: 4 },   # a
        { c: 4, e: 3 },                     # b
        { d: 8 },                           # c 
        { e: 7 },                           # d
        { f: 5 },                           # e 
        { c: 2, g: 2, h: 2 },               # f
        { f: 1, h: 6 },                     # g
        { f: 9, g: 8 }                      # h
    ]
    print(N)

# --------------------------------------------------
# Linked list

class Node : 
    def __init__ ( self, value, nxt=None ) :
        self.value = value
        self.next  = nxt

def Node_test ( ) :
    L = Node("a", Node("b", Node("c", Node("d"))))
    print(L.next.next.value)

def Node_test01 ( ) :
    L = Node("a", Node("b", Node("c", Node("d"))))
    cnode = L
    while cnode:
        print(cnode.value)
        cnode = cnode.next
    print(L.value)

# --------------------------------------------------
# Trees

class BTree: 
    def __init__ ( self, left, right ) :
        self.left  = left
        self.right = right

def test_btree ( ) :
    t = BTree(BTree("a", "b"), BTree("c", "d"))
    print(t.right.left)

class MTree: 
    def __init__ ( self, kids, nxt=None ) :
        self.kids = self.val = kids
        self.next = nxt

def test_mtree ( ) :
    t = MTree(MTree("a", MTree("b", MTree("c", MTree("d")))))
    print(t)
    print(t.kids.next.next.val)


# --------------------------------------------------
# Bunch Pattern
class Bunch ( dict ) :
    def __init__ ( self, *args, **kwds ) :
        super ( Bunch, self).__init__(*args,**kwds)
        self.__dict__ = self

def test_bunch ( ) :
    x = Bunch(name="Jayne Cobb", position="Public Relations") # Hahahaha!
    print(x.name)

def test_bunch_2 ( ) :
    T = Bunch
    t = T(left=T(left="a", right="b"), right=T(left="c"))
    print(t.left)
    print(t.left.right)
    print(t['left']['right'])
    a = "left" in t.right
    print(a)
    a = "right" in t.right
    print(a)


# --------------------------------------------------

if __name__=='__main__' : 
    test_bunch_2()
