#include <stdio.h>
#include <math.h>
int main(void)
{
    int repeat, ri;
    double x, y;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++){
           scanf("%lf",&x);
		if(x>=0){
	    y=sqrt(x);
		}
		else{
			y=pow(x+1,2) + 2*x + 1/x;
		}
        printf("f(%.2f) = %.2f\n", x, y);	
    }
    
	system("pause");
	return 0;
}
