#include "stdio.h"
#include "math.h"
int main(void)
{
    int count, i, m, n, sum;
    int repeat, ri;
    int prime(int m);

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d", &m, &n);
        sum=0;
		count=0; 
        for(i=m;i<=n;i++)
        {
        	if(prime(i)==1)
        	{
        		sum=sum+i;
        		count++;
			} 
        }
        printf("Count = %d, sum = %d\n", count, sum);
    }
}
int prime(int m)
{
	int i,t;
	t=1;
	if(m==1)t=0;
	for(i=2;i<=m/2;i++)
	{
	    if(m%i==0) 
	    {
	    	t=0;
	    	break;
	    }
	}
	return t;
}
/*---------*/

