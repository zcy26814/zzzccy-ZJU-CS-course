#include <stdio.h>
int main(void)
{    
    int a, b, maximum;
    int repeat, ri;
    int max(int a, int b);
   
    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d",&a, &b);
        maximum=max(a,b);
        printf("max(%d,%d) = %d\n", a, b, maximum);
    }
}
int max(int a, int b)
{
	int max;
	max=a;
	if(b>a)
	max=b;
	return max;
}
/*---------*/

