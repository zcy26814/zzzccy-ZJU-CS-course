#include<stdio.h>
#include<string.h>
int main(void)
{   char *color[5] = {"red", "blue", "yellow", "green", "black"}; 
    char **pc;  /* 定义二级指针变量 */
    char str[20];  int i;
    pc = color;   /* 二级指针赋值 */
    scanf("%s", str);
    for(i = 0; i < 5; i++)  
       if(strcmp(str, *(pc+i)) == 0)  /* 比较颜色是否相同 */
            break;
    if(i < 5)
        printf("%d\n", i+1);
    else
        printf("Not Found\n");    
    return 0;
}
