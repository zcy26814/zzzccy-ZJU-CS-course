#include <stdio.h>
int main(void)
{
    int i, index, k, n, temp;
    int repeat, ri;
    int a[10];

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
            for(k=0;k<n;k++)
            {
            	index=k;
            	for(i=k+1;i<n;i++)
				{
					if(a[index]<a[i])
					{
						index=i;
					} 
				} 
				temp=a[k];
				a[k]=a[index];
				a[index]=temp;
            }
        printf("After sorted: ");
        for(i = 0; i < n; i++) 
            printf("%d ", a[i]);
        printf("\n");
    }
}
