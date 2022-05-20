#include <stdio.h>
#include <string.h>
int main(void)
{
    char str[80], max[80];
    int i;

    scanf("%s", str);
    strcpy(max,str);
	for(i=1;i<5;i++)
	{
		scanf("%s",str);
		if(strcmp(str,max)>0)
		{
			strcpy(max,str);
		}
	} 
    printf("Max is: %s\n", max);
}   
