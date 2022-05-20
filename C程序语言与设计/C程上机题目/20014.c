#include <stdio.h>
int main(void)
{
	int math, eng, comp, average;

	/*---------*/
	math = 87; 
	eng = 72; 
	comp = 93;
	average = (math + eng + comp) / 3;
	printf("math = %d, eng = %d, comp = %d, average = %d\n", math, eng, comp, average);
	return 0;
}
