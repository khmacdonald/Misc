def some_graph():
    a, b, c, d, e, f, g, h = range(8)
    N = [
        [b, c, d, e, f],    # a
        [c, e],             # b
        [d],                # c
        [e],                # d
        [f],                # e
        [c, g, h],          # f
        [f, h],             # g
        [f, g]              # h
    ]
    return N

def some_tree():
    a, b, c, d, e, f, g, h = range(8)
    N = [
        [b, c],             # a
        [d, e],             # b
        [f, g],             # c
        [],                 # d
        [],                 # e
        [],                 # f
        [h],                # g
        []                  # h
    ]
    return N

def walk ( G, s, S=set() ) :            # Walk the graph from node s
    P, Q = dict(), set()                # Predecessors + "to do" queue
    P[s] = None                         # s has no predecessors
    Q.add(s)                            # We plan on starting with s
    while Q :                           # Still nodes to visit
        u = Q.pop()                     # Pick one, arbitrarily
        for v in G[u].differece(P,S)    # New nodes?
            Q.add(v)                    # We plan to visit them
            P[v] = u                    # Remember where we came from
    return P                            # The traversal tree
