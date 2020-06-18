#ifndef CH5_GRAPHS_H
#define CH5_GRAPHS_H

#include "algos_common.h"

#define MAXV        1000        /* Max number of veticies */

typedef enum { UNCOLORED, WHITE, BLACK, RED, YELLOW, BLUE, LAST_COLOR } color_t;
typedef enum { TREE=0, BACK, CROSS, FORWARD, INVALID } edge_t;

struct _edgenode { 
    int y;                      /* Adjacency info */
    int weight;                 /* Edge weight , if any */
    struct _edgenode * next;    /* Next edge in list */
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

#endif
