#include<stdio.h>
int main(){
    int n;
    scanf("%d", &n);
    int hat[100][2];
    for(int i = 0; i < n; i++){
        scanf("%d", &hat[i][1]);
    }
    int pat[100][2];
    for(int i = 0; i < n; i++){
        scanf("%d", &pat[i][1]);
    }
    for(int i = 0; i < n; i++){
        int flag = 1;
        for(int j = 0; j < n; j++){
            if(hat[i][1] > hat[j][1]) flag++;
        }
        hat[i][2] = flag;
    }
    for(int i = 0; i < n; i++){
        int flag = 1;
        for(int j = 0; j < n; j++){
            if(pat[i][1] > pat[j][1]) flag++;
        }
        pat[i][2] = flag;
    }
    for(int j = 0; j < n; j++){
            if(hat[n-1][2] == pat[j][2]) printf("%d",j+1);
    }
    for(int i =n-2; i >= 0;i--){
        for(int j = 0; j < n; j++){
            if(hat[i][2] == pat[j][2]) printf(" %d", j+1);
        }
    }
}