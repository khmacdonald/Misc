#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "print_statements.h"

#define CLOSE_FILE(F) if ( F ) { fclose(F); (F) = NULL; }
#define MAX_N (1<<20)
#define SET_FREE(X) if ( X ) { free(X); (X) = NULL; }

struct _cmd
{
    int32_t n;
    char * fname;
};

typedef struct _cmd    CMD;
typedef struct _cmd * pCMD;

void compute_primes ( int32_t * numbers, int32_t sz );
pCMD get_cmd ( int32_t argc, char * argv[] );
void output_primes ( int32_t * numbers, pCMD cmd );
void print_options ( pCMD cmd );
void process_cmd ( pCMD cmd );
void usage ( char * name );

/* **************************************************************** */
int32_t main ( int32_t argc, char * argv[] )
{
    pCMD cmd = get_cmd(argc,argv);

    if ( cmd )
    {
        process_cmd(cmd);
    }
    else
    {
        usage(argv[0]);
    }

    return 0;
}
/* **************************************************************** */

void compute_primes ( int32_t * numbers, int32_t sz )
{
    int32_t k,m,idx;

    for ( k=2; k<sz; ++k )
    {
        numbers[k] = 1;
    }
    for ( k=2; k<sz; ++k )
    {
        if ( numbers[k] )
        {
            idx = k+k;
            while ( idx<sz )
            {
                numbers[idx] = 0;
                idx += k;
            }
        }
    }

    return;
}

pCMD get_cmd ( int32_t argc, char * argv[] )
{
    pCMD cmd = NULL;
    char err_parse[] = "Command line option parsing error";

    if ( 3!=argc )
    {
        usage(argv[0]);
        goto END;
    }

    cmd = (pCMD)calloc(1,sizeof(*cmd));
    if ( NULL==cmd )
    {
        err_print("Could not allocate memory for command line options");
        goto END;
    }

    cmd->n = strtol(argv[1],NULL,10);
    cmd->fname = argv[2];

    if ( cmd->n<2 || cmd->n>MAX_N || NULL==cmd->fname )
    {
        err_print("%d,%p",cmd->n,cmd->fname);
        SET_FREE(cmd);
    }
    else
    {
        print_options(cmd);
    }

END:
    return cmd;
}

void output_primes ( int32_t * numbers, pCMD cmd )
{
    FILE * ofd = fopen(cmd->fname,"w");
    int32_t sz = cmd->n,k;

    if ( NULL==ofd )
    {
        err_print("Could not open file %s",cmd->fname);
        goto END;
    }

    fprintf(ofd,"#define PRIME_SIZE %d\n",sz);
    fprintf(ofd,"int32_t prime_array[PRIME_SIZE] = {\n    ");
    for ( k=0; k<sz; ++k )
    {
        fprintf(ofd,"%d, ",numbers[k]);
        if ( 0==((k+1) % 16) )
        {
            fprintf(ofd,"\n    ");
        }
    }
    fprintf(ofd,"\n};\n");

END:
    CLOSE_FILE(ofd);
    return;
}

void print_options ( pCMD cmd )
{
    printf("\n******************************************************************************\n");
    info_print("Output file    = %s",cmd->fname);
    info_print("Largest number = %u",cmd->n);
    printf("******************************************************************************\n\n");
}

void process_cmd ( pCMD cmd )
{
    int32_t * numbers = (int32_t*)calloc(sizeof(*numbers),cmd->n);

    if ( NULL==numbers )
    {
        err_print("Could not allocate numbers array");
        goto END;
    }

    /* Compute primes */
    compute_primes(numbers,cmd->n);

    /* Output primes */
    output_primes(numbers,cmd);

END:
    SET_FREE(numbers);
    return;
}

void usage ( char * name )
{
    printf("\n******************************************************************************\n");
    info_print("Calculates all primes less than a number inputted");
    info_print("Usage: %s <max number> <output file>",name);
    printf("******************************************************************************\n\n");
}









