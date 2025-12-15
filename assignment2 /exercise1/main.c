
#include <stdio.h>    // for printf
#include <stdlib.h>   
#include <math.h>
#include "axpy.h"
#include <sys/time.h>

double wtime() {
    struct timeval tv; 
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

int main(int argc, char **argv) {
    const int repetitions = 50;  
    const double alpha = 2.0;    
    int n = 1000000;             

    // 1. memory allocation
    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));
    double *z = (double *)malloc(n * sizeof(double));

    // 2. initialize
    for (int i = 0; i < n; i++) {
        x[i] = (double)i; 
        y[i] = 1.0;                 
    }

    // variable for time measurements
    double start_time, end_time, runtime_last = 0.0;
    double min_runtime = 1e30; // initialize with big number
    // 3. measure 50 times
    for (int r = 0; r < repetitions; r++) {
        start_time = wtime(); 
        axpy(n, alpha, x, y, z);
        end_time = wtime();
        runtime_last = end_time - start_time;
        printf("runtime %d: %.6f s\n", r, runtime_last);

        if (runtime_last < min_runtime) {
        min_runtime = runtime_last;
        }
    }

    printf("Trustworthy Runtime (Minimum): %.6f s\n", min_runtime);

    // free memory                           
    free(x); free(y); free(z);                
    
    return EXIT_SUCCESS;
}
 
    
    
