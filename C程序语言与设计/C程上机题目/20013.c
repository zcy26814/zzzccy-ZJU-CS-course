#include <stdio.h>
int main(void)
{
	int celsius, fahr;

	/*---------*/
	celsius = 26; 
	fahr = 9*celsius/5+32;

	printf("celsius = %d, fahr = %d\n", celsius, fahr);
	return 0;
}
