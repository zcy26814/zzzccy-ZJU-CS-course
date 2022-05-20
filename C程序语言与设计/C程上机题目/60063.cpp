#include<stdio.h>
#include<math.h>
int main(void)
{
	int repeat, i, j, data, a;
	
	scanf("%d",&repeat);
	for(i=1;i<=repeat;i++)
	{
		scanf("%d",&data);
		data %=256;
		for(j=1;j<=4;j++)
		{
			a=(int)pow(2,8-j);
			printf("%d,", data/a);
			data=data%a;
		}
		printf("\n"); 
	}
}
