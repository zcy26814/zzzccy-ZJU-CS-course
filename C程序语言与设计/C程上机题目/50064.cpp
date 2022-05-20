#include <stdio.h>
int main(void)
{
    long in, res;
    int ri, repeat;
    long reverse(long number); 

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%ld", &in);
        res=reverse(in);
        printf("%ld\n", res);
    }
}
long reverse(long number)
{
	int t, count, i, c, s, j, sum;
	
	s=t=number;
	count=1;
	sum=0;
	if(t<0) 
	number=t=-t;
	while(t>9)
	{
		t=t/10;
		count++;
	}
	for(i=1;i<=count;i++)
	{
		c=number%10;
		for(j=1;j<=count-i;j++)
		{
			c *=10;
		}
		sum +=c;
		number /=10;
    }
    if(s<0)sum=-sum;
    return sum;
}
/*---------*/

