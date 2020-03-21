#ifndef PRINT_STATEMENTS_H
#define PRINT_STATEMENTS_H

#define base_print(F,L,...) \
    do { \
        fprintf( F, "%s - [%s,%s,%d]: ",L,__FILE__,__FUNCTION__,__LINE__); \
        fprintf( F, __VA_ARGS__ ); \
    } while ( 0 )

#define info_print(...) base_print(stdout,"INFO",__VA_ARGS__)
#define err_print(...)  base_print(stdout,"ERROR",__VA_ARGS__)
#define dbg_print(...)  base_print(stdout,"DEBUG",__VA_ARGS__)

#define base_info_log(L,...) base_print(L,"INFO",__VA_ARGS__)
#define base_err_log(L,...)  base_print(L,"ERROR",__VA_ARGS__)
#define base_dbg_log(L,...)  base_print(L,"ERROR",__VA_ARGS__)

#define dbg_print_exit(N,...) \
    do { \
        dbg_print(__VA_ARGS__); \
        printf("\n    Exiting...\n");\
        exit(N); \
    } while(0)

#endif
