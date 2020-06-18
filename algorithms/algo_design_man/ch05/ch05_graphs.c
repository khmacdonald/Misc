#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_statements.h" /* Formatted print wrappers */
#include "queue.h"

#include "ch05_graphs.h"

int dbg_count;

static bool processed[MAXV+1];      /* Which vertices have been processed */
static bool discovered[MAXV+1];     /* Which vertices have been found */
static int parent[MAXV+1];          /* Discovered relation */
static color_t ncolor[MAXV+1];      /* The color of each node */

static int entry_time[MAXV+1];      /* The color of each node */
static int exit_time[MAXV+1];       /* The color of each node */
static int time = 0;

static bool bipartite = FALSE;      /* Is graph bipartite */
static bool finished = FALSE;

static int reachable_ancestor[MAXV+1];  /* Earliest reachable ancestor of v */
static int tree_out_degree[MAXV+1];     /* DFS tree outdegree of v */

/* ------------------------------------------------------------------------ */
/*                           STATIC FUNCTIONS                               */
/* ------------------------------------------------------------------------ */
#define MAX_GF_LINE 1024
static char * get_line ( FILE * fd ) {
    char * nline = calloc(1,MAX_GF_LINE+1);
    int nidx = 0;
    char c;

    if ( NULL==nline ) {
        return NULL;
    }

    while ( nidx<MAX_GF_LINE ) {
        c = fgetc(fd);
        if ( '\n'==c || feof(fd) ) {
            break;
        }
        nline[nidx++] = c;
    }
    return nline;
}

static int get_edge ( int * x, int * y, char * line ) {
    char * xx = line;
    char * yy = xx;
    int k, slen = strlen(line);

    for ( k=0; k<slen-1; ++k ) {
        if ( ' '==line[k] ) {
            line[k] = '\0';
            yy = line + k + 1;
            break;
        }
    }
    if ( xx==yy ) {
        printf("    Here\n");
        return 1;
    }
    *x = atoi(xx);
    *y = atoi(yy);

    return 0;
}

#define CHECK_NLINE(NL)   if ( NULL==NL ) { printf("[%d] ",__LINE__); \
        printf("Error: Missing valid lines in the graph file\n"); \
        printf("    Exiting ...\n"); \
        exit(0); \
    }

static int read_graph_file_internal ( graph * g, FILE * fd ) {
    char * nline = NULL;
    int x, y, k, nedges;

    do { /* Skip commented lines */
        if ( nline ) {
            free(nline);
        }
        nline = get_line(fd);
    } while ( nline && nline[0]=='#' );
    CHECK_NLINE(nline);

    /* The next two lines define nvertices and nedges */
    g->nvertices = atoi(nline);  /* nvertices line */
    free(nline);

    nline = get_line(fd);
    CHECK_NLINE(nline);
    nedges = atoi(nline);       /* nedges line */
    free(nline);

    for ( k=0; k<nedges; k++ ) {    /* Process all edge lines */
        nline = get_line(fd);
        CHECK_NLINE(nline);
        if ( get_edge(&x,&y,nline) ) {
            err_print("get_edge, for edge %d '%s', failed\n    Exiting....\n",
                      k,nline);
            exit(1);
        }
        insert_edge(g,x,y,g->directed);
        free(nline);
    }

    return 0;
}

static color_t complement ( color_t c ) {
    if ( WHITE==c ) {
        return BLACK;
    } else if ( BLACK==c ) {
        return WHITE;
    }

    return UNCOLORED;
}

static edge_t edge_classification ( graph * g, int v, int y ) {
    if ( parent[y] == v ) { 
        return (TREE);
    }
    if ( discovered[y] && !processed[y] ) {
        return (BACK);
    }
    if ( processed[y] && (entry_time[y] > entry_time[v]) ) {
        return FORWARD;
    }
    if ( processed[y] && (entry_time[y] < entry_time[v]) ) {
        return CROSS;
    }

    err_print("self_loop (%d,%d)\n",v,y);
    
    return INVALID;
}

/* ------------------------------------------------------------------------ */


void initialize_graph ( graph * g, bool directed ) {
    int i;          /* counter */

    g->nvertices = 0;
    g->nedges     = 0;
    g->directed   = directed;

    for ( i=1; i<MAXV; ++i ) {
        g->degree[i] = 0;
    }

    for ( i=1; i<MAXV; ++i ) {
        g->edges[i] = 0;
    }
}

