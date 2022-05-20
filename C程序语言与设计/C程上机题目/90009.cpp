#include <stdio.h>
int main (void)
{  
    int i, j, k, max_index, n;
    struct student{
        int number;
        char name[20];
        int score[3];
        int sum;
    }stu[10];

    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
    	scanf("%d%s%d%d%d", &stu[i].number, stu[i].name, &stu[i].score[0], &stu[i].score[1], &stu[i].score[2]);
    	stu[i].sum=stu[i].score[0]+stu[i].score[1]+stu[i].score[2];
    }
    max_index=0;
    for(i=1;i<n;i++)
    {
    	if(stu[i].sum>stu[max_index].sum)
    	max_index=i;
    }
    printf("总分最高的学生是: %s，%d分\n", stu[max_index].name, stu[max_index].sum);
}

