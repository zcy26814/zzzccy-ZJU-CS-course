double gx[MAX_m], gy[MAX_m], gw[MAX_m];

int gm;

double Poly_Oper(double* f, int ff, double* g, int fg) {
    double r, s, p;
    int i, j;
    
    r = 0;
    for(i=0; i<gm; i++) {
        s = gw[i];
        p = 0;
        if(ff == 1) {
            p = gy[i];
        } else {
            for(j=0; j<=MAX_n; j++) {
                p += f[j] * pow(gx[i], j);
            }
        }
        s *= p;
        
        p = 0;
        if(fg == 1) {
            p = gy[i];
        } else {
            for(j=0; j<=MAX_n; j++) {
                p += g[j] * pow(gx[i], j);
            }
        }
        s *= p;
        r += s;
    }
    
    return r;
}

int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps ) {
    double phi_0[MAX_n + 1] = {0}, phi_1[MAX_n + 1] = {0}, phi_2[MAX_n + 1] = {0};
    double x_phi_0[MAX_n + 1] = {0}, x_phi_1[MAX_n + 1] = {0}, x_phi_2[MAX_n + 1] = {0};
    double y[MAX_n +1] = {0}, a_0, b_1, c_1, error;
    int i, j;
    
    for(i=0; i<m; i++) {
        gx[i] = x[i];
        gy[i] = f(x[i]);
        gw[i] = w[i];
    }
    gm = m;
    
    phi_0[0] = 1; y[1] = 1;
    a_0 = Poly_Oper(phi_0, 0, y, 1) / Poly_Oper(phi_0, 0, phi_0, 0);
    error = Poly_Oper(y, 1, y, 1) - a_0 * Poly_Oper(phi_0, 0, y, 1);
    
    for(i=0; i<=MAX_n; i++) {
        c[i] = a_0 * phi_0[i];
    }
    
    for(i=0; i<MAX_n; i++) {
        x_phi_0[i+1] = phi_0[i];
    }
    
    b_1 = Poly_Oper(x_phi_0, 0,phi_0, 0) / Poly_Oper(phi_0, 0, phi_0, 0);
    phi_1[0] = -b_1; phi_1[1] = 1;
    a_0 = Poly_Oper(phi_1, 0, y, 1) / Poly_Oper(phi_1, 0, phi_1, 0);
    error -= a_0 * Poly_Oper(phi_1, 0, y, 1);
    
    for(i=0; i<=MAX_n; i++) {
        c[i] += a_0 * phi_1[i];
    }
    
    for(i=1; i<MAX_n; i++) {
        if(fabs(error) < *eps) break;
        if(phi_1[MAX_n] != 0) {
            *eps = error;
            return i + 1;
        }
        
        x_phi_0[0] = 0; phi_2[0] = 0;
        
        for(j=0; j<MAX_n; j++) {
            x_phi_0[j+1] = phi_1[j];
        }
        for(j=0; j<MAX_n; j++) {
            phi_2[j+1] = phi_1[j];
        }
        
        b_1 = Poly_Oper(x_phi_0, 0, phi_1, 0) / Poly_Oper(phi_1, 0, phi_1, 0);
        c_1 = Poly_Oper(x_phi_0, 0, phi_0, 0) / Poly_Oper(phi_0, 0, phi_0, 0);
       
        for(j=0; j<=MAX_n; j++) {
            phi_2[j] -= b_1* phi_1[j] + c_1 * phi_0[j];
        }
        
        a_0 = Poly_Oper(phi_2, 0, y, 1) / Poly_Oper(phi_2, 0, phi_2, 0);
        
        for(j=0; j<=MAX_n; j++) {
            c[j] += a_0 * phi_2[j];
        }
        
        error -= a_0 * Poly_Oper(phi_2, 0, y, 1);
        for(j=0; j<=MAX_n; j++) {
            phi_0[j] = phi_1[j];
            phi_1[j] = phi_2[j];
        }
        
    }
    *eps = error;
    return i;
}


/*

6-7 Orthogonal Polynomials Approximation
分数 40
作者 陈越
单位 浙江大学

Given a function f and a set of m>0 distinct points x1​<x2​<⋯<xm​. You are supposed to write a function to approximate f by an orthogonal polynomial using the exact function values at the given m points with a weight w(xi​) assigned to each point xi​. The total error err=∑i=1m​w(xi​)[f(xi​)−Pn​(xi​)]2 must be no larger than a given tolerance.
Format of function:

int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps );

where the function pointer double (*f)(double t) defines the function f; int m is the number of points; double x[] contains points x1​<x2​<⋯<xm​; double w[] contains the values of a weight function at the given points x[]; double c[] contains the coefficients c0​,c1​,⋯,cn​ of the approximation polynomial Pn​(x)=c0​+c1​x+⋯+cn​xn; double *eps is passed into the function as the tolerance for the error, and is supposed to be returned as the value of error. The function OPA is supposed to return the degree of the approximation polynomial.

Note: a constant Max_n is defined so that if the total error is still not small enough when n = Max_n, simply output the result obtained when n = Max_n.
Sample program of judge:

#include <stdio.h>

#include <math.h>


#define MAX_m 200

#define MAX_n 5


double f1(double x)

{

    return sin(x);

}


double f2(double x)

{

    return exp(x);

}


int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps );


void print_results( int n, double c[], double eps)

{    

    int i;


    printf("%d\n", n);

    for (i=0; i<=n; i++)

        printf("%12.4e ", c[i]);

    printf("\n");

    printf("error = %9.2e\n", eps);

    printf("\n");

}


int main()

{

    int m, i, n;

    double x[MAX_m], w[MAX_m], c[MAX_n+1], eps;


    m = 90;

    for (i=0; i<m; i++) {

        x[i] = 3.1415926535897932 * (double)(i+1) / 180.0;

        w[i] = 1.0;

    }

    eps = 0.001;

    n = OPA(f1, m, x, w, c, &eps);

    print_results(n, c, eps);


    m = 200;

    for (i=0; i<m; i++) {

        x[i] = 0.01*(double)i;

        w[i] = 1.0;

    }

    eps = 0.001;

    n = OPA(f2, m, x, w, c, &eps);

    print_results(n, c, eps);


    return 0;

}


** Your function will be put here **

Sample Output:

3
 -2.5301e-03   1.0287e+00  -7.2279e-02  -1.1287e-01 
error =  6.33e-05

4
  1.0025e+00   9.6180e-01   6.2900e-01   7.0907e-03   1.1792e-01 
error =  1.62e-04

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB

*/