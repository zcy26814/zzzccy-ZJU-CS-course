#include "stdio.h"
int main(void)
{
    int day, day_year, month, year;
    int repeat, ri;

    int day_of_year(int year, int month, int day);

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d%d", &year, &month, &day);
        day_year=day_of_year(year, month, day);
        printf("days of year: %d\n", day_year);
    }
}
int day_of_year(int year, int month, int day)
{
	int i, j, sum;
	int a[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if((year%4==0 &&year%100!=0)||year%400==0)
	{
		a[1]=29;
	}
	sum=0;
	for(i=0;i<month-1;i++)
	sum +=a[i];
	sum +=day;
	return sum;
}
