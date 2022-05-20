#include <stdio.h>
#include <math.h>
int main(void)
{
    int money, year;
    double interest, rate;

	scanf("%d",&money);
    scanf("%d",&year);
	scanf("%lf",&rate);
    interest = money*pow(1+rate,year) - money;
    printf("interest = %.2f\n", interest); 
	system("pause");
	return 0;
}
