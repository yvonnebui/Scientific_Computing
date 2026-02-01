/**
 * @file dense_solvers.c
 * @brief Implementation of mixed-precision and standard iterative solvers.
 * Contains the algorithmic logic for Task 1, utilizing BLAS and LAPACK
 * routines like GETRF and GETRS.
 */

#include <stdlib.h>
#include <lapacke.h>
#include <stdio.h>
#include <math.h>
#include <cblas.h>

int mp_iter_refinement(int n, double *A, double *b, double *x, int maxiter) {
    double tau = 1e-13;

    // 1. allocate memory
    int *ipiv = (int *)malloc(n * sizeof(int));
    float *A_f = (float *)malloc(n * n * sizeof(float));
    float *r_f = (float *)malloc(n * sizeof(float));
    float *d_f = (float *)malloc(n * sizeof(float));
    double *r = (double *)malloc(n * sizeof(double));

    if (!ipiv || !A_f || !r_f || !d_f || !r) return 1; // malloc failed

    // 2. initial solve with low precision (float)
    // Convert A to float
    LAPACKE_dlag2s(LAPACK_COL_MAJOR, n, n, A, n, A_f, n);

    // copy b to d_f because algorithm works in-place (replaces d with solution vector)
    for (int i = 0; i < n; i++) d_f[i] = (float)b[i];

    // LU decomposition in float
    LAPACKE_sgetrf(LAPACK_COL_MAJOR, n, n, A_f, n, ipiv);

    // Solve A d = b with solution stored in d_f
    LAPACKE_sgetrs(LAPACK_COL_MAJOR, 'N', n, 1, A_f, n, ipiv, d_f, n);

    // convert first solution back to double and store in x
    for (int i = 0; i < n; i++) x[i] = (double)d_f[i];

    // 3. iterative refinement loop in higher precision
    for (int iter = 0; iter < maxiter; iter++) {

        // r = b - A x (double), use BLAS for matrix-vector product
        // dgemv: y = alpha*A*x + beta*y
        for (int i = 0; i < n; i++) r[i] = b[i];
        cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1.0, A, n, x, 1, 1.0, r, 1);

        // stopping criterion ||r||_inf < tau
        double r_norm = 0.0;
        for (int i = 0; i < n; i++) if (fabs(r[i]) > r_norm) r_norm = fabs(r[i]);

        if (r_norm < tau) {
            printf("convergence after %d iterations.\n", iter);
            break;
        }

        // solve A d = r in float
        for (int i = 0; i < n; i++) r_f[i] = (float)r[i];
        LAPACKE_sgetrs(LAPACK_COL_MAJOR, 'N', n, 1, A_f, n, ipiv, r_f, n);

        // update x = x + d (double)
        for (int i = 0; i < n; i++) x[i] += (double)r_f[i];
    }

    // free memory
    free(ipiv); free(A_f); free(r_f); free(d_f); free(r);
    return 0;
}

int basic_lu(int n, double *A, double *b, double *x) {
    int info;
    int *ipiv = malloc(n * sizeof(int));
    double *A_copy = malloc(n * n * sizeof(double));
    if (!ipiv || !A_copy) return 1;

    // Copy A because GETRF works in-place
    for (int i = 0; i < n * n; i++) A_copy[i] = A[i];
    for (int i = 0; i < n; i++) x[i] = b[i];

    // LU factorization (double)
    info = LAPACKE_dgetrf(LAPACK_COL_MAJOR, n, n, A_copy, n, ipiv);
    if (info != 0) { free(ipiv); free(A_copy); return info; }

    // Solve
    info = LAPACKE_dgetrs(LAPACK_COL_MAJOR, 'N', n, 1, A_copy, n, ipiv, x, n);

    free(ipiv);
    free(A_copy);
    return info;
}

int basic_iter_refinement(int n, double *A, double *b, double *x) {
    int info;
    int *ipiv = malloc(n * sizeof(int));
    double *A_copy = malloc(n * n * sizeof(double));
    double *b_copy = malloc(n * sizeof(double));
    double *ferr = malloc(sizeof(double)); // forward error bound
    double *berr = malloc(sizeof(double)); // backward error bound

    if (!ipiv || !A_copy || !b_copy || !ferr || !berr) return 1;

    for (int i = 0; i < n * n; i++) A_copy[i] = A[i];
    for (int i = 0; i < n; i++) {
        b_copy[i] = b[i];
        x[i] = b[i]; // initial guess
    }

    // Factorization
    info = LAPACKE_dgetrf(LAPACK_COL_MAJOR, n, n, A_copy, n, ipiv);
    if (info == 0) {
        // DGERFS refines the solution x
        info = LAPACKE_dgerfs(LAPACK_COL_MAJOR, 'N', n, 1, A, n, A_copy, n, ipiv, b_copy, n, x, n, ferr, berr);
    }

    free(ipiv); free(A_copy); free(b_copy); free(ferr); free(berr);
    return info;
}

