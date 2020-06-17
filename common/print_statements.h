#ifndef PRINT_STATEMENTS_H
#define PRINT_STATEMENTS_H

/*
 * Define a series of standard formatted print statements.
 */

#define base_print(F,L,...) \
    do { \
        fprintf( F, "%s - [%s,%s,%d]: ",L,__FILE__,__FUNCTION__,__LINE__); \
        fprintf( F, __VA_ARGS__ ); \
    } while ( 0 )

#define info_print(...) base_print(stdout,"Info",__VA_ARGS__)
#define err_print(...)  base_print(stdout,"Error",__VA_ARGS__)
#define wrn_print(...)  base_print(stdout,"Warning",__VA_ARGS__)
#define dbg_print(...)  base_print(stdout,"Debug",__VA_ARGS__)

#define base_info_log(L,...) base_print(L,"Info",__VA_ARGS__)
#define base_err_log(L,...)  base_print(L,"Error",__VA_ARGS__)
#define base_wrn_log(L,...)  base_print(L,"Warning",__VA_ARGS__)
#define base_dbg_log(L,...)  base_print(L,"Debug",__VA_ARGS__)

/* If C is non-zero, print the statement */
#define dbg_cond_print(C,...) if ( C ) { dbg_print(__VA_ARGS__); }

/* Debug print statement, then exit with value N */
#define dbg_print_exit(N,...) \
    do { \
        dbg_print(__VA_ARGS__); \
        printf("\n    Exiting...\n");\
        exit(N); \
    } while(0)

/* Error print statement, then exit with value N */
#define err_print_exit(N,...) \
    do { \
        err_print(__VA_ARGS__); \
        printf("\n    Exiting...\n");\
        exit(N); \
    } while(0)

#endif
