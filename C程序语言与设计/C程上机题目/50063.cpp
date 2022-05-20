#include "stdio.h"
int main(void)
{
    int i, m, n;
    int repeat, ri;
    int factorsum(int number); 
  
    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d", &m, &n);
        for(i=m;i<=n;i++)
        if(factorsum(i)==i)
		printf("%d ", i);
        printf("\n");
    }
}
int factorsum(int number)
{
	int i,sum;
	
	sum=0;
	if(number==1)sum=1;
	for(i=1;i<=number/2;i++)
	{
		if(number%i==0)sum +=i;
	}
	return sum;
}
/*---------*/

