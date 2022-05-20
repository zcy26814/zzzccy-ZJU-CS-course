#include <stdio.h>
int main(void)
{
    char c;
    int count, word;
    int repeat, ri;

    scanf("%d", &repeat);
    getchar();
    for(ri = 1; ri <= repeat; ri++){
        c = getchar();
        
        count=0;
        while(c!='\n')
        {
        	word=c;
        	c = getchar();
			if(c==' '&&word!=' ') 
			{
				count++;
			}
		} 
		if(word!=' ') 
		{
			count++;
		}
        printf("count = %d\n", count);
    }
}
