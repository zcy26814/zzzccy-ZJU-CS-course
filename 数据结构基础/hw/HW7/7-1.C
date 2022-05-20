#include<stdio.h>
#include<stdlib.h>

int main(){
    char result[100][4];
	int computer[20000];
    int N, i, count = 0;
    scanf("%d",&N);//总电脑数 
    for(i=1;i<=N;i++)
        computer[i]=-1;//数据初始化，每个元素对应自己的位置
	while(1){
		char input;
		scanf("%c", &input);
		switch(input){
			case 'I':
				{
					int a, b;
					scanf("%d %d", &a, &b);
					int father, son, rootofa, rootofb;
					for (rootofa = a; computer[rootofa] > 0; rootofa=computer[a]);  
					for (rootofb = b; computer[rootofb] > 0; rootofb=computer[b]);  
					if((-computer[rootofa])>=(-computer[rootofb])){
						father = rootofa;
						son = rootofb;
					}
					else{
						father = rootofb;
						son = rootofa;
					}
					computer[son]=father;
					computer[father]--;
					
					int trail, lead, root;
					for ( trail = son; trail != father; trail = lead ){
      					lead = computer[trail];   
    					computer[trail]=father;   
					} 
					break;
				}
			case 'C':
				{
					int c, d;
					int testc, testd;
					scanf("%d %d", &c, &d);
					for(testc = c; computer[testc]>0; testc = computer[testc]);
					for(testd = d; computer[testd]>0; testd = computer[testd]);
					if(testc == testd) strcpy(result[count++],"yes");
					else strcpy(result[count++],"no");
					break;
				}
			case 'S':
				goto Continue;
			default:
				break;
		}
			
	}
    Continue:
	    strcpy(result[count],"\0");
	    for(count=0; *result[count]!='\0'; count++){
		    printf("%s\n", result[count]);
	    }
	
	/*检验连通区域*/
	int liantong = 0;
	for(i=1;i<=N;i++){
		if(computer[i]<0) liantong++;
	} 
    if(liantong == 1)
    	printf("The network is connected.");
    else
    	printf("There are %d components.", liantong);
    return 0;
}