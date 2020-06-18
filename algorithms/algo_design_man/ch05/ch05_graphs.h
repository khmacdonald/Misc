#ifndef CH5_GRAPHS_H
#define CH5_GRAPHS_H

#include "algos_common.h"

#define MAXV        1000        /* Max number of veticies */

typedef enum { UNCOLORED, WHITE, BLACK, RED, YELLOW, BLUE, LAST_COLOR } color_t;
typedef enum { TREE=0, BACK, CROSS, FORWARD, INVALID } edge_t;

struct _edgenode { 
    int y;                      /* Adjacency info */
    int weight;                 /* Edge weight , if any */
    struct _edgenode * next;    /* next edge in list */
};
typedef struct _edgenode edgenode;

struct _graph { 
    edgenode *edges[MAXV+1];        /* Adjacency info */
    int degree[MAXV+1];             /* Out degree of vertex */
    int nvertices;                  /* Number of vertices in graph */
    int nedges;                     /* Number of edges in graph */
    bool directed;                  /* Is the graph directed */
};
typedef struct _graph graph;

/*
 * Initializes a graph data structure zeroing out all information and
 * defining if the graph is directed or not.
 */
void initialize_graph ( graph * g, bool directed ) ;

/*
 * Inserts an edge into the graph.
 */
void insert_edge ( graph * g, int x, int y, bool directed ) ;

/*
 * Prints out each node, in order, and all the edges for  each node.
 */
void print_graph ( graph * g ) ;

/*
 * Reads a graph interactively with command line prompt.
 */
void read_graph_interactive ( graph * g, bool directed ) ;

/*
 * Reads a graph from a formatted file.
 */
int read_graph_file ( graph * g, char * fname, bool directed ) ;

void initialize_search ( graph * g ) ;

/* Bread first functions */
void initialize_bfs ( graph * g ) ;
int breadth_first_search ( graph * g, int start ) ;
void connected_components ( graph * g ) ;
void find_path ( int start, int end, int parents[] ) ;
void print_parents ( int lnum, int n ) ;
void two_color ( graph * g ) ;

/* Depth first functions */
int depth_first_search ( graph * g, int start ) ;

/* unit tests */
void unit_test_initialize_graph ( int argc, char ** argv ) ;
void unit_test_insert_edge ( int argc, char ** argv ) ;
void unit_test_print_graph ( int argc, char ** argv ) ;
void unit_test_read_graph_interactive ( int argc, char ** argv ) ;
void unit_test_read_graph_file ( int argc, char ** argv ) ;

void unit_test_find_path ( int argc, char ** argv ) ;
void unit_test_connected_componentes ( int argc, char ** argv ) ;

void unit_test_find_cycles ( int argc, char ** argv ) ;

typedef void (*g_unit_test_t)(int,char**);
extern const g_unit_test_t g_all_unit_tests[];
void g_run_all_unit_tests ( int argc, char ** argv ) ;

#define G_ALL_UNIT_TESTS (sizeof(g_all_unit_tests)/sizeof(g_all_unit_tests[0]))

#endif
