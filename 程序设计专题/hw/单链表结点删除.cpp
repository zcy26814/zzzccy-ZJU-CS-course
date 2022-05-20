#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *deletem( struct ListNode *L, int m );
void printlist( struct ListNode *L )
{
     struct ListNode *p = L;
     while (p) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("\n");
}

int main()
{
    int m;
    struct ListNode *L = readlist();
    scanf("%d", &m);
    L = deletem(L, m);
    printlist(L);

    return 0;
}

struct ListNode *readlist()
{
	//---**尾插法**--- 
	//定义3个指针变量
	//head用于返回链表的首结点，先初始化指空
	//p 用于申请新节点 
	//last 用于连接head和新节点的一个尾指针，并且每次都停留在链表结尾 
	struct ListNode *head=NULL,*p,*last;
	int n;
	//先把last指向head ，起始时首尾都在一起 
	last=head; 
	do{
		//输入节点信息 
		scanf("%d",&n);
		//输入值！= -1时 操作 
		if(n!=-1)
		{
			//---申请新节点--- 
			p=(struct ListNode *)malloc(sizeof(struct ListNode));
			p->data=n;
			p->next=NULL; //申请的新节点初始化，下一个节点指空 
			
			//---连接节点----
			//head需要返回，不能用来移动，当检测到尾指针指空，表示首尾指针并未有任何值 
			if(last==NULL)
				head=p; //直接把第一个节点赋值到head   
			else
				last->next=p;  //若last非空 则把p连接到last后一个节点 head->last->p->null; 
			last=p; //连接完后last移动到到p上，既移动到新的结尾 	head->last->p1->last(p)->null;
		}
		else  
			break;
    	}while(n!=-1);// -1结束循环 
	return head;
				
}

struct ListNode *deletem( struct ListNode *L,int m )
{
    //--由于单链表遍历是不可逆的---
	//设置两个指针一个控制移动，一个用于连接（防止断链）
	struct ListNode *p,*q;
    p=L;  //p用于移动 
    q=NULL;  //q初始化 
    //当p非空时 
    while(p)
    {
		//若data为m 
		if(p->data==m)
    	{
    		//情况1：中间节点或者末尾节点是m ，此时 q!=NULL    
			if(q)
				q->next=p->next;    //q->m(p)->x    q->x			
			//情况2:首节点就是m ，此时 q=NULL 
			else
				L=p->next; //则直接移动链表的首结点后移 
		}
		else//data不为m，则q移动到p当前位置，相当于记录p前一个节点 
			q=p;
			
		//p指针移动到下一个节点	
    	p=p->next;
	}
    return L;
}
