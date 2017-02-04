//
//  pycon_challenge.h
//  CPP_Playground
//

#ifndef pycon_challenge_h
#define pycon_challenge_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int nrows;
    int ncols;
    long int ** data;
} matrix_t;

typedef struct {
    matrix_t m;
    int w_nrows;
    int w_ncols;
    unsigned short int valid;
    long int solution;
} problem_t;

extern problem_t* read_problem_instances(const char* file_name);

extern long int * find_densest(problem_t* problem);

#endif /* pycon_challenge_h */
