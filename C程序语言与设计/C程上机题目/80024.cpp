#include<stdio.h>
#include<string.h>
int main()
{
    char s[80], t[80];
    int m;
    int repeat, ri;
    void strmcpy(char *s,char *t, int m);

    scanf("%d", &repeat);
    getchar();
    for(ri = 1; ri <= repeat; ri++){
        gets(t);
        scanf("%d", &m);
        getchar();
        if(strlen(t) < m)
            printf("error input");
        else{
        	strmcpy(s,t,m);
            puts(s);
        }
    }
}
void strmcpy(char *s,char *t, int m)
{
	strcpy(s,t+m-1);
	
}
