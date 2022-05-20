#include <stdio.h>
int sign(int x);
int main(void)
{
    int x, y;
    int repeat, ri;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%d",&x);
        y=sign(x);
        printf("sign(%d) = %d\n", x, y);
    }
}

int sign(int x)
{
	if(x==0)return 0;
	else if(x>0)return 1;
	else return -1;
}

