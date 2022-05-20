#include<stdio.h>
struct condition{
	int obj1;	//用于存储输入的第一个字母- 'A'的值 
	int obj2;	//存储第二个字母的 
	int num;	//存储数字 
	int ret;	//是否是 =  
}condition[20];

int judge(int *a,int n);	//判断函数 

int main(void)
{
	int n;
	scanf("%d\n",&n);
	int i;
	char s[5];
	
	//录入数据 
	for(i=0; i<n; i++){
		gets(s);
		condition[i].obj1 = s[0] - 'A';
		if(s[1] != '='){
			condition[i].obj2 = s[2] - 'A';
			condition[i].num = s[3] - '0';
			condition[i].ret = 0;		//如果输入的不是 = 就ret录为1；		
		}
		else{
			condition[i].num = s[2] - '0';	
			condition[i].ret = 1;
		}
		if(s[1] == '<'){
			condition[i].num *= -1;		//如果是 < 存储的数字变为负； 
		}
		
	}

	//循环给数组赋值 0~6各种情况，在给判断函数判断是否符合输入的条件。 
	int day[7] ;	//值班顺序 ，下标表示 ABCDEFG，对应值表示时间。 
	int a,b,c,d,e,f,g;
	for(a=0; a<7; a++){
		for(b=0; b<7 ; b++){
			for(c=0; c<7 ; c++){
				for(d=0; d<7 ; d++){
					for(e=0; e<7 ; e++){
						for(f=0; f<7 ; f++){
							for(g=0; g<7 ; g++){
								day[0] = a;
								day[1] = b;
								day[2] = c;
								day[3] = d;
								day[4] = e;
								day[5] = f;
								day[6] = g;
								if(judge(day,n))	//判断是否符合输入的条件。 
									goto E;
							}
						}
					}
				}
			}
		}
	}
E:	
	if(judge(day,n)){
		char Day[8];
		for(i=0; i<7; i++){
			Day[day[i]] = i + 'A';	//把值班时间按顺序写入对应大夫 
		}
		Day[8] = '\0';
		puts(Day);
	}
	
	return 0;
}

int judge(int *a,int n){
	int i = 0;
	int ret = 1;
	
	//判断传入的值班日期与输入的条件是否符合。 
	for(i=0; i<n; i++)
	{
		//如果是 = ，就判断值班日期和条件日期-1是否相等 .（值班日期是从0开始算的） 
		if(condition[i].ret){
			if(a[condition[i].obj1] != condition[i].num - 1)
				ret = 0;
				break;
		} 
		else if(a[condition[i].obj1] + condition[i].num != a[condition[i].obj2]){
			ret = 0;
			break;
		}
	}
	return ret;
}
