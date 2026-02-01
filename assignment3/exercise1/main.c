/**
 * @file main.c
 * @brief Driver program for solving a dense linear system.
 *
 * This program reads a dense matrix from a file, constructs a right-hand side
 * vector, solves the linear system using a mixed precision iterative refinement
 * method, and prints an error estimate.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <lapacke.h>
#include <cblas.h>
#include "matrix.h"
#include <math.h> //for fabs
#include "dense_solvers.h" //for implemented function

/**
 * @brief Program entry point.
 *
 * The program expects a file containing a dense square matrix A as input.
 * It constructs a test vector x = (1, ..., 1)^T, computes the right-hand side
 * b = A x, and solves the linear system A x = b using mixed precision
 * iterative refinement.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 *             argv[1] must specify the input matrix file.
 *
 * @return
 *   Returns 0 on successful execution and a non-zero value on error.
 */
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

    // 3. Evaluate the relative backward error using LAPACKE_dlange
    // enumerator: ||x||_inf 
    double norm_x = LAPACKE_dlange(LAPACK_COL_MAJOR, 'I', n, 1, x.data, n);

    // numerator: ||x - x_approx||_inf
    double *diff = malloc(n * sizeof(double));
    if (diff) {
        for (int i = 0; i < n; i++) {
            diff[i] = x.data[i] - x_approx.data[i];
        }
        
        double norm_diff = LAPACKE_dlange(LAPACK_COL_MAJOR, 'I', n, 1, diff, n);
        double rel_error = norm_diff / norm_x;

        printf("\nrelative error: %e\n", rel_error);
        free(diff);
    } else {
        fprintf(stderr, "Memory allocation for error calculation failed.\n");
    }
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
