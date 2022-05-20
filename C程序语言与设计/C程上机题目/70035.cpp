#include "stdio.h"
#include "string.h"
#define MAXLEN 80
int main(void)
{  
    char ch;
    char str[MAXLEN], num[MAXLEN];
    int i, k;
    int repeat, ri;
    long number;

    scanf("%d", &repeat);
    getchar();
    for(ri = 1; ri <= repeat; ri++){
        i = 0;
        scanf("%s",str);
        number=0;
        k=0;
        for(i=0;str[i]!=0;i++)
        {
        	if((str[i]>='0'&&str[i]<='9')||(str[i]>='a'&&str[i]<='f')||(str[i]>='A'&&str[i]<='F'))
        	{
        	num[k]=str[i];
        	k++;
        	}
		}
		num[k]=0; 
		for(i=0;num[i]!=0;i++)
		{
			if(num[i]>='0'&&num[i]<='9')
			number=number*16+num[i]-'0';
			if(num[i]>='A' && num[i]<='F')
			number=number*16+num[i]-'A'+10;
			if(num[i]>='a' && num[i]<='f')
			number=number*16+num[i]-'a'+10;
		}
      	printf("Dec = %ld\n",number);
    }
}
