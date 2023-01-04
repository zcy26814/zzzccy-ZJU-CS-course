double fabs(double x) {
    return x >= 0 ? x : -x;
}

void Price(int n, double p[]) {
    int i;
    double a[n], b[n], err;
    double threshold = 1e-6;
    for(i=0; i<n; i++) b[i] = p[i] / 2;
    while(1) {
        err = 0;
        for(i=0; i<n; i++) a[i] = p[i];
        p[0] = b[0] - (p[n-1] + p[1]) / 4;
        p[n-1] = b[n-1] - (p[n-2] + p[0]) / 4;
        for(i=1; i<n-1; i++) {
            p[i] = b[i] - (p[i-1] + p[i+1]) / 4;
        }
        for(i=0; i<n; i++) {
            err += fabs(a[i] - p[i]);
        }
        if(err < threshold) break;
    }
}


/*

6-3 There is No Free Lunch
分数 40
作者 陈越
单位 浙江大学

One day, CYLL found an interesting piece of commercial from newspaper: the Cyber-restaurant was offering a kind of "Lunch Special" which was said that one could "buy one get two for free". That is, if you buy one of the dishes on their menu, denoted by di​ with price pi​, you may get the two neighboring dishes di−1​ and di+1​ for free! If you pick up d1​, then you may get d2​ and the last one dn​ for free, and if you choose the last one dn​, you may get dn−1​ and d1​ for free.

However, after investigation CYLL realized that there was no free lunch at all. The price pi​ of the i-th dish was actually calculated by adding up twice the cost ci​ of the dish and half of the costs of the two "free" dishes. Now given all the prices on the menu, you are asked to help CYLL find the cost of each of the dishes.
Format of function:

void Price( int n, double p[] );

where int n satisfies that 2< n ≤10000; double p[] is passed into the function as an array of prices pi​ and then will be returned storing the costs of the dishes.
Sample program of judge:

#include <stdio.h>


#define Max_size 10000 // max number of dishes 


void Price( int n, double p[] );


int main()

{

    int n, i;

    double p[Max_size];


    scanf("%d", &n);

    for (i=0; i<n; i++) 

        scanf("%lf", &p[i]);

    Price(n, p);

    for (i=0; i<n; i++)

        printf("%.2f ", p[i]);

    printf("\n");


    return 0;

}


** Your function will be put here **

Sample Input:

12 23.64 17.39 12.77 16.62 10.67 14.85 12.68 26.90 28.30 15.59 37.99 23.18

Sample Output:

9.20 5.58 3.24 7.00 1.99 6.36 2.25 10.01 11.52 0.50 17.65 4.88 

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB

*/