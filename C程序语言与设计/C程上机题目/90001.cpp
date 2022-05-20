#include <stdio.h>
int main (void)
{
    int i, n;
    double x;
    struct emp{
        char  name[10]; 
        double jbg;  
        double fdg;   
        double zc;
    } s[10];

    scanf("%d", &n);
    for(i=0;i<n;i++)
	{
		scanf("%s%lf%lf%lf",s[i].name,&s[i].jbg, &s[i].fdg, &s[i].zc);
		x=s[i].jbg + s[i].fdg - s[i].zc;
	} 
	 
    for (i = 0; i < n; i++)      
        printf ("%5s 实发工资：%7.2f\n", s[i].name, s[i].jbg + s[i].fdg - s[i].zc);
}  

