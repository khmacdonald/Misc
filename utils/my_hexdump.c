#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define destroy_opt(O) do { \
    if ( O ) { \
        if ( O->fd ) { \
            fclose(O->fd); \
        } \
        memset(O,0,sizeof(struct opt)); \
        free(O); \
        O = NULL; \
    } \
} while(0)

struct opt {
    char * fname;
    FILE * fd;
    unsigned int loc;
    unsigned char u[16];
    int rd;
};

struct opt * get_opt ( int argc, char ** argv ) {
    struct opt * opt = calloc(1,sizeof(*opt));

    if ( NULL==opt ) {
        return NULL;
    }
    opt->fd = fopen(argv[1],"r");
    opt->fname = argv[1];
    opt->loc = 0;
    memset(opt->u,0,16);

    return opt;
}

void print_bytes ( struct opt * opt ) {
    int k;
    for ( k=0; k<16; ++k ) {
        printf("%02x ",opt->u[k]);
        if ( 7==k ) {
            printf("  ");
        }
    }
}

void print_characters ( struct opt * opt ) {
    int k;
    printf(" | ");
    for ( k=0; k<16; ++k ) {
        if ( isprint(opt->u[k]) ) {
            printf("%c",opt->u[k]);
        } else {
            printf(".");
        }
    }
    printf(" |");
}

void print_line ( struct opt * opt ) {
    int k;

    printf("%08x    ",opt->loc);
    print_bytes(opt);
    print_characters(opt);
    printf("\n");
}

void process_opt ( struct opt * opt ) {
    while ( 1 ) {
        memset(opt->u,0,16);
        opt->rd = fread(opt->u,1,16,opt->fd);
        print_line(opt);
        opt->loc += opt->rd;
        if ( 16!=opt->rd || 511<opt->loc ) {
            break;
        }
    }
}

int main ( int argc, char ** argv ) {
    struct opt * opt = NULL;

    if ( 2!=argc ) {
        return 1;
    }

    opt = get_opt(argc,argv);
    process_opt(opt);
    destroy_opt(opt);

    return 0;
}
