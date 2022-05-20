#include "stdio.h"
int main(void)
{
    int i, j, n;
    int a[10][10]; 
    int repeat, ri;
 
    scanf("%d",&repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i=0;i<=n;i++)
        {
        	for(j=0;j<=n;j++)
        	{
				if(i != 0 || j != 0)
				{
					if(i==0 || j==0)
					a[i][j]=i+j;
					else a[i][j]=i*j;
				}
        	}
        	
        }
        for(i = 0; i <= n; i++){
            for(j = 0; j <= n; j++)
                if(i == 0 && j == 0) printf("%-4c", '*');
                else if(i == 0 || j <= i) printf("%-4d", a[i][j]);
            printf("\n");
        }
    }
}

