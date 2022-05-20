#include<stdio.h>
int main()
{
	char a[10000],b;
	int c=0,d=0,i;
	gets(a);
	for(i=0;(b=a[i])!='\0';i++){
		if(b==' '){
			d=0;
		} 
		else if(d==0){
			d=1;
			c++;
		}
		} 
		printf("%d",c);
		return 0;
} 
