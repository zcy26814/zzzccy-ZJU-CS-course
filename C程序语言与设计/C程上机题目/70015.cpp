#include <stdio.h>
int main(void)
{
    int i, index, n, t;
    int repeat, ri;
    int a[10];

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
            index=0;
            for(i=1;i<n;i++)
            {
            	if(a[i]<a[index])
            	{
            		index=i;
            	}
            }
            t=a[0];
            a[0]=a[index];
            a[index]=t;
            index=1;
            for(i=2;i<n;i++)
            {
            	if(a[i]>a[index])
            	{
            		index=i;
            	}
            }
            t=a[n-1];
            a[n-1]=a[index];
            a[index]=t;
        printf("After swap: ");
        for(i = 0; i < n; i++) 
            printf("%d ", a[i]);
        printf("\n");
    }
}

