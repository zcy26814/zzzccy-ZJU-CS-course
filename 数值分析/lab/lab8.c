double Integral(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t)  {
    double PI = 3.1415926535898;
    int MAX_N = 10000;
    
    double T, ht, hr, Rt[2][MAX_N], Rr[2][MAX_N];
    int n, i, j, k;
    T = PI / t;
    n = (b - a) / T;
    ht = T;
    hr = b - a - n * T;
    Rt[0][0] = ht / 2 * (f(0, l, t) + f(T, l, t));
    Rr[0][0] = hr / 2 * (f(a, l, t) + f(a + hr, l, t));
    
    for(i=2; i<=MAX_N; i++) {
        Rt[1][0] = 0; Rr[1][0] = 0;
        for(k=1; k<=pow(2, i-2); k++) {
            Rt[1][0] += f((k-0.5) * ht, l, t);
            Rr[1][0] += f(a + (k - 0.5) * hr, l, t);
        }
        Rt[1][0] *= ht; Rt[1][0] += Rt[0][0]; Rt[1][0] /= 2;
        Rr[1][0] *= hr; Rr[1][0] += Rr[0][0]; Rr[1][0] /= 2;
        
        for(j=1; j<i; j++) {
            Rt[1][j] = Rt[1][j-1] + (Rt[1][j-1] - Rt[0][j-1]) / (pow(4, j) - 1);
            Rr[1][j] = Rr[1][j-1] + (Rr[1][j-1] - Rr[0][j-1]) / (pow(4, j) - 1);
        }
        
        if(fabs(Rt[1][i-1] * n + Rr[1][i-1] - Rt[0][i-2] * n - Rr[0][i-2]) < eps) {
            return (Rt[1][i-1] * n + Rr[1][i-1]) / 100;
        }
        
        ht /= 2;
        hr /= 2;
        for(j=0; j<i; j++) {
            Rt[0][j] = Rt[1][j];
            Rr[0][j] = Rr[1][j];
        }
    }
    return 0;
}


/*

6-8 Shape Roof
分数 50
作者 陈越
单位 浙江大学

The kind of roof shown in Figure 1 is shaped from plain flat rectangular plastic board in Figure 2.

Figure 1

Figure 2

The transection of the roof is a sine curve which fits the function y(x)=lsin(lx) in centimeters. Given the length of the roof, your task is to calculate the length of the flat board needed to shape the roof.
Format of function:

double Integral(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t);

where the function Integral returns the value of a definit integral of a given function pointed by f over a given interval from double a to double b. The integrant function f will be defined in the sample program of judge. Other parameters are: double eps, the accuracy of the resulting value of the integral; double l and double t, the altitude and the frequency of the sine curve, respectively.

Note: the length of the flat board which Integral returns must be in meters.
Sample program of judge:

#include <stdio.h>

#include <math.h>


double f0( double x, double l, double t )

{

    return sqrt(1.0+l*l*t*t*cos(t*x)*cos(t*x));

}


double Integral(double a, double b, double (*f)(double x, double y, double z), 

double eps, double l, double t);


int main()

{

    double a=0.0, b, eps=0.005, l, t;


    scanf("%lf %lf %lf", &l, &b, &t);

    printf("%.2f\n", Integral(a, b, f0, eps, l, t));


    return 0;

}


** Your function will be put here **

Sample Input:

2 100 1

Sample Output:

1.68

代码长度限制
16 KB
时间限制
650 ms
内存限制
64 MB

*/