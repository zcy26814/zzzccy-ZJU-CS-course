#include <stdio.h>
int main(void)
{
    struct complex{
        int real;
        int imag;
    }product, x, y;

    scanf("%d%d%d%d", &x.real, &x.imag, &y.real, &y.imag);
    product.real=x.real*y.real-x.imag*y.imag;
    product.imag=x.real*y.imag+x.imag*y.real;
    printf("(%d+%di) * (%d+%di) = %d + %di\n", x.real, x.imag, y.real, y.imag, product.real, product.imag);
}
