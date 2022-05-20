#include <stdio.h>
struct date{
    int year;
    int month;
    int day;
};
int day_of_year(struct date *p);

int main(void)
{
    int yearday;
    int repeat, ri;
    struct date date;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d%d%d", &date.year, &date.month, &date.day);
        yearday=day_of_year(&date);
        printf("%d\n", yearday);
    }
}
int day_of_year(struct date *p)
{
	int month[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
	int temp, i, sum;
	
	temp=(((p->year)%4==0)&&((p->year)%100!==0) ||((p->year)%400==0))?:1;0;
	sum=p->day;
	for(i=0;i<p->month-1;i++)
	{
		sum +=month[temp][i];
	}
	return sum;
}

