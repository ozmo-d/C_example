#include <stdio.h>
#include <stdlib.h>
#define BASE_SIZE 5

typedef struct _matrix{
    float data[BASE_SIZE][BASE_SIZE];
    int x;
    int y;
} BasicMatrix;

void initialize_matrix(BasicMatrix* mat) {
    for (int i=0; i<BASE_SIZE; i++) {
        for(int j=0; j<BASE_SIZE; j++) {
            mat->data[i][j] = 0.0;
        }
    }
}

void display_matrix(BasicMatrix* mat) {
    printf("\n");
    for (int i=0; i<mat->x; i++) {
        for (int j=0; j<mat->y; j++) {
            printf("%.1f  ", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void LU_dolittle(BasicMatrix* A) {
    int N = A->x;
    for (int n=0; n<N; n++) {
        // n == 0 case
        if(n==0) {
            for (int i=1; i<N; i++) {
                A->data[i][0] /= A->data[0][0];
            }
        } else {
        // do a row
            for(int k=n; k<N; k++) {
                for(int m=0; m<(n); m++) {
                    A->data[n][k] -= (A->data[n][m] * A->data[m][k]);
                }
            }
        // do a column
            for(int k=n+1; k<N; k++) {
                for (int m=0; m<(n); m++) {
                    A->data[k][n] -= A->data[k][m]*A->data[m][n];
                }
                A->data[k][n] /= A->data[n][n];
            }
        }
    }
}

void LU_gaussian(BasicMatrix* A) {
    int N = A->x;
    for(int i=0; i< N; i++) {
        // divide the columns by the pivot.
        for(int k=i+1; k<N; k++) {
            A->data[k][i] /= A->data[i][i];
        }
        // multiply-accumulate each element of the submatrix.
        for(int x=i+1; x<N; x++) {
            for(int y=i+1; y<N; y++) {
                A->data[x][y] -= A->data[x][i]*A->data[i][y];
            }
        }
    }
}



/*
Y = A*B;
Y is (m x n), when A is (m x k) and B is (k x n).
*/
BasicMatrix multiply(BasicMatrix* A, BasicMatrix* B) {
    BasicMatrix Y;
    Y.x = A->x;
    Y.y = B->y;
    initialize_matrix(&Y);
    for(int i=0; i < Y.x; i++) {
        for(int j=0; j < Y.y; j++) {
            for(int k=0; k< A->y; k++) // A.y == B.x
            {
                Y.data[i][j] += ((A->data[i][k])*(B->data[k][j]));
            }
        }
    }
    return Y;
}

BasicMatrix* expand_LU(BasicMatrix* A) {
    int N = A->x;
    BasicMatrix L, U;
    BasicMatrix* LU = malloc(2*sizeof(BasicMatrix));
    L.x = L.y = U.x = U.y = N;
    initialize_matrix(&L);
    initialize_matrix(&U);
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i==j) {
                L.data[i][j] = 1;
            }
            if (i<=j) {
                U.data[i][j] = A->data[i][j];
            }
            else {
                L.data[i][j] = A->data[i][j];
            }
        }
    }
    LU[0] = L;
    LU[1] = U;
    return LU;
}


void validate_LU(BasicMatrix* A) {
    BasicMatrix* LU;
    LU = expand_LU(A);
    printf("Lower:\n");
    display_matrix(&LU[0]);
    printf("Upper:\n");
    display_matrix(&LU[1]);
    BasicMatrix Y;
    Y = multiply(&LU[0], &LU[1]);
    printf("L*U:\n");
    display_matrix(&Y);
}


void test_multiply() {
    BasicMatrix A = {
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
        3,
        3
    };
    BasicMatrix B = {
        {{0, 1, 0}, {1, 0, 0}, {0, 0, 1}},
        3,
        3
    };    
    display_matrix(&A);
    display_matrix(&B);
    BasicMatrix Y;
    Y = multiply(&B, &A);
    display_matrix(&Y);
}