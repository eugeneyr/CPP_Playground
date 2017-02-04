#include "pycon_challenge.h"

const int BUFFER_SIZE = 16 * 1024 * 1024;

problem_t * read_problem_instances(const char* file_name) {
    FILE * file = fopen(file_name, "r");
    problem_t* rv = NULL;
    if (NULL != file) {
        char * buffer = calloc(BUFFER_SIZE, 0);
        if (buffer) {
            int no_of_problems = 0;
            fscanf(file, "%d", &no_of_problems);
            if (no_of_problems > 0) {
                rv = calloc(no_of_problems * sizeof(problem_t) + 1, 0);
            }
            for (int i = 0; i < no_of_problems; i++) {
                fscanf(file, "%d", &rv[i].w_nrows);
                fscanf(file, "%d", &rv[i].w_ncols);
                fscanf(file, "%d", &rv[i].m.nrows);
                fscanf(file, "%d", &rv[i].m.ncols);
                if (rv[i].m.nrows > 0 && rv[i].m.ncols > 0) {
                    rv[i].m.data = calloc(rv[i].m.nrows * sizeof(void*), 0);
                }
                for (int j = 0; j < rv[i].m.nrows; j++) {
                    rv[i].m.data[j] = calloc(rv[i].m.ncols * sizeof(long int), 0);
                    for (int k = 0; k < rv[i].m.ncols; k++) {
                        fscanf(file, "%ld", &rv[i].m.data[j][k]);
                    }
                }
            }
            free(buffer);
        }
        fclose(file);
    }
    return rv;
}

long sum(long int arr[], int start, int end) {
    long int tmp = 0;
    for (int i = start; i < end; i++) {
        tmp += arr[i];
    }
    return tmp;
}


long ** alloc_long_array(int rows, int cols) {
    long ** rv = calloc(rows * sizeof(long*), 0);
    for (int i = 0; i < rows; i++) {
        rv[i] = calloc(cols * sizeof(long int), 0);
    }
    return rv;
}

void free_array(void ** arr, int rows) {
    if (arr) {
        for (int i = 0; i < rows; i++) {
            if (arr[i]) {
                free(arr[i]);
                arr[i] = NULL;
            }
        }
        free(arr);
    }
}

long int * find_densest(problem_t* problem) {
    if (!problem) {
        return NULL;
    }
    
    if (!problem->m.data) {
        problem->valid = 0;
        return NULL;
    }
    
    long ** data = problem->m.data;
    
    if (problem->w_nrows <= 0 || problem->w_ncols <= 0) {
        problem->valid = 0;
        return NULL;
    }
    if (problem->m.nrows < problem->w_nrows) {
        problem->valid = 0;
        return NULL;
    }
    if (!data[0]) {
        problem->valid = 0;
        return NULL;
    }
    int rows = problem->m.nrows;
    int cols = problem->m.ncols;
    if (problem->m.ncols < problem->w_ncols) {
        problem->valid = 0;
        return NULL;
    }
    
    int w_nrows = problem->w_nrows;
    
    int w_ncols = problem->w_ncols;
    
    long maxSum = 0;
    
    long int ** rowSums = alloc_long_array(rows, cols - w_ncols + 1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - w_ncols + 1; j++) {
            if (j == 0) {
                rowSums[i][j] = sum(data[i], j, j + w_ncols);
            } else {
                rowSums[i][j] = rowSums[i][j - 1] + data[i][j + w_ncols - 1] - data[i][j - 1];
            }
        }
    }
    for (int j = 0; j < cols - w_ncols + 1; j++) {
        long * sumCol = calloc(sizeof(long int) * (rows - w_nrows + 1), 0);
        for (int i = 0; i < rows - w_nrows + 1; i++) {
            long theSum;
            if (i == 0) {
                long tmpSum = 0;
                for (int i1 = 0; i1 < w_nrows; i1++) {
                    tmpSum += rowSums[i1][j];
                }
                theSum = tmpSum;
            } else {
                theSum = sumCol[i - 1] - rowSums[i - 1][j] + rowSums[i + w_nrows - 1][j];
            }
            if (theSum > maxSum) {
                maxSum = theSum;
            }
            sumCol[i] = theSum;
        }
        free(sumCol);
    }
    free_array((void **) rowSums, rows);
    problem->valid = 1;
    problem->solution = maxSum;
    
    return &problem->solution;
}


void * free_problem_list(problem_t* problems) {
    if (problems) {
        for (problem_t* problem = problems; problem; problem++) {
            free_array((void **) problem->m.data, problem->m.nrows);
        }
        free(problems);
    }
    return NULL;
}

void solve_problems(const char dirName[], int no_of_files) {
    static char format_str[] = "%s/inputs/input%d.txt";
    for (int i = 0; i < no_of_files; i++) {
        char fileName[1024];
        sprintf(fileName, format_str, dirName, i);
        problem_t * problems = read_problem_instances(fileName);
        printf("%s\n", fileName);
        
        for (problem_t* problem = problems; problem; problem++) {
            long int * result = find_densest(problem);
            if (result) {
                printf("%ld\n", *result);
            } else {
                printf("None\n");
            }
        }
        problems = free_problem_list(problems);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s path_to_test_dir {no_of_files}\n", argv[0]);
        return -1;
    }
    
    int no_of_files = 4;
    
    if (argc > 2) {
        no_of_files = atoi(argv[2]);
    }
    
    solve_problems(argv[1], no_of_files);
    
    return 0;
}
