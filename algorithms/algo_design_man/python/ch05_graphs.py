#!/usr/local/bin/python3

# This file defines edges and graphs.  If invoked as a script
# this file performs a basic task using breadth.  Specifically,
# given a file that defines a graph, it lists all the nodes that
# can be travelled to first from node 1, then from node 6

import queue
import sys

class Edge ( object ) :
    ''' Defines linked list of edges '''

    def __init__ ( self, node ) :
        self.node = node    # Connected node in edge
        self.next = None    # Initialized as not linked to anything

class Graph ( object ) :
    ''' Defines a graph '''

    def __init__ ( self, max_nodes=100 ) :
        ''' Initialize graph with a certain number of nodes '''
        self.max_nodes = max_nodes+1                # Max number of nodes
        self.nvertices = 0                          # No defined vertices yet
        self.nedges = 0                             # No defined edges yet
        self.edges = [ None ] * self.max_nodes      # Edges for each node

    def __init_search ( self ) :
        ''' Initializes internal buffers to do searches '''
        self.processed  = [False] * (self.nvertices+1)
        self.discovered = [False] * (self.nvertices+1)

    def __get_lines_of_graph_file ( self, fname ) :
        ''' Reads in the lines of the graph file, ignoring comments '''
        fd = open(fname,"r")
        flines = fd.readlines()
        fd.close()

        # Skip commented lines
        for k in range(len(flines)) :
            if '#'!=flines[k][0] : 
                break

        # Compute the number of vertices defined in graph
        nvertices = int(flines[k].strip())

        return nvertices, flines[k+1:]

    def read_graph_file ( self, fname ) :
        ''' Read a graph from a file '''
        print(f"Reading graph from file {fname}")
        nvertices, edge_lines = self.__get_lines_of_graph_file(fname) 

        # If necessary readjust
        if nvertices > self.max_nodes:
            self.max_nodes = nvertices+1
            self.edges = [ None ] * self.max_nodes  
            self.nvertices = nvertices

        self.nvertices = nvertices
        self.__init_search()

        # The remaining lines are 'n m' where n connects to m.
        # Edges are directed, i.e. n -> m
        for el in edge_lines :
            el = el.strip()
            sel = el.split(' ')
            if len(sel)==2:             # Sanity check
                n = int(sel[0])
                m = int(sel[1])
                new_edge = Edge(m)      # Create new edge
                self.nedges += 1

                # Push new edge onto linked list of edges for node n
                if self.edges[n] : 
                    new_edge.next = self.edges[n] 
                self.edges[n] = new_edge 

    def print_graph ( self ) :
        ''' Prints out a graph, showing each edge per node '''
        for k in range(1,self.nvertices+1) :
            node_str = f"Node {k} : "       # print node
            e = self.edges[k]
            while e:
                node_str += f" {e.node}"    # print each edge 
                e = e.next
            print(node_str)

    def breadth_first_search ( self, start ) :
        ''' Computes a breadth first search '''

        # Initialization sequence
        self.__init_search()            # Internal search buffers
        q = queue.Queue()               # Queue of nodes visited
        q.put(start)                    # Save start node
        self.discovered[start] = True   # Start node is discovered

        while not q.empty() :           # More nodes to process
            v = q.get()                 # Get next node 
            self.processed[v] = True    # Mark as discovered
            e = self.edges[v]           # List of edges to node v

            # Process each node connected to v
            while e :                           
                n = e.node                      # Next connected node
                if not self.discovered[n] :     # Do nothing if already discovered
                    q.put(n)                    # Push onto queue
                    self.discovered[n] = True   # Mark new node as discovered
                e = e.next                      # Get next edge

    def connected_component ( self, node ) :
        '''
        Use breadth first search to find all nodes that can be
        travelled to starting at node 'node'. 
        '''
        self.breadth_first_search(node)     

        # Nodes that can be travelled to starting at
        # 'node' will be marked as discovered.
        con = ''
        for k in range(1,self.nvertices+1) :
            if self.discovered[k] : 
                con += f" {k}" # The connected nodes are all discovered
        print(f"Components {node} connects to = ({con} )")


def test_graph_read () :
    ''' Testing function '''
    fname = "ch05_graphs_sample_input.txt"

    G = Graph()                 # Create a graph object
    G.read_graph_file(fname)    # Read in graph from file
    print("    Graph")
    G.print_graph()             # Pretty print graph
    print(" ------------------------------- ")
    print("    Find components: ")  
    G.connected_component(1)        # Find nodes that node 1 connects to
    G.connected_component(6)        # Find nodes that node 6 connects to
    print("\n\n")

if __name__=="__main__":
    test_graph_read ()


