#include <stdio.h>
int main(void)
{
    char c;
    int blank, digit, letter, other;
    int ri, repeat;

    scanf("%d", &repeat);
    getchar();
    for(ri = 1; ri<=repeat; ri++){
        c = getchar();
        letter=digit=blank=other=0;
        while(c!='\n')
		{
        	if((c>='a'&&c<='z') ||(c>='A'&&c<='Z'))
			letter++;
			else if(c>='1'&&c<='9')
			digit++;
			else if(c==' ')
			blank++;
			else other++;
			c = getchar();
        }
        printf("letter = %d, blank = %d, digit = %d, other = %d\n", letter, blank, digit, other);
    }
}

