#include <stdio.h>
int main(void)
{
    int i, n;
    double average, sum;
    struct student{
        int num;
        char name[10];
        int score;
    }s[10];

    scanf("%d", &n);
    sum=0;
    for(i=0;i<n;i++)
	{
		scanf("%d%s%d", &s[i].num, s[i].name, &s[i].score);
		sum +=s[i].score;
	} 
	average=sum/n;
    printf("average: %.2f\n", average);
}
