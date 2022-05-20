#include<stdio.h>
int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    int i = 0;
    int ini[200];
    while(i < N){
        scanf("%d", &ini[i]);
        i++;
    }
    int j =0;
    int tmp[200];
    int a[200];
    while(j < K){
        int l = 0;
        while(l < N){
            scanf("%d", &tmp[l]);
            l++;
        }
        int count = 0;
        for(int q = 0; q < N; q++){
            for(int p = q; p < N; p++){
                if(tmp[q] > tmp[p]) count++;
            }
        }
        if(count%2) a[j] = 1;
        else a[j] = 0;
        j++;
    }
    int m = 0;
    while (m < K)
    {
        if(a[m]) printf("no\n");
        else printf("yes\n");
        m++;
    }    
}