double func(int n, double c[], double x) {
    int i;
    double y = 0;
    for(i=n; i>=0; i--) {
        y = c[i] + x * y;
    }
    return y;
}

double dfunc(int n, double c[], double x) {
    int i;
    double y =  0;
    for(i=n; i>0; i--) {
        y = i * c[i] + x * y;
    }
    return y;
}

double d2func(int n, double c[], double x) {
    int i;
    double y = 0;
    for(i=n; i>1; i--) {
        y = i * (i - 1) * c[i] + x * y;
    }
    return y;
}

void c2dc(int n, double c[], double arr[]) {
    int i;
    for(i=1; i<=n; i++) {
        arr[i - 1] = c[i] * i;
    }
}

double abs(double x) {
    return x >= 0 ? x : -x;
}

int sign(double x) {
    if(x > ZERO) {
        return 1;
    } else if(x < -ZERO) {
        return -1;
    } else {
        return 0;
    }
}

double Polynomial_Root(int n, double c[], double a, double b, double EPS) {
    int i, j, items = 5, max_step = 1000;
    double f, df, d2f, p, err, fb;
    if(b < a) {
        p = b;
        b = a;
        a = p;
    }

    for(i=0; i<=items; i++) {
        p = a + (b - a) * i / items;
        j = 0;
        while(j < max_step) {
            f = func(n, c, p);
            df = dfunc(n, c, p);
            d2f = d2func(n, c, p);
            if(sign(f) == 0) return p;
            fb = df * df - f * d2f;
            err = f * df / fb;
            if(p - err < a || p - err > b || sign(fb) == 0) break;
            if(sign(err) == 0) return p;
            p -= err;
            j++;
        }
    }
    while(1);
}


/*

6-2 Root of a Polynomial
分数 50
作者 陈越
单位 浙江大学

A polynomial of degree n has the common form as p(x)=cn​xn+cn−1​xn−1+⋯+c1​x+c0​. Your task is to write a function to find a root of a given polynomial in a given interval.
Format of function:

double Polynomial_Root(int n, double c[], double a, double b, double EPS);

where int n is the degree of the polynomial; double c[] is an array of n+1 coefficients cn​, cn−1​, ..., c1​, and c0​ of the given polynomial; double a and b are the two end-points of the given interval; and double EPS is the accuracy of the root.

The function must return the root.

Note: It is guaranteed that a unique real number r exists in the given interval such that p(r)=0.
Sample program of judge:

#include <stdio.h>

#include <math.h>

#define ZERO 1e-13 // X is considered to be 0 if |X|<ZERO 

#define MAXN 11    // Max Polynomial Degree + 1 

double Polynomial_Root(int n, double c[], double a, double b, double EPS);

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);

    for (i=n; i>=0; i--) 
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));

    return 0;
}

** Your function will be put here **

Sample Input:

2 1 1.5 -1
0 2

Sample Output:

0.5000

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB

*/