#include<stdio.h>
#define n 10
void swap(int a[],int b, int c);
int main(){
    int a[n] = {2,5,3,7,8,6,4,1,0,9};
    int tmp;
    int i;
    for(i = 0; i < n; i++){ //10个元素总共需要9次选择排序
        for(int j = i+1; j <= n; j++){ //遍历i+1后的每一个元素，如果a[j]小于a[i]，则交换顺序
            if(a[i] > a[j]){
                swap(a, i, j);
            }
        }
    }
    for(i = 0; i < n; i++) printf("%d", a[i]);
    return 0;
}

void swap(int a[],int b, int c){
    int tmp = a[b];
    a[b] = a[c];
    a[c] = tmp;
}