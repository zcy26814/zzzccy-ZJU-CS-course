#include <stdio.h>
int main(void)
{
    int i, n, sum;
    int repeat, ri;
    int a[10];
    double aver;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
            sum=0;
            for(i=0;i<n;i++)
            {
				sum +=a[i];
            }
            aver=sum*1.0/n;
        printf("average = %.2f\n", aver);
    }
}
