#include<stdio.h>
#include<math.h>



    int k;
    int a[1001];
    int b[1001];
    
    int n;
    int root;
void BuildCBT(int root);
int main(){
    int i;
    scanf("%d", &n);
    for(i = 1; i<=n;i++){
        scanf("%d", &a[i]);
    }
    int tmp;
    for (int j=1;j<n;j++){
        for (i=1;i<n-j+1;i++){
            if(a[i]>a[i+1]){
                tmp=a[i];
                a[i]=a[i+1];
                a[i+1]=tmp;
            }
        }
    }
    BuildCBT(1);
    for(i = 1; i<n;i++){
        printf("%d ", b[i]);
    }
    printf("%d\n", b[n]);
}

void BuildCBT(int root){
    if(root > n) return;
    BuildCBT(root * 2);
    b[root] = a[++k];
    BuildCBT(root * 2 + 1);
}