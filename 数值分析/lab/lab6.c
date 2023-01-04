void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]) {
    double h[MAX_N], alpha[MAX_N], l[MAX_N], z[MAX_N], mu[MAX_N];
    int i;
    
    for(i=0; i<=n; i++) a[i+1] = f[i];
    for(i=0; i<n; i++) h[i] = x[i+1] - x[i];
    for(i=1; i<n; i++) alpha[i] = 3 / h[i] * (f[i+1] - f[i]) - 3 / h[i-1] * (f[i] - f[i-1]);
    
    if(Type == 1) {
        alpha[0] = 3 / h[0] * (f[1] - f[0]) - 3 * s0;
        alpha[n] = 3 * sn - 3 / h[n-1] * (f[n] - f[n-1]);
        
        l[0] = 2 * h[0];
        mu[0] = 0.5;
        z[0] = alpha[0] / l[0];
        
        for(i=1; i<n; i++) {
            l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * mu[i-1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
        }
        
        l[n] = h[n-1] * (2 - mu[n-1]);
        z[n] = (alpha[n] - h[n-1] * z[n-1]) / l[n];
        c[n+1] = z[n];
        
        for(i=n-1; i>=0; i--) {
            c[i+1] = z[i] - mu[i] * c[i+2];
            b[i+1] = (a[i+2] - a[i+1]) / h[i] - h[i] * (c[i+2] + 2 * c[i+1]) / 3;
            d[i+1] = (c[i+2] - c[i+1]) / (3 * h[i]);
        }
    } else if(Type == 2) {
        l[0] = 1;
        mu[0] = 0;
        z[0] = s0 / 2;
        
        for(i=1; i<n; i++) {
            l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * mu[i-1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i]; 
        }
        
        l[n] = 1;
        z[n] = sn / 2;
        c[n+1] = sn / 2;
        
        for(i=n-1; i>=0; i--) {
            c[i+1] = z[i] - mu[i] * c[i+2];
            b[i+1] = (a[i+2] - a[i+1]) / h[i] - h[i] * (c[i+2] + 2 * c[i+1]) / 3;
            d[i+1] = (c[i+2] - c[i+1]) / (3 * h[i]);
        }
    }
    
    
}

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] ) {
    int k;
    
    if(t < x[0] || t > x[n]) return Fmax;
    
    k = 0;
    while(t > x[k]) k++;
    if(t == x[0]) k++;
    
    return a[k] + (t - x[k-1]) * (b[k] + (t - x[k-1]) * (c[k] + (t - x[k-1]) * d[k]));
}


/*

6-6 Cubic Spline
分数 50
作者 陈越
单位 浙江大学

Construct the cubic spline interpolant S for the function f, defined at points x0​<x1​<⋯<xn​, satisfying some given boundary conditions. Partition a given interval into m equal-length subintervals, and approximate the function values at the endpoints of these subintervals.
Format of functions:

void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);


double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] );

The function Cubic_Spline is for calculating the set of coefficients of S(x) where S(x)=S[j](x)=aj​+bj​(x−xj−1​)+cj​(x−xj−1​)2+dj​(x−xj−1​)3 for x∈[xj−1​,xj​]. The function S is for obtaining an approximation of f(t) using the spline function S(t). The parameters are defined as the following:

int n is the number of interpolating points−1;

double x[] contains n+1 distinct real numbers x0​<x1​<⋯<xn​;

double f[] contains n+1 real numbers f(x0​),f(x1​),⋯f(xn​);

int Type is the type of boundary conditions, where 1 corresponds to the clamped boundary condition S′(x0​)=s0​, S′(xn​)=sn​ and 2 corresponds to the natural boundary condition S′′(x0​)=s0​, S′′(xn​)=sn​;

double s0 and double sn are s0​ and sn​, respectively;

double a[], b[], c[], and d[] contain the set of coefficients of S(x);

double t is an endpoint of a subinterval;

and finally double Fmax is the default value that S(t) will assume if t is out of the range [x0​,xn​].
Sample program of judge:

#include <stdio.h>


#define MAX_N 10


void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);


double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] );


int main()

{

    int n, Type, m, i;

    double x[MAX_N], f[MAX_N], a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];

    double s0, sn, Fmax, t0, tm, h, t;


    scanf("%d", &n);

    for (i=0; i<=n; i++) 

        scanf("%lf", &x[i]);

    for (i=0; i<=n; i++) 

        scanf("%lf", &f[i]);

    scanf("%d %lf %lf %lf", &Type, &s0, &sn, &Fmax);


    Cubic_Spline(n, x, f, Type, s0, sn, a, b, c, d);

    for (i=1; i<=n; i++)

        printf("%12.8e %12.8e %12.8e %12.8e \n", a[i], b[i], c[i], d[i]);


    scanf("%lf %lf %d", &t0, &tm, &m);

    h = (tm-t0)/(double)m;

    for (i=0; i<=m; i++) {

        t = t0+h*(double)i;

        printf("f(%12.8e) = %12.8e\n", t, S(t, Fmax, n, x, a, b, c, d));

    }


    return 0;

}


** Your functions will be put here **

Sample Input:

2
0.0 1.0 2.0
0.0 1.0 2.0
1 1.0 1.0 0.0
0.0 3.0 2

Sample Output:

0.00000000e+00 1.00000000e+00 0.00000000e+00 0.00000000e+00 
1.00000000e+00 1.00000000e+00 0.00000000e+00 0.00000000e+00 
f(0.00000000e+00) = 0.00000000e+00
f(1.50000000e+00) = 1.50000000e+00
f(3.00000000e+00) = 0.00000000e+00

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB

*/