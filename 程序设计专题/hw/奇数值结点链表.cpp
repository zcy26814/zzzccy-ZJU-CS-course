#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *getodd( struct ListNode **L );
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
    struct ListNode *L, *Odd;
    L = readlist();
    Odd = getodd(&L);
    printlist(Odd);
    printlist(L);

    return 0;
}
struct ListNode *readlist()
{
	struct ListNode *head=NULL,*p,*last;
    int n;
	last=head;    //last指针用于移动表示链表末尾 
	do{
		scanf("%d",&n);    //输入结点数值 
		if(n!=-1)
		{
			p=(struct ListNode *)malloc(sizeof(struct ListNode));    //申请新节点 
			p->data=n;    //新节点赋值 
			p->next=NULL;     //新节点指空 
			if(last==NULL)    //若为头结点时 
				head=p;
			else
				last->next=p;    //非头结点时，尾接 
			last=p;    //标志位移动到新节点处		
		}
		else
			break;	
	}while(n!=-1);
		return head;
				
}

struct ListNode *getodd( struct ListNode **L )
{
	//奇数分离构成新链表，返回删除奇数的链表的头结点 
	struct ListNode *odd=NULL,*last,*p,*q,*k;
	last=odd;  //用于奇数链表链表 插入新节点
	p=*L;    //表示原链表移动指针 
	q=NULL; //q初始化，作为原链表移动指针前一个节点的标记 
	while(p)
	{
		if((p->data)%2) //data取余2为 1 则为奇数，删除节点 
		{
			if(q&&p!=*L) //非L收个节点就是奇数的情况 
			{
				k=p; //保存奇数节点 
				q->next=p->next; //删除奇数节点 
				
				if(last!=NULL)    //插入odd链表 
					last->next=k;
				else
					odd=k;
				last=k;		
			}	
			else //L的第一个就是奇数的情况  
			{ 
				k=p;              //保存奇数节点 
				*L=p->next;       //头结点向后移动，删除奇数节点 
				
				if(last!=NULL)    //插入odd链表 
					last->next=k;
				else
					odd=k;
				last=k;		
			}
		}
		else
			q=p; //未找到奇数节点，则用q保留当前位置 		 
		p=p->next; //p指针继续向下移动
        if(last) //odd链表非空则
		    last->next=NULL;  //odd末尾指针指空 
	} 
	return odd;		
}
