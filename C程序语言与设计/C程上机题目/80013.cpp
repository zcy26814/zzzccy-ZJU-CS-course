#include <stdio.h>
void sort(int a[],int n);
int main(void)
{
    int i, n;
    int repeat, ri;
    int a[10];

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
            sort(a,n);
        printf("After sorted: ");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
}
void sort(int a[],int n)
{
	int i, k, index,temp;
	
	for(k=0;k<n;k++)
	{
		index=k;
		for(i=k+1;i<n;i++)
		{
			if(a[i]<a[index])
			{
				index=i;
				temp=a[k];
				a[k]=a[index];
				a[i]=temp;
			}
		}
	}
}
