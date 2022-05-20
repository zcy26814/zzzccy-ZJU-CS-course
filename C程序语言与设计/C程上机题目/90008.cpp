#include <stdio.h>
struct time{
    int hour, minute, second;
};
void timecal(struct time *p, int n);

int main(void)
{
    int n;
    int repeat, ri;
    struct time time;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d:%d:%d", &time.hour, &time.minute, &time.second);
        scanf("%d",&n);
        timecal(&time, n);
        printf("time: %d:%d:%d\n", time.hour, time.minute, time.second);
    }
}
void timecal(struct time *p, int n)
{
		(*p).second +=n;
		if((p->second)>=60)
		{
			p->minute = p->minute + p->second / 60;
			p->second %=60;	
		} 
		if((p->minute)>=60)
		{
			p->hour = p->hour + p->minute / 60;
			p->minute %=60;
		} 
		if((p->hour)>=24)
		{
			p->hour %=24;
		}
}
