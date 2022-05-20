#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include "strlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>


#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"
#include "x.h"

linklist *Newlink(void)
{
	linklist *head;
	
	head = (linklist *)malloc(sizeof(linklist));//创建头结点 
	head->dataptr = NULL;
	head->next = NULL;
	return head;
}

void Insert(linklist *head, linklist *p, void *q)
{
	linklist *ptr;
	
	if (q == NULL);//若数据不存在，则不插入
	else{
		if (p == NULL){//插入的新结点为空
		    p = head;
		    while (p->next != NULL) p = p->next;//找到链表的尾节点
	    }
	    ptr = (linklist *)malloc(sizeof(linklist));//创建新结点成为尾节点 
	    ptr->dataptr = q;
	    ptr->next = p->next;
	    p->next = ptr;
	}
}

void travel(void)
{
	travellink(list[Rectangle], DrawRectangle);
	travellink(list[Roundedrectangle], DrawRoundedrectangle);
	travellink(list[Rhombus], DrawRhombus);
	travellink(list[CenteredEllipse], DrawCenteredEllipse);
	travellink(list[Arrow], DrawArrow);
	travellink(list[Line], DrawLine1);
	travellink(list[Parallelogram], DrawParallelogram);
	travellink(list[Text], DrawText1);
}

void travellink(linklist *head, void (*traveler)(void *p))
{
	linklist* q;
	
	if (traveler == NULL);//绘制函数为空 
	if (head->next == NULL);//链表中无图形数据 
	else{
		q=head->next;
	    while (q != NULL)//循环绘制所有图形 
	    {
		   (*traveler)(q->dataptr);
		   q = q->next;
	    }
	}
}

linklist *Next(linklist *p)
{
	if (p != NULL) return p->next;//返回下一个结点 
	return NULL;
} 

void *Node(linklist *p)
{
	if (p != NULL) return p->dataptr;//返回当前结点的数据 
	return NULL;
}

void Deletelink(void)
{
	int i;
	for (i=0;i<NLIST;i++){
		if (list[i]->next!=NULL)
		   list[i]->next=NULL;
	}
}
