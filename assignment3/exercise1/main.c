/**
 * @file main.c
 * @brief Driver program for solving a dense linear system.
 *
 * This program reads a dense matrix from a file, constructs a right-hand side
 * vector, runs different solvers, measures runtime, and writes residuals to CSV.
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
#include <time.h>

/**
 * @brief Helper function for time measurement for ex 1b
 */
static double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

/**
 * @brief Calculates the relative error ||x - x_approx||_inf / ||x||_inf using LAPACK. (For 1b)
 */
double calculate_rel_error(int n, double *x_true, double *x_approx) {
    // Denominator: ||x||_inf
    double norm_x = LAPACKE_dlange(LAPACK_COL_MAJOR, 'I', n, 1, x_true, n);

    // Numerator: ||x - x_approx||_inf
    double *diff = malloc(n * sizeof(double));
    if (!diff) return -1.0;

    for (int i = 0; i < n; i++) {
        diff[i] = x_true[i] - x_approx[i];
    }

    double norm_diff = LAPACKE_dlange(LAPACK_COL_MAJOR, 'I', n, 1, diff, n);
    free(diff);

    return (norm_x > 0) ? (norm_diff / norm_x) : norm_diff;
}


/**
 * @brief Program entry point.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments (argv[1] is the input matrix file).
 * @return 0 on success, non-zero on failure.
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

// -------------------- start exercise 1b --------------------
    // Write runtime + residuals for different solvers to CSV
    FILE *f = fopen("measurements.csv", "w");
    if (f) {
        fprintf(f, "function,runtime_in_s,residual\n");

        double start, end;
        double res;

        // 1) Mixed-precision iterative refinement
        start = get_time();
        mp_iter_refinement(n, A.data, b.data, x_approx.data, 100);
        end = get_time();
        res = calculate_rel_error(n, x.data, x_approx.data);
        fprintf(f, "mp_iter_refinement,%e,%e\n", end - start, res);

        // 2) Double precision LU solver
        start = get_time();
        basic_lu(n, A.data, b.data, x_approx.data);
        end = get_time();
        res = calculate_rel_error(n, x.data, x_approx.data);
        fprintf(f, "basic_lu,%e,%e\n", end - start, res);

        // 3) Double precision iterative refinement
        start = get_time();
        basic_iter_refinement(n, A.data, b.data, x_approx.data);
        end = get_time();
        res = calculate_rel_error(n, x.data, x_approx.data);
        fprintf(f, "basic_iter_refinement,%e,%e\n", end - start, res);

        fclose(f);
    } else {
        fprintf(stderr, "Could not open measurements.csv for writing.\n");
    }
    // ------------------ exercise 1b ------------------
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
