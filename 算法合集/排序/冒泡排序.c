#include<stdio.h>
#define n 10
void swap(int a[],int b, int c);
int main(){
    int a[n] = {2,5,3,7,8,6,4,1,0,9};
    int tmp;
    int i;
    for(i = 0; i < n; i++){ //10个元素总共需要9次排序
        for(int j = 0; j < n-i; j++){ //对于每个j与j+1个元素，如果a[j+1]小于a[j]，则交换顺序
            if(a[j] > a[j+1]){
                swap(a, j, j+1);
            }
        }
    }
    for(i = 0;i<10;i++) printf("%d", a[i]);
    return 0;
}

void swap(int a[],int b, int c){
    int tmp = a[b];
    a[b] = a[c];
    a[c] = tmp;
}