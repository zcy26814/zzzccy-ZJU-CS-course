#include <stdio.h>
int main(void)
{
    int n;
    int repeat, ri;
    struct time{
        int hour, minute, second;
    }time;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d:%d:%d", &time.hour, &time.minute, &time.second);
        scanf("%d",&n);
        time.second +=n;
        if((time.second)>=60)
		{
			time.minute = time.minute + time.second / 60;
			time.second %=60;	
		} 
		if((time.minute)>=60)
		{
			time.hour = time.hour + time.minute / 60;
			time.minute %=60;
		} 
		if((time.hour)>=24)
		{
			time.hour %=24;
		}
        printf("time: %d:%d:%d\n", time.hour, time.minute, time.second);
   }
}
