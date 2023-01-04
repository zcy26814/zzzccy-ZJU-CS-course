int ca[MAX_SIZE][MAX_SIZE], cb[MAX_SIZE];

double fabs(double x) {
    if(x >= 0) {
        return x;
    } else {
        return -x;
    }
}

int prechange(int n, double a[][MAX_SIZE], double b[]) {
    int i, j, maxi;
    double maxa, tmp;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) ca[i][j] = a[i][j];
        cb[i] = b[i];
    }
    for(i=0; i<n; i++) {
        maxa = fabs(ca[i][i]);
        maxi = i;
        for(j=i+1; j<n; j++) {
            if(fabs(ca[j][i]) > maxa) {
                maxa = fabs(ca[j][i]);
                maxi = j;
            }
        }
        if(maxa > 0) {
            if(maxi > i) {
                for(j=0; j<n; j++) {
                    tmp = ca[i][j];
                    ca[i][j] = ca[maxi][j];
                    ca[maxi][j] = tmp;
                }
                tmp = cb[i];
                cb[i] = cb[maxi];
                cb[maxi] = tmp;
            }
        } else {
            for(j=0; j<i; j++) {
                if(fabs(ca[j][i]) > maxa) {
                    maxa = fabs(ca[j][i]);
                    maxi = j;
                }
            }
            if(maxa > 0) {
                if(maxi < i) {
                    for(j=0; j<n; j++) ca[i][j] = ca[maxi][j];
                    cb[i] = cb[maxi];
                }
            } else {
                return -1;
            }
        }
    }
    return 0;
}

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN ) {
    int i, j, iterator;
    double tmp, maxd, d[MAX_SIZE], my_bound = 1000;
    bool flag;
    if(prechange(n, a, b) == -1) return -1;
    for(i=0; i<n; i++) {
        if(ca[i][i] == 0) return -2;
    }
    for(iterator=1; iterator<=MAXN; iterator++) {
        maxd = 0;
        for(i=0; i<n; i++) {
            d[i] = cb[i];
            for(j=0; j<n; j++) {
                d[i] -= ca[i][j] * x[j];
            }
            d[i] /= ca[i][i];
        }
        for(i=0; i<n; i++) {
            if(maxd < fabs(d[i])) maxd = fabs(d[i]);
            x[i] += d[i];
        }
        if(maxd > my_bound) return -2;
        if(maxd < TOL) return iterator;
    }
    return 0;
}
    
int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN ) {
    int i, j, iterator;
    double tmp, maxd, my_bound = 1000;
    bool flag;
    if(prechange(n, a, b) == -1) return -1;
    for(i=0; i<n; i++) {
        if(ca[i][i] == 0) return -2;
    }
    for(iterator=1; iterator<=MAXN; iterator++) {
        maxd = 0;
        for(i=0; i<n; i++) {
            tmp = cb[i];
            for(j=0; j<n; j++) {
                tmp -= ca[i][j] * x[j];
            }
            tmp /= ca[i][i];
            x[i] += tmp;
            if(fabs(tmp) > maxd) maxd = fabs(tmp);
        }
        if(maxd > my_bound) return -2;
        if(maxd < TOL) return iterator;
    }
    return 0;
}


/*

6-4 Compare Methods of Jacobi with Gauss-Seidel
分数 50
作者 陈越
单位 浙江大学

Use Jacobi and Gauss-Seidel methods to solve a given n×n linear system Ax
=b
with an initial approximation x

(0).

Note: When checking each aii​, first scan downward for the entry with maximum absolute value (aii​ included). If that entry is non-zero, swap it to the diagonal. Otherwise if that entry is zero, scan upward for the entry with maximum absolute value. If that entry is non-zero, then add that row to the i-th row.
Format of functions:

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );


int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

where int n is the size of the matrix of which the entries are in the array double a[][MAX_SIZE] and MAX_SIZE is a constant defined by the judge; double b[] is for b
, double x[] passes in the initial approximation x
(0) and return the solution x
; double TOL is the tolerance for ∥x
(k+1)−x

(k)∥∞​; and finally int MAXN is the maximum number of iterations.

The function must return:

    k if there is a solution found after k iterations;
    0 if maximum number of iterations exceeded;
    1 if the matrix has a zero column and hence no unique solution exists;
    2 if there is no convergence, that is, there is an entry of x

    (K) that is out of the range [-bound, bound] where bound is a constant defined by the judge.

Sample program of judge:

#include <stdio.h>

#include <math.h>


#define MAX_SIZE 10

#define bound pow(2, 127)

#define ZERO 1e-9 // X is considered to be 0 if |X|<ZERO 


enum bool { false = 0, true = 1 };

#define bool enum bool


int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );


int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );


int main()

{

    int n, MAXN, i, j, k;

    double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];

    double TOL;


    scanf("%d", &n);

    for (i=0; i<n; i++) {

        for (j=0; j<n; j++)

            scanf("%lf", &a[i][j]);

        scanf("%lf", &b[i]);

    }

    scanf("%lf %d", &TOL, &MAXN);


    printf("Result of Jacobi method:\n");

    for ( i=0; i<n; i++ )

        x[i] = 0.0;

    k = Jacobi( n, a, b, x, TOL, MAXN );

    switch ( k ) {

        case -2:

            printf("No convergence.\n");

            break;

        case -1: 

            printf("Matrix has a zero column.  No unique solution exists.\n");

            break;

        case 0:

            printf("Maximum number of iterations exceeded.\n");

            break;

        default:

            printf("no_iteration = %d\n", k);

            for ( j=0; j<n; j++ )

                printf("%.8f\n", x[j]);

            break;

    }

    printf("Result of Gauss-Seidel method:\n");

    for ( i=0; i<n; i++ )

        x[i] = 0.0;

    k = Gauss_Seidel( n, a, b, x, TOL, MAXN );

    switch ( k ) {

        case -2:

            printf("No convergence.\n");

            break;

        case -1: 

            printf("Matrix has a zero column.  No unique solution exists.\n");

            break;

        case 0:

            printf("Maximum number of iterations exceeded.\n");

            break;

        default:

            printf("no_iteration = %d\n", k);

            for ( j=0; j<n; j++ )

                printf("%.8f\n", x[j]);

            break;

    }


    return 0;

}


** Your function will be put here **

Sample Input 1:

3
2	-1	1	-1
2	2	2	4
-1	-1	2	-5
0.000000001 1000

Sample Output 1:

Result of Jacobi method:
No convergence.
Result of Gauss-Seidel method:
no_iteration = 37
1.00000000
2.00000000
-1.00000000

Sample Input 2:

3
1    2    -2    7
1    1    1    2
2    2    1    5
0.000000001 1000

Sample Output 2:

Result of Jacobi method:
no_iteration = 232
1.00000000
2.00000000
-1.00000000
Result of Gauss-Seidel method:
No convergence.

Sample Input 3:

5
2 1 0 0 0 1
1 2 1 0 0 1
0 1 2 1 0 1
0 0 1 2 1 1
0 0 0 1 2 1
0.000000001 100

Sample Output 3:

Result of Jacobi method:
Maximum number of iterations exceeded.
Result of Gauss-Seidel method:
no_iteration = 65
0.50000000
0.00000000
0.50000000
0.00000000
0.50000000

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB

*/