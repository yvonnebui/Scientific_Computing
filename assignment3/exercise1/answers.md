## Comparison of Solvers (Task 1.b)

### 1. Runtimes

- **mp_iter_refinement**:  
  Fastest method because the expensive LU factorization is performed in single
  precision (float), which is significantly cheaper for the CPU than double
  precision arithmetic.

- **basic_lu**:  
  Fast because it performs only one LU factorization without any iterative
  refinement, but at the cost of lower accuracy.

- **basic_iter_refinement**:  
  Slowest method since both the LU factorization and the refinement steps are
  carried out entirely in double precision.

**Influence of the Virtual Machine**:  
The virtual machine may cause fluctuations in the absolute runtimes. However,
the relative performance differences remain clearly visible, especially the
speed advantage of single precision factorization.

### 2. Residuals (Accuracy)

- **Iterative methods**:  
  Both *mp_iter_refinement* and *basic_iter_refinement* achieve very small
  residuals, indicating high solution accuracy.

- **mp_iter_refinement**:  
  Despite using a float-based LU factorization, high accuracy is achieved
  because the residual \( r = b - Ax \) is computed in double precision and
  iteratively corrected.

- **basic_lu**:  
  Shows the largest residual since it does not apply any iterative refinement
  steps to compensate for rounding errors.
