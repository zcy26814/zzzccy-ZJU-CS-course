#include <stdio.h>
int fun(int n);
int main(void)
{	
    int m1,m2;

    scanf("%d%d", &m1, &m2);
    printf("%d的逆向是%d\n", m1, fun(m1));  
    printf("%d的逆向是%d\n", m2, fun(m2));  

}
int fun(int number)
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


