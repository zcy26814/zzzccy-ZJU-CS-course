#include <stdio.h>
#include <math.h>
#define MAXH 505
#define MAXN 505

/*
注意重点h是黑高，n是内点个数 
BlackRoot[h][n] 表示root为黑色的红黑树，黑高为h,内节点为n能组成的不同红黑树种类
RedRoot[h][n] 表示root为红色的红黑树，（即root为红色，其他条件均和普通红黑树一样，被认可为特殊红黑树）黑高为h,内节点为n能组成的不同红黑树种类 
*/ 
int BlackRoot[MAXH][MAXN]={0};
int RedRoot[MAXH][MAXN]={0}; 
int mod = 1000000007;

int main(){
	int answer=0;//最后输出答案个数 
	int n, low, high;
    scanf("%d", &n);
    //已知条件，类似于数列首几项，又已知数列递推公式，递推得最后结果 
    //n为1或2的以红根或黑根各自的种类数 
    //注意此处谈论的黑高均包括叶子节点两个空孩子的黑高（*重点） 
    BlackRoot[2][1] = 1;//根为黑色树按照上述黑高定义黑高最小也为2 
	BlackRoot[2][2] = 2;
    RedRoot[1][1] = 1;
    
	//从n(内节点)为3开始递推
	for(int i=3;i<=n;i++){
		//考虑收缩范围以降低复杂度，内点数为n，黑高最小为log2(n+1)/2,最大为log2(n+1)*2
		int low=log2(i+1)/2;
		int high=log2(i+1)*2;
		for(int j=low;j<high;j++){//遍历高度 
			for(int k=1;k<i-1;k++){//遍历左子树内点数 
				BlackRoot[j][i]+= ((BlackRoot[j-1][k]+RedRoot[j-1][k])*(BlackRoot[j-1][i-k-1]+RedRoot[j-1][i-k-1]))%mod;
				RedRoot[j][i]+=BlackRoot[j][k]*BlackRoot[j][i-k-1]%mod;
				BlackRoot[j][i]%=mod;
				RedRoot[j][i]%=mod;
			} 
		}
	} 
    
    for(int i = 2; i < 30; ++ i)//黑色根黑高最少为2 
        answer = (answer + BlackRoot[i][n])%mod;
    printf("%d", answer);
} 

