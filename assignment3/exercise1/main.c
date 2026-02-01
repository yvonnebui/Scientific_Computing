#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <lapacke.h>
#include <cblas.h>
#include "matrix.h"
#include <math.h> //for fabs
#include "dense_solvers.h" //for implemented function

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    if (argc != 2) return 1;
    Matrix A;
    if (parse_matrix(argv[1], &A)) {
        fprintf(stderr, "Matrix file '%s' is invalid or does not exist.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    assert(A.ncols == A.nrows);
    int n = A.nrows;

    // init vector x
    Matrix x;
    x.nrows=n; x.ncols=1;
    x.data = malloc(n*sizeof(double));
    if (!x.data) return 1;
    for (int i=0; i<n; i++) x.data[i] = 1;

    // init vector b
    Matrix b;
    b.nrows=n;
    b.ncols=1;
    b.data = malloc(n*sizeof(double));
    if (!b.data) return 1;

    cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, 1, A.data, n, x.data, 1, 0, b.data, 1);

 //-----your implementation--------------------------------------------

    // 1. Reserve memory for x_approx 
    Matrix x_approx;
    x_approx.nrows = n; 
    x_approx.ncols = 1; //its a vector
    x_approx.data = malloc(n * sizeof(double));
    if (!x_approx.data) {
        free_matrix(&A);
        free_matrix(&x);
        free_matrix(&b);
        return 1;
    }

    // 2. Call implemented function 
    int maxiter = 100;
    mp_iter_refinement(n, A.data, b.data, x_approx.data, maxiter);

    // 3. Evaluate the relative backward error with infinite norm
    double max_diff = 0.0;
    double max_x_true = 0.0; // should be one

    for (int i = 0; i < n; i++) {
        // numerator: ||x - x_approx||_infnorm
        double diff = fabs(x.data[i] - x_approx.data[i]);
        if (diff > max_diff) max_diff = diff;
        
        // enumerator: ||x_true||_infnorm
        if (fabs(x.data[i]) > max_x_true) max_x_true = fabs(x.data[i]);
    }

    double rel_error = max_diff / max_x_true;
    printf("\nrelative error: %e\n", rel_error);

//----------------------------end of my implementation-----------------------------------------
    print_matrix("A", &A);
    print_matrix("x", &x);
    print_matrix("b", &b);

    free_matrix(&A);
    free_matrix(&x);
    free_matrix(&b);
    free_matrix(&x_approx); // also free the new vector

    return 0;
}