void insert_edge ( graph * g, int x, int y, bool directed ) {
    edgenode * p;           /* temporary pointer */

    p = malloc(sizeof(*p)); /* allocate edgenode storage */

    //p->weight = NULL; /* In book like this */
    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;        /* insert at head of list */

    if ( directed==FALSE ) {
        insert_edge(g,y,x,TRUE);
    } else {
        g->nedges++;
    }
}

void read_graph_interactive ( graph * g, bool directed ) {
    int i;      /* counter */
    int m;      /* number of edges */
    int x, y;   /* verticies in edge (x,y) */

    initialize_graph(g,directed);

    printf("How many verticies: ");
    scanf("%d",&(g->nvertices));
    printf("How many edges: ");
    scanf("%d",&m);

    printf("For each edge type two space separated numbers to represent\n");
    printf("an edge.  For example, if an edge goes from node 0 to node\n");
    printf("1, type '0 1'\n");
    for ( i=1; i<=m; ++i ) {
        printf("    Next edge: ");
        scanf("%d %d",&x,&y);
        insert_edge(g,x,y,directed);
    }
}

int read_graph_file ( graph * g, char * fname, bool directed ) {
    FILE * fd = NULL;
    int ret = 0;
    char * nline = NULL;

    if ( !(g && fname) ) {
        printf("Error: Invalid parameters pointers: g = %p and fname = %p\n",g,fname);
        return 1;
    }
    fd = fopen(fname,"r");
    if ( !fd ) {
        printf("Error: Could not open graph file '%s'\n",fname);
        return 1;
    }

    initialize_graph(g,TRUE);
    ret = read_graph_file_internal(g,fd);

    fclose(fd);
    fd = NULL;
    return 0;
}

void print_graph ( graph * g ) {
    int k;          /* counter */
    edgenode * p;   /* temporary pointer */

    printf("    Graph ( nodes: edge list )\n");
    for ( k=1; k<=g->nvertices; ++k ) {
        printf("%d: ",k);
        p = g->edges[k];
        while ( p ) {
            printf(" %d",p->y);
            p = p->next;
        }
        printf("\n");
    }
}

void process_vertex_early ( int v ) {
    /* Breadth first search */
    //printf("%s: %d\n",__FUNCTION__,v);
    //printf(" %d",v);
}
void process_vertex_early_dfs ( int v ) {
    reachable_ancestor[v] = v;
}

typedef void (*pv_late_t)(int);
void process_vertex_late_void ( int v ) {
    //printf("%s: %d\n",__FUNCTION__,v);
}

void process_vertex_late_dfs ( int v ) {
    bool root;      /* is the vertex the root of the DFS tree? */
    int time_v;     /* earliest reachable time for v */
    int time_parent;/* earliest reachable time for parent[v] */

    if ( parent[v]<1 ) {    /* test if v is the root */
        if ( tree_out_degree[v] > 1 ) {
            printf("root articulation vertex: %d\n",v);
        }
        return;
    }

    root = (parent[parent[v]]<1);   /* test if parent[v] is root */

    if ( !root ) {
        if ( reachable_ancestor[v] == parent[v] ) {
            printf("parent articulartion vertex: %d\n",parent[v]);
        }
        if ( reachable_ancestor[v] == v ) {
            printf("bridge articulation vertex: %d\n",parent[v]);

            if ( tree_out_degree[v] > 0 ) { /* test if v is not a leaf */
                printf("bridge articulation vertex: %d\n",v);
            }
        }
    } /* if ( !root ) */

    time_v = entry_time[reachable_ancestor[v]];
    time_parent = entry_time[reachable_ancestor[parent[v]]];

    if ( time_v < time_parent ) {
        reachable_ancestor[parent[v]] = reachable_ancestor[v];
    }
}

void process_edge_two_color ( int v, int y ) {
    /* For two color functionality */
    if ( ncolor[v] == ncolor[y] ) {
        bipartite = FALSE;
        err_print("Not a bipartite graph due to (%d,%d).\n",v,y);
    }
    ncolor[y] = complement(ncolor[v]);
}
void process_edge_dfs ( graph * g, int v, int y ) {
    /* For depth first search */
    static int cycle_count = 0;

    if ( TRUE==discovered[y] && (parent[v]!=y) ) {
        printf("[%d] Cycle %d from %d to %d: ",__LINE__,++cycle_count,y,v);
        find_path(y,v,parent);
        printf("\n");
        finished = TRUE;
    }
}
void process_edge_dfs_art_vert ( graph * g, int v, int y ) {
    /* For finding articulation vertices */
    edge_t class;      /* edge class */

    class = edge_classification(g,v,y);     /* Get edge classification */

    /*
     * Update reachable_ancestor 
     */
    if ( TREE==class ) {
        tree_out_degree[v]++;
    }
    if ( (BACK==class) && (parent[v]!=y) ) {
        if ( entry_time[y] < entry_time[reachable_ancestor[v]] ) {
            reachable_ancestor[v] = y;
        }
    }

    return;
}
void process_edge ( graph * g, int v, int y ) {
    return;
}


