#include <stdio.h>
int main(void)
{    
    int n;
    double factorial;
    double fact(int n);

    scanf ("%d", &n);
    factorial=fact(n);
    printf("%d! = %f\n", n, factorial);
}

double fact(int n)
{
	int i, sum;
	sum=1;
	for(i=1;i<=n;i++)
	{
		sum=sum*i;
	}
	return sum;
}

