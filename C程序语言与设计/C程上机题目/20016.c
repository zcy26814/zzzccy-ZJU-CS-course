#include <stdio.h>
int main(void)
{
	int y;
	int x;
	/*---------*/

	x = 3;
	y = x*x;
	printf("%d = %d * %d\n", y, x, x);
	printf("%d * %d = %d\n", x,x,y);

	system("pause");
	return 0;
}
