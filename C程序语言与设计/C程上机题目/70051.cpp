
#include <stdio.h>
int main( )
{
    int i, index, n, temp;
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
            	if(a[i]>=a[index])
            	index=i;
            }
            printf("max = %d, index = %d\n", a[index],index);
            temp=a[n-1];
            a[n-1]=a[index];
            a[index]=temp;
        for(i = 0; i < n; i++) 
            printf("%d ", a[i]);
        printf("\n");
    }
}
