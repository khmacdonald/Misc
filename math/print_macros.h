#ifndef PRINT_MACROS_H
#define PRINT_MACROS_H

#define base_print(F,L,...) \
    do { \
        fprintf( F, "%s - [%s,%s,%d]: ",L,__FILE__,__FUNCTION__,__LINE__); \
        fprintf( F, __VA_ARGS__ ); \
        fprintf( F, "\n" ); \
    } while ( 0 )

#define info_print(...) base_print(stdout,"INFO",__VA_ARGS__)
#define error_print(...) base_print(stdout,"ERROR",__VA_ARGS__)

#endif
