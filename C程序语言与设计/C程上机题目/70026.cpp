#include "stdio.h"
int main(void)
{
    int flag, i, j, k, row, col, n;
    int a[6][6];
    int repeat, ri;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
                
                for(i=0;i<n;i++)
                {
                	flag=1;
                	k=a[i][0];
                	col=0;
                	for(j=0;j<n;j++)
					{
						if(a[i][j]>k)
						{
							k=a[i][j];
							col=j;
						}
					} 
					for(j=0;j<n;j++)
					{
						
						if(i!=j && a[i][col]>=a[j][col])
						{
							flag=0;
							break;
						}
						
					}
					if(flag==1)
					{
						row=i;
						break; 
					} 
				} 
        if(flag != 0)
            printf("a[%d][%d] = %d\n", row, col,a[row][col]);
        else
            printf("NO\n");
    }
}