void initialize_search ( graph * g ) {
    int k;      /* counter */

    for ( k=0; k<=g->nvertices; ++k ) {
        processed[k]  = FALSE;
        discovered[k] = FALSE;
        parent[k]     = -1;
    }
    return;
}

int breadth_first_search ( graph * g, int start ) {
    queue q;        /* queue of vertices to visit */
    int v;          /* current vertex */
    int y;          /* successor vertex */
    edgenode * p;   /* temporary pointer */
    pv_late_t process_vertex_late = process_vertex_late_void;

    initialize_search(g);              /* Initialize helper arrays */
    init_queue(&q);                 /* Initialize queue */
    enqueue(&q,start);              /* Push start node onto queue */
    discovered[start] = TRUE;       /* Marke the start node as discovered */

    while ( empty_queue(&q)==FALSE ) {
        dequeue(&v,&q);                 /* Get next node */
        process_vertex_early(v);
        processed[v] = TRUE;            /* Mark node processed*/
        p = g->edges[v];                /* Get list of edges from v */

        while ( p ) {                   /* Process each node connected to v */
            y = p->y;                   
            if ( (FALSE==processed[y]) || g->directed ) {
                process_edge(g,v,y);      
            }
            if ( FALSE==discovered[y] ) {
                enqueue(&q,y);          /* If not discovered push onto queue */
                discovered[y] = TRUE;   /* Mark as disovered */
                parent[y] = v;          /* Mark as child of v */
            }
            p = p->next;                /* Get next edge */
        }

        process_vertex_late(v);
    }

    return 0;
}

void connected_components ( graph * g ) {
    int c;      /* component number */
    int k;      /* counter */

    initialize_search(g);

    c = 0;
    /* 
     * Prints out the partitions to the graph.  If everthing is
     * connected, only one component will be printed out.
     */

    for ( k=1; k<=g->nvertices; ++k ) {
        if ( FALSE==discovered[k] ) { /* If not visited, search graph */
            c++;
            printf("Component %d: ",c);
            /* New undiscovered node.  Search for all components. */
            breadth_first_search(g,k); 
            printf("\n");
        }
    }
}

void find_path ( int start, int end, int parents[] ) {
    if ( 0==end ) {
        printf("\n");
        err_print("Invalid: start = %d, end = %d\n    Exiting....\n",start,end);
        exit(1);
    }
    if ( (start==end) || (-1==end) ) {
        printf("%d",start);
    } else {
        //printf("\n");
        find_path(start,parent[end],parents);
        printf(" %d",end);
    }
}

void print_parents ( int lnum, int n ) {
    int k;

    printf("[%d] parents:",lnum);
    for ( k=0; k<=n; ++k ) {
        //printf("%d has parent %d\n",k,parent[k]);
        printf(" (%d,%d)",k,parent[k]);
    }
    printf("\n");
}

void two_color ( graph * g ) {
    int k;      /* counter */

    for ( k=1; k<=g->nvertices; ++k ) {
        ncolor[k] = UNCOLORED;
    }

    bipartite = TRUE;
    initialize_search(g);

    for ( k=1; k<g->nvertices; ++k ) {
        if ( FALSE==discovered[k] ) {
            ncolor[k] = WHITE;
            breadth_first_search(g,k);
        }
    }

    return;
}

/* Depth first functions */
int depth_first_search ( graph * g, int v ) {
    edgenode * p;       /* tmp pointer */
    int y;              /* successor node */
    pv_late_t process_vertex_late = process_vertex_late_dfs;

    if (finished) {
        return 0;         /* allow for search termination */
    }

    discovered[v] = TRUE;       /* Mark node as discovered */
    time = time+1;              /* Increment time */
    entry_time[v] = time;       /* Note entry time */

    process_vertex_early_dfs(v);    /* Process node */

    for ( p=g->edges[v]; p; p=p->next ) {
        y = p->y;                       /* Get node */
        if ( FALSE==discovered[y] ) {   /* Undiscovered node */
            parent[y] = v;              /* Save parent of node */
            //process_edge_dfs(g,v,y);          /* Process edge */
            process_edge_dfs_art_vert(g,v,y);
            depth_first_search(g,y);    /* Recursion */
        } else if ( (!processed[y] && (parent[v]!=y)) || (g->directed) ) {
            //process_edge_dfs(g,v,y);
            process_edge_dfs_art_vert(g,v,y);
        }

        if ( finished ) {
            return 0;
        }
    }

    process_vertex_late(v);

    time = time+1;          /* Increment time */
    exit_time[v] = time;    /* Note exit time */
    
    processed[v] = TRUE;    /* Mark node processed */

    return 0;
}















