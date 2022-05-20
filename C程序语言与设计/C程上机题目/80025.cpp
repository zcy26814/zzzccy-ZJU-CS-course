#include <stdio.h>
int main()
{
    char s[80];
    int repeat, ri;
    int mirror(char *p);
 
    scanf("%d", &repeat);
    getchar();
    for(ri = 1; ri <= repeat; ri++){
        gets(s);
        if(mirror(s) != 0)
      	    printf("YES\n");
        else
            printf("NO\n");
    }
}
 int mirror(char *p)
 {
 	int i,count,r;
 	
 	i=0;
	 while(p[i]!=0)
	 {
	 	i++;
	 } 
	 count=i;
	 r=1;
	 for(i=1;i<count/2;i++)
	 {
	 	if(p[i]!=p[count-i-1])
	 	{
	 		r=0;
	 		break;
	 	}
	 }
	 return r;
 }
