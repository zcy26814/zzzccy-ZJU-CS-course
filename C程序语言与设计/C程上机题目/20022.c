#include <stdio.h>
int main(void)
{
    int celsius, fahr;  

    scanf("%d",&fahr);
	celsius=5*(fahr-32)/9;
    printf("celsius = %d\n", celsius); 
	system("pause");
	return 0;
}

