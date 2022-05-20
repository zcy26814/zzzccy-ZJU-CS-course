#include "stdio.h"
int main(void)
{
    int i, m, n;
    int repeat, ri;
    int is(int number); 
  
    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d", &m, &n);
        printf("result:\n");
        for(i=m;i<=n;i++)
        if(is(i)==1)printf("%d\n", i);
/*---------*/
    }
}
int is(int number)
{
	int t, g,sum;
	t=number;
	sum=0;
	while(t>0)
	{
		g=t%10;
		sum=sum+g*g*g;
		t/=10;
	}
	if(sum==number)
	g=1;
	else g=0;
	return g;
}
/*---------*/
