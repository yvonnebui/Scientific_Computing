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

    if (!ipiv || !A_f || !r_f || !d_f || !r) return 1; // Fehler bei malloc

    // 2. inital solve with low precision (float)
    // Convert a to float
    LAPACKE_dlag2s(LAPACK_COL_MAJOR, n, n, A, n, A_f, n);
    
    // copy b to d_f because algorithm works inplace (replaces b with solution vector d)
    for (int i = 0; i < n; i++) d_f[i] = (float)b[i];

    // LU Decompisition in float
    LAPACKE_sgetrf(LAPACK_COL_MAJOR, n, n, A_f, n, ipiv);
    
    // Solve ad = b with solution stored in d_f
    LAPACKE_sgetrs(LAPACK_COL_MAJOR, 'N', n, 1, A_f, n, ipiv, d_f, n);
    
    // convert first solution back to double and store in x
    for (int i = 0; i < n; i++) x[i] = (double)d_f[i];

    //  3. iterative refinement loop in higher precision 
    for (int iter = 0; iter < maxiter; iter++) {

        // r = b - Ax (in double), use BLAS for matrix vector product
        // dgemv makes inplace calculation from vektor b to r, general form: y=α⋅Ax+β⋅y
        for (int i = 0; i < n; i++) r[i] = b[i];
        cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1.0, A, n, x, 1, 1.0, r, 1); 

        // stopping criterion ||r||_inf < tau
        double r_norm = 0.0;
        for (int i = 0; i < n; i++) if (fabs(r[i]) > r_norm) r_norm = fabs(r[i]);
        
        if (r_norm < tau) {
            printf("convergence after %d iterations.\n", iter);
            break;
        }

        // solve Ad = r in float
        for (int i = 0; i < n; i++) r_f[i] = (float)r[i];
        LAPACKE_sgetrs(LAPACK_COL_MAJOR, 'N', n, 1, A_f, n, ipiv, r_f, n);

        // Update x = x + d (in double)
        for (int i = 0; i < n; i++) x[i] += (double)r_f[i];
    }

    // Speicher freigeben [cite: 29]
    free(ipiv); free(A_f); free(r_f); free(d_f); free(r);
    return 0;
}

