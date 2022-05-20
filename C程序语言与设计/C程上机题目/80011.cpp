#include <stdio.h>
void mov(int *x, int n, int m);
int main(void)
{
    int i, m, n;
    int a[80];

    scanf("%d%d", &n, &m);
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
        mov(a, n, m);
    printf("After move: ");
    for(i = 0; i < n; i++)
         printf("%d ", a[i]);
    printf("\n"); 
}
void mov(int *x, int n, int m)
{
	int i, j, temp;
	
	for(j=0;j<m;j++)
	{
		for(i=n-1+j;i>=j;i--)
		{
			*(x+i+1)=*(x+i);
		}
	}
	for(i=0;i<m;i++)
	{
		*(x+i)=*(x+n+i);
	}
}