/* ------------------------------------------------------------ */

/* Unit tests */
void unit_test_initialize_graph ( int argc, char ** argv ) {
    graph G;

    printf("\n***Running test %s:\n",__FUNCTION__);
    initialize_graph(&G,TRUE);
    initialize_graph(&G,FALSE);
    printf("    %s: Success!\n\n",__FUNCTION__);
}

void unit_test_insert_edge ( int argc, char ** argv ) {
    graph G;


    printf("\n***Running test %s:\n",__FUNCTION__);
    initialize_graph(&G,TRUE);
    insert_edge(&G,2,3,TRUE);
    printf("    %s: Success!\n\n",__FUNCTION__);
}

void unit_test_print_graph ( int argc, char ** argv ) {
    graph G;

    printf("\n***Running test %s:\n",__FUNCTION__);
    initialize_graph(&G,TRUE);
    G.nvertices = 6;
    insert_edge(&G,0,3,TRUE);
    insert_edge(&G,1,3,TRUE);
    insert_edge(&G,1,2,TRUE);
    insert_edge(&G,2,3,TRUE);
    insert_edge(&G,3,5,TRUE);
    insert_edge(&G,3,3,TRUE);
    insert_edge(&G,3,0,TRUE);
    insert_edge(&G,4,3,TRUE);
    insert_edge(&G,5,3,TRUE);
    print_graph(&G);
    printf("    %s: Success!\n\n",__FUNCTION__);
}

void unit_test_read_graph_interactive ( int argc, char ** argv ) {
    graph G;

    printf("\n***Running test %s:\n",__FUNCTION__);
    read_graph_interactive(&G,TRUE);
    print_graph(&G);
    printf("    %s: Success!\n\n",__FUNCTION__);
}

void unit_test_read_graph_file ( int argc, char ** argv ) {
    graph G;

    printf("\n***Running test %s:\n",__FUNCTION__);
    read_graph_file(&G,"ch05_graphs_sample_input.txt",TRUE);
    print_graph(&G);
    printf("    %s: Success!\n\n",__FUNCTION__);
}

void unit_test_find_path ( int argc, char ** argv ) {
    char * fname = "ch05_graphs_sample_input.txt";
    graph G;

    read_graph_file(&G,fname,TRUE);
    print_graph(&G);
    breadth_first_search(&G,1);
    printf("Path for 1 -> 4: ");
    find_path(1,4,parent);
    printf("\n");
}

void unit_test_connected_components ( int argc, char ** argv ) {
    char * fname = "ch05_graphs_sample_input.txt";
    graph G;

    read_graph_file(&G,fname,TRUE);
    print_graph(&G);
    connected_components(&G);
    printf("\n");
}

void unit_test_find_cycles ( int argc, char ** argv ) {
    char * fname = "ch05_graphs_sample_input.txt";
    graph G;
    int k;

    read_graph_file(&G,fname,TRUE);
    printf("\n------------------------------------------------------------\n\n");
    print_graph(&G);
    printf("\n------------------------------------------------------------\n\n");
    initialize_search(&G);
    for ( k=1; k<=G.nvertices; ++k ) {
        if ( FALSE==discovered[k] ) {
            depth_first_search(&G,k);
            finished = FALSE; /* Find next cycle */
        }
    }
    printf("\n------------------------------------------------------------\n");
    printf("\n");
}

const g_unit_test_t g_all_unit_tests[] = {
    unit_test_initialize_graph,
    unit_test_insert_edge,
    unit_test_print_graph,
    unit_test_read_graph_interactive,
    unit_test_read_graph_file,
    unit_test_find_path,
    unit_test_connected_components,
    unit_test_find_cycles
};

void g_run_all_unit_tests ( int argc, char ** argv ) {
    int k;
    char * test_delimit = "--------------------------------------------";

    printf("\n%s\n",test_delimit);
    printf("--- Running All Unit Tests for Chapter 5 --- \n");
    printf("%s\n",test_delimit);
    for ( k=0; k<G_ALL_UNIT_TESTS; ++k ) {
        g_all_unit_tests[k](argc,argv);
        printf("%s\n",test_delimit);
    }
    printf("---    Testing Complete for Chapter 5    --- \n");
    printf("%s\n\n",test_delimit);
}























