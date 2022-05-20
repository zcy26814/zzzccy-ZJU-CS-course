#include "stdio.h"
int main(void)
{
    int count, digit, in; 
    int repeat, ri;
    int countdigit(int number, int digit);

    scanf("%d",&repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d", &in, &digit);
        count=countdigit(in,digit);
        printf("Number %d of digit %d: %d\n", in, digit, count);
    }
}
int countdigit(int number, int digit)
{
	int t, count;
	if(number<0)number=-number;
	count=0;
	if(number==0&&digit==0)count++;
	while(number>0)
	{
	    t=number%10;
	    if(t==digit)
	    count++;
	    number/=10;
	}
	return count;
}
/*---------*/

