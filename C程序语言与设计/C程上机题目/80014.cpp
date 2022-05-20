#include<stdio.h>
int main(void)
{
    int count, i, m, n, no;
    int num[50];
    int *p;

    scanf("%d%d", &n, &m);
    for(i = 0; i < n; i++)
        num[i] = i + 1;
    p = num;
    count=1;
    no=1;
    p=p+m-1;
    printf("No%d: %d\n", no, *p);
    *p=0;
    while(count<n-1)
    {
    	for(i=0;i<m;i++)
    	{
    		p++;
			if(p>num+n-1) 
			{
				p=num;
			}
    		while(*p==0)
    		{
    			p++;
				if(p>num+n-1) 
				{
					p=num;
				}
    		}
    			
    	}
		no++;
    	printf("No%d: %d\n", no, *p);
    	*p=0;
    	count++;
    }
    p = num;
    while(*p == 0)
        p++;
    printf("Last No is: %d\n", *p);
}

