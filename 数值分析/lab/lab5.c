double fabs(double x) {
    if(x >= 0) {
        return x;
    } else {
        return -x;
    }
}

int maxindex(int n, double x[]) {
    double t;
    int i, maxi;
    t = 0;
    maxi = 0;
    for(i=0; i<n; i++) {
        if(t < fabs(x[i])) {
            t = fabs(x[i]);
            maxi = i;
        }
    }
    return maxi;
}

int LU(int n, double a[][MAX_SIZE], double l[][MAX_SIZE], double u[][MAX_SIZE]) {
    int i, j, k;
    
    for(i=0; i<n; i++) {
        l[i][i] = 1;
        for(j=i; j<n; j++) {
            u[i][j] = a[i][j];
            for(k=0; k<i; k++) {
                u[i][j] -= l[i][k] * u[k][j];
            }
        }
        if(u[i][i] == 0) return -1;
        for(j=i+1; j<n; j++) {
            l[j][i] = a[j][i];
            for(k=0; k<i; k++) {
                l[j][i] -= l[j][k] * u[k][i];
            }
            l[j][i] /= u[i][i];
        }
    }
    return 0;
}

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN) {
    double l[MAX_SIZE][MAX_SIZE], u[MAX_SIZE][MAX_SIZE], ca[MAX_SIZE][MAX_SIZE], x[MAX_SIZE], y[MAX_SIZE], err, mu, t;
    int i, j, k, p;
    
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) ca[i][j] = a[i][j];
        ca[i][i] -= *lambda;
    }
    if(LU(n, ca, l, u) == -1) return -1;
    
    p = maxindex(n, v);
    t = v[p];
    for(i=0; i<n; i++) v[i] /= t;
    
    for(k=1; k<=MAXN; k++) {
        err = 0;
        for(i=0; i<n; i++) {
            y[i] = v[i];
            for(j=0; j<i; j++) {
                y[i] -= l[i][j] * y[j];
            }
        }
        
        for(i=n-1; i>=0; i--) {
            x[i] = y[i];
            for(j=n-1; j>i; j--) {
                x[i] -= u[i][j] * x[j];
            }
            x[i] /= u[i][i];
        }
        
        mu = x[p];
        p = maxindex(n, x);
        t = x[p];
        for(i=0; i<n; i++) x[i] /= t;
        
        for(i=0; i<n; i++) {
            if(fabs(x[i] - v[i]) > err) err = fabs(x[i] - v[i]);
            v[i] = x[i];
        }
        if(err < TOL) {
            *lambda += 1 / mu;
            return 1;
        }
    }
    return 0;
}


/*

Approximate an eigenvalue and an associated eigenvector of a given n×n matrix A near a given value p and a nonzero vector x
=(x1​,⋯,xn​)T.
Format of function:

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);

where int n is the size of the matrix of which the entries are in the array double a[][MAX_SIZE] and MAX_SIZE is a constant defined by the judge; double *lambda is passed into the function as an initial approximation p of the eigenvalue and is supposed to be returned as a more accurate eigenvalue; double v[] is passed into the function as the initial vector x

and is supposed to be returned as the associated eigenvector with unit ∥⋅∥∞​ norm; double TOL is the tolerance for the eigenvalue; and finally int MAXN is the maximum number of iterations.

The function must return:

    1 if there is a solution;
    0 if maximum number of iterations exceeded;
    −1 if p is just the accurate eigenvalue.

Sample program of judge:

#include <stdio.h>


#define MAX_SIZE 10


int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);


int main()

{

    int n, MAXN, m, i, j, k;

    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];

    double lambda, TOL;


    scanf("%d", &n);

    for (i=0; i<n; i++) 

        for (j=0; j<n; j++) 

            scanf("%lf", &a[i][j]);

    scanf("%lf %d", &TOL, &MAXN);

    scanf("%d", &m);

    for (i=0; i<m; i++) {

        scanf("%lf", &lambda);

        for (j=0; j<n; j++)

            scanf("%lf", &v[j]);

        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {

            case -1: 

                printf("%12.8f is an eigenvalue.\n", lambda );

                break;

            case 0:

                printf("Maximum number of iterations exceeded.\n");

                break;

            case 1:

                printf("%12.8f\n", lambda );

                for (k=0; k<n; k++)

                    printf("%12.8f ", v[k]);

                printf("\n");

                break;

        }

    }


    return 0;

}


** Your function will be put here **

Sample Input 1:

3
1 2 3
2 3 4
3 4 5
0.0000000001 1000
1
-0.6 1 1 1

Sample Output 1:

-0.62347538
  1.00000000   0.17206558  -0.65586885 
  
*/