void Series_Sum(double sum[]) {
    int i, j;
    double x, y, t;
        
    sum[0] = 1.644934066848;
    sum[10] = 1;
    for(i=1; i<10; i++) {
        x = 0.1 * i;
        y = 0;
        t = 1 / (24 * (1 + x));
        for(j=1; j<1100; j++) {
            y += t;
            t *= (j + x) / (j + 1 + x) * j / (j + 4);
        }
        sum[i] = 1 + (1 - x) * (0.25 + (2 - x) * ((3 - x) * y + 1.0 / 18));
    }
    for(i=11; i<3001; i++) {
        sum[i] = ((i - 10) * sum[i - 10] + 100.0 / i) / i;
    }
}


/*

6-1 Numerical Summation of a Series
分数 40
作者 陈越
单位 浙江大学

Produce a table of the values of the series

ϕ(x)=∑k=1∞​k(k+x)1​ ......(1)

for the 3001 values of x, x = 0.0, 0.1, 0.2, ..., 300.00. All entries of the table must have an absolute error less than 10−10. This problem is based on a problem from Hamming (1962), when mainframes were very slow by today's microcomputer standards.
Format of function:

void Series_Sum( double sum[] );

where double sum[] is an array of 3001 entries, each contains a value of ϕ(x) for x = 0.0, 0.1, 0.2, ..., 300.00.
Sample program of judge:

#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];

    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);

    return 0;
}

** Your function will be put here **

Sample Output:

0.00   1.644934066848
0.10   1.534607244904
...
1.00   1.000000000000
...
2.00   0.750000000000
...
300.00   0.020942212934

Hint:

The problem with summing the sequence in equation (1) is that too many terms may be required to complete the summation in the given time. Additionally, if enough terms were to be summed, roundoff would render any typical double precision computation useless for the desired precision.

To improve the convergence of the summation process note that

k(k+1)1​=k1​−k+11​......(2)

which implies ϕ(1)=1.0. One can then produce a series for ϕ(x)−ϕ(1) which converges faster than the original series. This series not only converges much faster, it also reduces roundoff loss.

This process of finding a faster converging series may be repeated again on the second series to produce a third sequence, which converges even more rapidly than the second.

The following equation is helpful in determining how may items are required in summing the series above.

∑k=n∞​kr1​<∫n−1∞​xr1​dx for k>1 and r≥1......(3)
代码长度限制
16 KB
时间限制
100 ms
内存限制
64 MB

*/