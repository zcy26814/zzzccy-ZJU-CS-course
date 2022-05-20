#include <stdio.h> 
int main(void)
{
    int i, j, temp;
    char str[80];		

    i = 0;
    while((str[i] = getchar( )) != '\n') 
        i++; 
    str[i] = 0; 
    j=i;
	for(i=0;i<j/2;i++)
	{
		temp=str[i];
		str[i]=str[j-1-i];
		str[j-1-i]=temp;
	}     
    for(i = 0; str[i] != 0; i++) 
        putchar(str[i]);
}
