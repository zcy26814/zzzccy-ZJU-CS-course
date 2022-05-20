#include <stdio.h>
int main(void)
{
    int a, i, n;
    int ri, repeat;
    long sn;
    long fn(int a, int n);

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%ld%d", &a, &n);
        sn=0;
        for(i=1;i<=n;i++)
        sn +=fn(a,i);
        printf("%ld\n", sn);
    }
}
long fn(int a, int n)
{
	int i, j, t, sum;
	sum=a;
	for(i=2;i<=n;i++)
	{
	t=a;
	for(j=1;j<=i-1;j++)
        {
          t *=10;
        }
    sum +=t;
    }
    return sum;
}
/*---------*/

