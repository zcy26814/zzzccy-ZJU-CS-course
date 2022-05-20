#include <stdio.h>
int main()
{
    int i,j;
    char a[4][100],s[20];
    for(j=0;j<4;j++) {
    	scanf("%s",&a[j]);
	}
	for(i=0;i<4;i++){
		s[i*2]=a[i][0];
        s[i*2+1]=a[i][1];
	}
    s[i*2]='\0';
    printf("%s",s);
    return 0;
}
