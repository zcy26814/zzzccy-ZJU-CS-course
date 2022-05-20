#include <stdio.h>
int main(void)
{
	int n, digit1, digit2, digit3;

		/*---------*/
	n = 152;
	digit1 = n % 10;
	digit2 = (n - digit1) / 10 % 10;
	digit3 = (n - digit1 - 10 * digit2) / 100 % 10;
	printf("整数%d的个位数字是%d, 十位数字是%d, 百位数字是%d\n", n, digit1, digit2, digit3);
	return 0;
}

