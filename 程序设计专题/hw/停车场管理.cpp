#include<stdio.h>
#include<stdlib.h>
struct Space{
	int car;		//汽车编号 
	int into_time;	// 停入时间 
	char empty;		// 判断能否停车 “Y”可以，“N”不行。 
}space[10];
typedef struct infor{
	char state;		//状态 “A D E” 
	int car;		//编号 
	int time;		//时间 
	struct infor *next;
}Infor;
Infor *creat_infor();
int main(void)
{
	int n;
	scanf("%d",&n);
	int i;
	for(i=0; i<n; i++){
		space[i].empty = 'Y';
	} 
	
	// 创建链表 
	Infor *head = creat_infor();
	int cnt = 0; 		//记录停入车辆个数 
	int rret = 0;		//用于判断是否 waiting
	int out_time = 0;	//在a车要停入时没车位，b车出来后停入的 a车的时间改成b车出来的时间 
	
	Infor *p = head;
	while(p){
		if(p->state == 'A'){
			//寻找是否有空车位 
			for(i=0; i<n; i++){ 
				if(space[i].empty == 'Y'){
					//如果有空车位，判断out—time有没有被更改，被更改则说明上述情况 
					if(out_time){
						p->time = out_time;
						out_time = 0;	//使用完后改回0 
					}
					// 将车位信息改成该车的信息 
					space[i].car = p->car;
					space[i].into_time = p->time;
					space[i].empty = 'N';		//车位改为不能停车状态 
					p->state = '0'; 			// 改变此信息状态，不再处理。 
					printf("car#%d in parking space #%d\n",space[i].car,i+1);
					cnt++;						// 车辆停入，cnt加一 
					break;
				}
			}
			// i等于n说明循环结束没有找到空车位 
			if(i == n){
				printf("car#%d waiting\n",p->car);
				rret++;		//记录有车在等待。 
			}
		}else if(p->state == 'D'){
			int ret = 1;		//用于判断有停车位里有没有该车，1为没有 
			for(i=0; i<n; i++){
				if(space[i].car == p->car){
					printf("car#%d out,parking time %d\n",space[i].car,p->time-space[i].into_time);
					//如果cnt等于n就表面停车场停满了 ，rret 等于 1，则有车在等待入库，需要记录此车出去时间。 
					if(rret){
						out_time = p->time;
						p->state = '0'; // 改变此信息状态，不再处理。
						rret--;
						p = head;
					}
					cnt--;
					for(i; i<n-1; i++){
						space[i].car = space[i+1].car;
						space[i].empty = space[i+1].empty;
						space[i].into_time = space[i+1].into_time;
					}
					space[i].empty = 'Y';
					p->state = '0'; // 改变此信息状态，不再处理。 
					ret = 0;
					break;
				}
			}
			if(ret){
				printf("the car not in park\n");
			}
		}
		p = p->next;
	}
	return 0;
} 
//创建链表存储输入的信息 
Infor *creat_infor(){
	Infor *head = NULL;
	char state;
	int car;
	int time;
	do{
		fflush(stdin);//清空输入缓冲区，防止s吸收空格回车 
		scanf("%c",&state);
		scanf("%d%d",&car,&time);
		if(state != 'E'){
			Infor *p = (Infor*)malloc(sizeof(Infor));
			p->state = state;
			p->car = car;
			p->time = time;
			p->next = NULL;
			Infor *last = head;
			// 如果last不是空则表明head已经存入数据。 
			if(last != NULL){
				while(last->next){
					last = last->next;
				}
				last->next = p;
			}else{
				head = p;
			}			
		}		
	}while( state != 'E');
	return head;
} 
