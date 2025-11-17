define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double eval_poly(int n, double *a, double x) {
    double result = 0.0;

    for (int i = 0; i <= n; i++) {

        double term = a[i];

        for (int j = 0; j < i; j++) {
            term = term * x;
        }

        result += term;
    }

    return result;
}

double eval_horner(int n, double *a, double x) {
    double result = a[n];

    for (int i = n - 1; i >= 0; i--) {
        result = result * x + a[i];
    }

    return result;
}

double eval_sumdiv(int n, double *d) {
    // start with 1
    double result = 1.0;

    // go backwards through the array
    for (int i = n; i >= 1; i--) {
        result = 1.0 + result / d[i];
    }

    // divide  with d[0]
    result = result / d[0];

    return result;
}

int main() {
// Exercise 2b 
    double coeffs[] = {-998.0, -998.0, -998.0, -998.0, -998.0, -998.0, 1.0};
    int n_poly = 6;


    // x = 1
    printf("Test for x = 1\n");
    double x1 = 1.0;
    double result1_poly = eval_poly(n_poly, coeffs, x1);
    double result1_horner = eval_horner(n_poly, coeffs, x1);

    printf("poly:   %.15f\n", result1_poly);
    printf("horner: %.15f\n", result1_horner);


    // x = 999
    printf("Test for x = 999\n");
    double x2 = 999.0;
    double result2_poly = eval_poly(n_poly, coeffs, x2);
    double result2_horner = eval_horner(n_poly, coeffs, x2);

    printf("poly:   %.15f\n", result2_poly);
    printf("horner: %.15f\n", result2_horner);

//Exercise 2b
    // fill the Array up to d_20
    double d[21];
    d[0] = 1.0;
    for (int i = 1; i <= 20; i++) {
        d[i] = (double)i;
    }

    // exact value
    double e_exact = M_E;

    // table for n = 1 to 20
    for (int n = 1; n <= 20; n++) {
        double e_approx = eval_sumdiv(n, d);
        double error = fabs(e_approx - e_exact);

        printf("%4d | %17.14f | %17.14f | %.15e\n",
               n, e_approx, e_exact, error);
    }

    return 0;
}
