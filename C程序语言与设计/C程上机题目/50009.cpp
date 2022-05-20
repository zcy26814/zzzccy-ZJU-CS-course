#include "stdio.h"
#include "math.h"
double funcos(double e, double x);
int main(void)
{
    int repeat, ri;
    double e, sum, x; 

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%le%le", &e, &x);
        sum=funcos(e,x);
        printf("sum = %f\n", sum);
    }
}
double funcos(double e, double x)
{
	int i,flag,t;
	double sum, item,fact;
	
	sum=0;
	item=1;
	flag=1;
	t=0;
	while(1)
	{
		sum+=item;
		if(fabs(item)<e)break;
		flag=-flag;
		t +=2;
		fact=1;
		for(i=1;i<=t;i++)
		fact *=i;
		item=flag*pow(x,t)/fact;
	}
	return sum;
	
}
/*---------*/
