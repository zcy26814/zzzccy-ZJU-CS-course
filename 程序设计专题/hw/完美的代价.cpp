 #include<stdio.h>  
 #include<stdlib.h>  
 int main(){  
     int i,j,l,n,k,sum=0,flat=1,c=-1;
     char *a;
     scanf("%d",&n);
     a=(char *)malloc(n*sizeof(char));
     scanf("%s",a);
     j=n-1;  
     //利用贪心的思想，将每个遍历的字符找到后面与他相同的然后交换到正确的位置时所需的交换次数   
     for(i=0;i<j;i++){
         for(k=j;k>=i;k--){
             if(k==i){//说明没有找到与a[i]相同的字符   
                 if(n%2==0||c!=-1){//如果n为偶数或者a[i]不是唯一一个单个无相同字符   
                     flat=0;
                     break;
                 }
                 c=1;//n为奇数，将第一个单个的字符a[i]移到中间位置所需的交换次数   
                 sum=sum+n/2-i;
                 break;
             }
             if(a[k]==a[i]){
                 for(l=k;l<j;l++){  
                     a[l]=a[l+1];  
                 }  
                 a[j]=a[i];  
                 sum=sum+j-k;  
                 j--;  
                 break;  
             }  
         }  
         if(flat==0){
             break;
         } 
     }  
     if(flat==0)
         printf("Impossible");
     else if(sum==0)
         printf("0");
     else 
         printf("%d\n",sum);
     return 0;  
}