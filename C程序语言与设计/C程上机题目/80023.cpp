#include<stdio.h>
void main()
{
    char c;
    char str[80];
    int repeat, ri;
    void delchar(char *str, char c);

    scanf("%d", &repeat);
    getchar();
    for(ri = 1; ri <= repeat; ri++){
        gets(str);
        scanf("%c", &c);
        getchar();
        delchar(str,c);
        printf("result: ");
        puts(str);
    }
}
void delchar(char *str, char c)
{
	int i,j,count;
	
	i=0;
	count=0;
	while(str[i]!=0)
	{
		if(str[i]==c)
		{
			str[i]='1';
		}
		i++;
		count++;
	}
	i=0;
	while(str[i]!=0)
	{
		if(str[i]=='1')
		{
			for(j=i;j<count;j++)
			{
				str[j]=str[j+1];
			}
		}
		if(str[i]!='1')
		{
			i++;
		}
	}
	
}
