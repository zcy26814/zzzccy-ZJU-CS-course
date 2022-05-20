#include "stdio.h"
#include "math.h"
int prime(int i); 
int main(void)
{
    int count, i, m, n, number;

    scanf("%d%d", &m, &n);
    if(m % 2 != 0) m = m + 1;
    if(m >= 6){
    	count=0;
    	for(number=m;number<=n;number=number+2)
    	{
    	   for(i=2;i<number;i++)
    	    {
    		if(prime(i) && prime(number-i))
    		   {
			    printf("%d=%d+%d ", number, i, number-i);
    	        count=count+1;
				break;
			   }
    	    }
    	    if(count%5==0) printf("\n");
    }
}
}
int prime(int i)
{   int j,k;
	
	k=1;
	for(j=2;j<=sqrt(i);j++)
	{
		if(i%j==0)
		{
		k=0;
		break;
	    }
	}
	return k;
} 

