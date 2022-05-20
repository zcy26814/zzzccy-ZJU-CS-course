#include<stdio.h>
int main()
{
	double a,b;
	char d;
	scanf("%lf%c%lf",&a,&d,&b);
	switch(d){
	case '+':printf("%lf",a+b); break;
	case '-':printf("%lf",a-b);	break;
	case '*':printf("%lf",a*b);	break;
	case '/':if(b!=0){
		printf("%lf",a/b);
	}
	else{
		printf("Divisor can not be 0!");
	}
	break;
	default :printf("Unknown operator!");break;
	}
	return 0;
}