#include "basic_matrix.h"
#include <time.h>
#include <string.h>

#define N_CASES 4000000
#define M_SIZE 5
static const float test_data[M_SIZE][M_SIZE] = {
    {2,  4,  6,  2,  1},
    {4,  9, 14,  8,  8},
    {2,  6, 12, 12, 21},
    {4, 10, 20, 17, 32},
    {8, 17, 30, 18, 34}
    };

// test the performance of the algorithms
void profile() {
    BasicMatrix vector;
    clock_t start_t, end_t;

    start_t = clock();
    for (int i=0; i<N_CASES; i++) {
        vector.x = M_SIZE;
        vector.y = M_SIZE;
        memcpy(vector.data, test_data, sizeof (float) * M_SIZE * M_SIZE);
        LU_dolittle(&vector);
    }
    end_t = clock();
    printf("Dolittle elapsed time %2.5fs\n", ((double)end_t - (double)start_t) / CLOCKS_PER_SEC);

    start_t = clock();
    for (int i=0; i<N_CASES; i++) {
        vector.x = M_SIZE;
        vector.y = M_SIZE;
        memcpy(vector.data, test_data, sizeof (float) * M_SIZE * M_SIZE);
        LU_gaussian(&vector);
    }
    end_t = clock();
    printf("Gaussian elapsed time %2.5fs\n", ((double)end_t - (double)start_t) / CLOCKS_PER_SEC);    
}

int main() {
    BasicMatrix A1 = {
        {{2, 1, 2, 1}, {1, 1.5, 3, 2.5}, {-4, 0, 2, 6}, {1, 2.5, 9, 13.5}},
        4,
        4
    };
    BasicMatrix A2 = {
        {{2, 1, 2, 1}, {1, 1.5, 3, 2.5}, {-4, 0, 2, 6}, {1, 2.5, 9, 13.5}},
        4,
        4
    };   
  
    printf("\nDolittle algorithm:\nInput A=");
    display_matrix(&A1);
    LU_dolittle(&A1);
    validate_LU(&A1);    
    

    printf("\nGaussian algorithm:\nInput A=\n");
    display_matrix(&A2);
    LU_gaussian(&A2);
    validate_LU(&A2);    

    profile();
}

