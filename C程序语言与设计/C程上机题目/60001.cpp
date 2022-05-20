#include <stdio.h>
double fact(int n);
double multi(int n);	
int main(void)
{	
    int i; 
    int repeat, ri;
    double eps, sum, item;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%le", &eps);
        sum=0;
        item=1;
        i=1;
        while(1)
        {
        	sum +=item;
        	if(item<eps)break;
        	item=fact(i)/multi(2*i+1);
        	i++;
        }
        printf("PI = %0.5f\n", 2 * sum);
    }

}
double fact(int n)
{
	int i;
	double sum;
	sum=1;
	for(i=1;i<=n;i++)
	sum *=i;
	return sum;
}
double multi(int n)
{
	int i;
	double sum;
	sum=1;
	for(i=1;i<=n;i +=2)
	sum *=i;
	return sum;
}

