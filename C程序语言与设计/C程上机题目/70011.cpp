#include <stdio.h>
int main(void)   
{
    int i, j, n, x;
    int repeat, ri;
    int a[10];

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
        scanf("%d", &x);
        for(i=n-1;i>=0;i--)
        {
        	a[i+1]=a[i];
        }
        a[0]=x;
        for(i=1;i<=n;i++)
        {
        	if(x>a[i])
        	{
        		a[i-1]=a[i];
        		a[i]=x;
        	}
        	else break;
        }
        for(i = 0; i < n + 1; i++)
            printf("%d ", a[i]);
        putchar('\n');   
    }
}


