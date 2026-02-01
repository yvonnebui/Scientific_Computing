/**
 * @file dense_solvers.h
 * @brief Prototypes for dense linear system solvers.
 *
 * This header defines functions for solving dense linear systems using
 * mixed-precision iterative refinement, standard LU factorization,
 * and double-precision iterative refinement.
 */

#ifndef DENSE_SOLVERS_H
#define DENSE_SOLVERS_H

/**
 * @brief Solves Ax = b using mixed-precision iterative refinement.
 *
 * This method factors the matrix in single precision (float) to save time,
 * then iteratively improves the solution in double precision.
 *
 * @param n Dimension of the square matrix A and vectors b, x.
 * @param A Pointer to the n-by-n matrix (column-major).
 * @param b Pointer to the right-hand side vector (not modified).
 * @param x Pointer to the solution vector (updated in-place).
 * @param maxiter Maximum number of refinement iterations.
 *
 * @return 0 on success, non-zero on failure.
 */
int mp_iter_refinement(int n, double *A, double *b, double *x, int maxiter);

/**
 * @brief Solve a dense linear system using standard double precision LU factorization.
 *
 * This function uses the LAPACK routine DGETRS to compute the solution.
 *
 * @param n Dimension of the square matrix A.
 * @param A Pointer to the system matrix A.
 * @param b Pointer to the right-hand side vector b.
 * @param x Pointer to the solution vector.
 * @return Returns 0 on success, non-zero on failure.
 */
int basic_lu(int n, double *A, double *b, double *x);

/**
 * @brief Solve a dense linear system using double precision iterative refinement.
 *
 * This function uses the LAPACK routine DGERFS to compute the refined solution.
 *
 * @param n Dimension of the square matrix A.
 * @param A Pointer to the system matrix A.
 * @param b Pointer to the right-hand side vector b.
 * @param x Pointer to the solution vector.
 * @return Returns 0 on success, non-zero on failure.
 */
int basic_iter_refinement(int n, double *A, double *b, double *x);

#endif


