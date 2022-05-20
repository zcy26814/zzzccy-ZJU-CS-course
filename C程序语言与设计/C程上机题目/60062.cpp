#include <stdio.h>
int multi(int s1, int s2, char t);
int main(void)
{
    char operato;
    int operand1, operand2, res;
    int repeat, ri;

    scanf("%d", &repeat);
    for(ri = 1; ri <= repeat; ri++)
	{
        scanf("%d", &operand1);
        operato= getchar();
        while(operato!='=') 
		{
        scanf("%d", &operand2);
        operand1=multi(operand1,operand2,operato);
        operato=getchar();
        }
		res=operand1;
		printf("%d\n", res);  
    }
}
int multi(int s1, int s2, char t)
{
	int sum;
	
	switch(t)
	{
	case '+':sum=s1+s2;break;
	case '-':sum=s1-s2;break;
	case '*':sum=s1*s2;break;
	case '/':sum=s1/s2;break;
	}
	return sum; 
}
