#include <stdio.h>
#include <string.h>
int main(void)
{
    char sx[80], longest[80];
    int i, n;
    int repeat, ri;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        scanf("%s", sx);
        strcpy(longest,sx);
        for(i=1;i<n;i++)
        {
        	scanf("%s",sx);
        	if(strlen(sx)>strlen(longest))
        	{
        		strcpy(longest,sx);
        	}
        	
        }
        printf("The longest is: %s\n",longest);
}
}
