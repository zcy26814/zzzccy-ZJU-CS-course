#include <stdio.h>
int main(void)
{
    int repeat, ri;
    double x, y;  

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
        scanf("%lf", &x);
        if(x==0){
			y=0;}
		else{y=1/x;
	}
        printf("f(%.2f) = %.1f\n", x, y);	
     }
	system("pause");
	return 0;
}

