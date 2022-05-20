#include "stdio.h"
#include "math.h"
int main(void)
{
   int i, m, n;
   int repeat, ri;
   long f;
   long fib(int n);

   scanf("%d",&repeat);
   for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d", &m, &n);
        for(i=1;i<=n;i++)
        {
        	if(fib(i)>=m&&fib(i)<=n)
        	{
        		f=fib(i);
        		printf("%ld ", f); 
        	}
        }
        printf("\n");
    }
}
long fib(int n)
{
	int x1,x2,x,i;
	x1=1;
	x2=1;
	for(i=3;i<=n;i++)
	{
		x=x1+x2;
		x1=x2;
		x2=x;
	}
	return x2;
}
/*---------*/

