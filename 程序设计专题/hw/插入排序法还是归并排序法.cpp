#include <stdio.h>
#include <string.h>

int Judge(int a[],int b[],int n) {//判断是插入还是归并段
    int i,flag=0,pos=0;
    for(i=1; i<n; i++) {
        if(b[i-1]<=b[i]) {
            flag=1;
        } else {
            pos=i;
            break;
        }
    }
    if(flag) {
        for(i=pos; i<n; i++) {
            if(a[i]!=b[i]) {
                pos=0;
                break;
            }
        }
    } else
        pos=0;
    return pos;
}
void NextInsertionSort(int a[],int pos,int n) {//下一次插入排序
    int i,tmp=a[pos];
    int index;
    for(i=0; i<pos; i++) {
        if(a[i]>tmp) {
            index=i;
            break;
        }
    }
    for(i=pos-1; i>=index; i--) {
        a[i+1]=a[i];
    }
    a[index]=tmp;
}
int k=0;
void Merge(int a[],int low,int high,int mid) {//两段归并成一段
    int i,j;
    int c[100]= {0};
    for(i=low; i<=high; i++) {
        c[i]=a[i];
    }
    i=low,j=mid+1;
    while(i<=mid&&j<=high) {
        if(c[i]<=c[j]) {
            a[k++]=c[i];
            i++;
        } else {
            a[k++]=c[j];
            j++;
        }
    }
    while(i<=mid) {
        a[k++]=c[i];
        i++;
    }
    while(j<=high) {
        a[k++]=c[j];
        j++;
    }


}
int GetMergeLen(int a[],int n) {//获得当前归并段的最大长度
    int i,j;
    for(j=2; j<=n; j*=2) {//j<=n
        for(i=j; i<n; i=i+2*j)//i<n
        {
            if(a[i-1]>a[i])
                break;
        }    
        if(i<n)
            break;
    }
    return j;
}
void NextMergeSort(int a[],int low,int high,int len) {//下一次归并
    int i;
    for(i=low; i<=high; i+=len) {
        int mid=(i+i+len-1)/2;
        if(i+len-1<=high) {
            Merge(a,i,i+len-1,mid);
        }
        else if(mid<high) {
            Merge(a,i,high,mid);
        }
    }

}
int main() {
    int n;
    scanf("%d",&n);
    int i;
    int a[n],b[n];
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    for(i=0; i<n; i++) {
        scanf("%d",&b[i]);
    }
    int pos=Judge(a,b,n);
    if(pos) {
        printf("Insertion Sort\n");
        NextInsertionSort(b,pos,n);
    } else {
        printf("Merge Sort\n");
        int len=2*GetMergeLen(b,n);//下一次归并段长度=当前归并段长度*2
        NextMergeSort(b,0,n-1,len);
    }
    for(i=0; i<n; i++) {
        if(i)
            printf(" ");
        printf("%d",b[i]);
    }
    return 0;
}
