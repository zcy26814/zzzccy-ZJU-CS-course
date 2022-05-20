/* 题目1 */

#include "graphics.h"
#include "genlib.h"
#include "conio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

/*
 * 常量宏定义 
 * ---------- 
 *定义画房子的各种数据大小 
 */

#define HouseHeight         2.5
#define HouseWidth          2.0
#define AtticHeight         2.0

#define DoorWidth           0.5
#define DoorHeight          1.8

#define PaneHeight          0.5
#define PaneWidth           0.4

#define WindowsWidth        0.3
#define WindowsHeight       1.25

#define Chimney1Height      0.8
#define Chimney2Height      0.1
#define Chimney2Width       0.4

#define deltax1             0.2
#define deltax2             0.1
#define deltay              0.4

/* 定义画房子所需各类函数 */
 
void DrawHouse(double x, double y);/* 定义画房子的函数 */
void DrawOutline(double x, double y); /* 定义画房子轮廓的函数 */
void DrawWindows(double x, double y);/* 定义画窗的函数 */
void DrawDoor(double x, double y); /* 定义画门的函数 */
void DrawBox(double x, double y, double width, double height);/* 定义画方格的函数 */
void DrawTriangle(double x, double y, double base, double height);/* 定义画屋顶的函数 */

/* 以下为主程序 */

void Main()
{
    double cx, cy;

    InitGraphics();/*图形初始化*/
    cx = GetWindowWidth() / 2;
    cy = GetWindowHeight() / 2;
    DrawHouse(cx - HouseWidth / 2, cy - (HouseHeight + AtticHeight) / 2);
}

/* 作用：画房子 */ 

void DrawHouse(double x, double y)
{
    DrawOutline(x, y);
    DrawDoor(x + HouseWidth / 2, y);
    DrawWindows(x, y);
    DrawChimney1(x, y);
    DrawChimney2(x, y);
}

/* 作用：画方格 */

void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

/* 作用：画房子轮廓 */

void DrawOutline(double x, double y)
{
    DrawBox(x, y, HouseWidth, HouseHeight);
    DrawTriangle(x, y + HouseHeight, HouseWidth, AtticHeight);
}

/* 作用：画门 */

void DrawDoor(double x, double y)
{
    DrawBox(x, y, DoorWidth, DoorHeight);
}

/* 作用：画窗 */

void DrawWindows(double x, double y)
{
    DrawBox(x + WindowsWidth, y + WindowsHeight, PaneWidth, PaneHeight); 
}


/* 作用：画三角形 */

void DrawTriangle(double x, double y, double base, double height)
{
    MovePen(x, y);
    DrawLine(base, 0);
    DrawLine(-base / 2, height);
    DrawLine(-base / 2, -height);
}

/* 作用：画烟囱；烟囱一共有两部分 */

DrawChimney1(double x, double y)
{
	MovePen(x + deltax1, y + HouseHeight + deltay);
	DrawLine(0, Chimney1Height);
	DrawLine(deltax1, 0);
	DrawLine(0, -Chimney1Height/2);
}

DrawChimney2(double x, double y)
{
	DrawBox(x + deltax2, y + HouseHeight + deltay + Chimney1Height, Chimney2Width, Chimney2Height);
}





/* 题目2 */

#include "graphics.h"
#include "extgraph.h" 
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include "random.h"
#include "strlib.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

/* 宏定义常量π */
 
#define  PI     3.1415926

/* 定义所需函数 */
 
void forward(double distance);/* 定义画线段的函数 */
void turn(double angle); /* 定义旋转的函数 */
void move(double distance);/* 定义移动笔端的函数 */
void DrawHexagonal(double x, double y); /* 定义画六边形的函数 */
 
double theta = 0;/* 初始化角度为0 */

/* 以下为主程序 */
 
void Main()
{ 
    InitGraphics(); /*图形初始化*/

    DefineColor("DeepGreen", 0, 0.49, 0);/* 自定义深绿色 */
    SetPenColor("DeepGreen");/* 作用：把画笔颜色换成深绿色 */
   
    double cx, cy;
    int i=0;

    cx = GetWindowWidth()/2;
    cy = GetWindowHeight()/2;

   
/* 画图思路：图形为一个正六边形绕一个端点旋转20°,共旋转18次而成 */

    for(i=0;i<18;i++){ 
        DrawHexagonal(cx, cy);
        theta += 20;
    } 
}

/* 作用：画直线 */ 
void forward(double distance)
{
	DrawLine(distance*cos(theta/ 180 * PI), distance*sin(theta/ 180 * PI));
}

/* 
 *angle为正值，表示角的终边逆时针旋转 
 *----------------------------------- 
 * 作用：进行旋转 
 */
 
void turn(double angle)
{
	theta += angle;
}

/* 作用：移动画笔的笔端*/
 
void move(double distance)
{
	MovePen(distance*cos(theta/ 180 * PI), distance*sin(theta/ 180 * PI));
}

/* 作用：画六边形 */

void DrawHexagonal(double x, double y)
{
	double line = 1.5;
	MovePen(x,y);
	turn(60);
	forward(line);
	turn(-60);
	forward(line);
	turn(-60);
	forward(line);
	turn(-60);
	forward(line);
	turn(-60);
	forward(line);
	turn(-60);
	forward(line);
}





/* 题目3 */

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

int cx,cy;

bool inBox(double x0, double y0)
{
	return(x0 > 0 && x0 < cx && y0 > 0 && y0 < cy);
}

void MouseEventProcess(int x, int y, int button, int event)/*鼠标消息回调函数*/
{
	static double lx=0.0, ly=0.0;
	double mx,my;
	
	/* 作用：将像素转化为英寸 */
	
	mx = ScaleXInches(x);
	my = ScaleYInches(y) ;
	
	static bool isDraw = FALSE;
	
	switch(event){
		case BUTTON_DOWN:/* 按下鼠标的情况 */
		    if (button == LEFT_BUTTON){
		    	isDraw = TRUE;/* 按住鼠标左键画画 */ 
			} 
			break;
		case BUTTON_DOUBLECLICK:/* 双击鼠标的情况 */ 
			break;
		case BUTTON_UP:/* 松开鼠标的情况 */
			if (button == LEFT_BUTTON){
				isDraw = FALSE;/* 松开鼠标左键停止画画 */
			}
		case MOUSEMOVE:/* 移动鼠标的作用是画线 */ 
		    if(isDraw){
		    	DrawLine(mx-lx,my-ly);
		    	MovePen(mx,my);
			} 
			break;
	}
	lx = mx;
	ly = my;
}

void Main()
{
	InitGraphics();
	
	cx = GetWindowWidth();
	cy = GetWindowHeight();
	registerMouseEvent(MouseEventProcess);/* 注册鼠标回调函数 */ 
	SetPenSize(1);/* 设置画笔粗细为1 */ 
}





/* 题目4 */

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define TIMER_BLINK200  1/* 宏定义计时器常量 */ 

const int mseconds200 = 200;
double cx, cy;

static char* p1, * p2;
static char text[100] = { '\0', '\0' };
static int ptr = 0, textlen = 0;/* 输入的字符串长度 */
static double textx, texty; /* 字符申的起始位置 */
static bool IsBlink = TRUE; /* 是否闪烁标志 */

/* 定义所需函数 */

void startTimer(int id, int timeinterval);
void cancelTimer(int id);
void deleteit(int a);
void add(int a, char c);
void CleanBlink();
void Blinkit();
void KeyboardEventProcess(int key, int event);/* 键盘消息回调函数 */
void CharEventProcess(char c); /* 字符消息回调函数 */
void TimerEventProcess(int timerID);/* 定时器消息回调函数 */

/* 以下为主程序  */

void Main()/* 仅初始化执行一次 */
{
    InitGraphics();/* 图形初始化 */

    registerKeyboardEvent(KeyboardEventProcess);/* 注册镀盘消息回调函数 */
    registerCharEvent(CharEventProcess);/* 注册字符消息回调函数 */
    registerTimerEvent(TimerEventProcess); /* 注册定时器消息回调函数 */

    startTimer(TIMER_BLINK200, mseconds200);
    SetPenColor("Black"); /* 设置画笔颜色为黑 */
    SetPenSize(1);/* 设置画笔粗细为/ */

    cx = 0;
    cy = GetWindowHeight() - 0.1;
    textx = cx;
    texty = cy;
}

void CharEventProcess(char c)/* 字符消息回调函数 */
{
    switch (c) {
    case '\b':/* 输入退格符的情况 */
        CleanBlink();

        MovePen(cx, cy);
        SetEraseMode(TRUE);
        DrawTextString(text);
        if (ptr) {
            deleteit(ptr--);
            textlen--;
        }
        p1 = &text[0];
        p2 = &text[ptr];

        MovePen(cx, cy);
        SetEraseMode(FALSE);
        DrawTextString(text);/* 输出当前字符，且输出位置相应后移 */
        Blinkit();
        break;
    default:
        CleanBlink();

        MovePen(cx, cy);
        SetEraseMode(TRUE);
        DrawTextString(text);
        add(ptr, c);
        ptr++;
        text[++textlen] = '\0';

        p1 = &text[0];
        p2 = &text[ptr];

        MovePen(cx, cy);
        SetEraseMode(FALSE);
        DrawTextString(text);

        Blinkit();
        break;
    }
}

void KeyboardEventProcess(int key, int event)/* 每当产生键盘消息，都要执行 */
{
    switch (event) {
    case KEY_DOWN:/* 按下键盘的情况 */
        switch (key) {
        case VK_LEFT:/* 按下左键的情况 */
            if (ptr) {
                ptr--;
                CleanBlink();
                p1 = &text[0];
                p2 = &text[ptr];
                Blinkit();
            }
            break;
        case VK_RIGHT:/* 按下键右键的情况 */
            if (ptr < textlen) {
                ptr++;
                CleanBlink();
                p1 = &text[0];
                p2 = &text[ptr];
                Blinkit();
            }
            break;
        case VK_DELETE:/* 按下删除键的情况 */
            CleanBlink();

            MovePen(cx, cy);
            SetEraseMode(TRUE);
            DrawTextString(text);
            if (ptr + 1 != '\0') {
                deleteit(ptr + 1);
                textlen--;
            }
            p1 = &text[0];
            p2 = &text[ptr];
            MovePen(cx, cy);
            SetEraseMode(FALSE);
            DrawTextString(text);
            Blinkit();
            break;
        default:
            break;
        }
    }
}

/* 作用：刪去字符申中第a个字符 */

void deleteit(int a)
{
    while (text[a - 1] != '\0') {
        text[a - 1] = text[a];
        a++;
    }
}

/* 作用：把读入的字符插入字符申 */

void add(int a, char c)
{
    char temp = c;
    while (text[a] != '\0') {
        temp = text[a];
        text[a] = c;
        a++;
        c = temp;
    }
    text[a++] = c;
    text[a] = '\0';
}

/* 作用：清除光标 */

void CleanBlink()
{
    cancelTimer(TIMER_BLINK200);
    SetEraseMode(TRUE);
    MovePen(textx, texty - 0.04);
    DrawLine(0.05, 8);
    SetEraseMode(FALSE);
}

void Blinkit()
{
    textx = TextStringWidth(p1) - TextStringWidth(p2);
    MovePen(textx, texty);
    startTimer(TIMER_BLINK200, mseconds200);
}

/* 作用：定时器消息回调函数 */

void TimerEventProcess(int timerID)
{
    bool erasemode;

    switch (timerID) {
    case TIMER_BLINK200:
        erasemode = GetEraseMode();
        MovePen(textx, texty - 0.04);/* 起始位置 */
        SetEraseMode(IsBlink);
        DrawLine(0.05, 0);
        SetEraseMode(erasemode);
        IsBlink = !IsBlink;/*交替显示/隐藏字符申符号*/
        break;
    default:
        break;
    }
}





/* 题目5 */

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "linkedlist.h"
#include <math.h>

#define PI 3.1415926

linkedlistADT SnowList; /* 链表各结点依次存放各线段的角度 */
double length;          /* 初始边长（inch） */

static void DwawPolarLine(double r, double theta); /* 绘制极坐标线段 */
static void DrawKochSnowLine(void *obj); /* 绘制各线段并为链表遍历函数调用定制 */
static void SplitEdges(linkedlistADT linkedlist);/* 每边依次分解为四条边 */
static void KochSnow(linkedlistADT linkedlist, int n);/* 递归求n阶Koch雪花各边角度 */
static void KochSnow1(linkedlistADT linkedlist, int n);/* 非递归方法求n阶Koch雪花各边角度 */

void Main() 
{
	int n;

    InitGraphics();/* 图形初始化 */

	SetPenColor("Red"); /* 设置画笔颜色为红色 */
    SetPenSize(1);      /* 设置画笔粗细为1 */

	InitConsole();
	printf("Enter n: "); /* 输入阶数 */
	n = GetInteger();
	printf("Enter length: ");/* 输入初始边长（英寸） */
	length = GetReal();
	FreeConsole();

    /* 作用：初始三角形放在图形窗口中心位置并且画笔移动到左下角顶点位置 */
	MovePen(GetWindowWidth()/2.0 - length/2.0,
            GetWindowHeight()/2 - length/2.0*tan(30.0/180.0*PI));

	length = length / pow(3.0, (float)n); /* n阶雪花最终的线段大小 */

	SnowList = NewLinkedList(); /* 初始化链表 */
	KochSnow(SnowList, n);      /* 递归依次生成n阶雪花各线段角度，存放于链表中 */
	KochSnow1(SnowList, n);      /* 非递归依次生成n阶雪花各线段角度，存放于链表中 */
	
    TraverseLinkedList(SnowList, DrawKochSnowLine);/* 遍历链表，绘制线段 */
    FreeLinkedList(SnowList);/* 删除链表并释放空间 */

}

/* 作用：绘制极坐标直线，其中长度r，角度theta */
static void DrawPolarLine(double r, double theta)
{
	double radians;

	radians = theta / 180 * PI;
	DrawLine(r * cos(radians), r * sin(radians));
}

/*
 * 作用：为TraverseLinkedList调用函数参数定制的绘制直线函数
 * ------------------------------------------------------- 
 * obj是角度指针，length是直线长度（全局变量）
 */
static void DrawKochSnowLine(void *obj)
{
	DrawPolarLine(length, *((double *)obj));
}

/*
 * 作用：将各边依次分裂为四边
 * --------------------------
 * 每边角度依次为：theta, theta-60, theta+60, theta
 * 其中，theta为原边的角度，也就是n-1阶存放于链表各节点中的各边角度
 */
static void SplitEdges(linkedlistADT SnowList)
{
	linkedlistADT ptr1;
	double *ptheta, theta;

	ptr1 = SnowList;   /* 链表指针，即表头指针 */
    ptr1 = NextNode(SnowList, ptr1);/* 表头指针的下一个结点，即第一个数据结点 */
	while (ptr1 != NULL) {
		theta = *((double *)NodeObj(SnowList, ptr1)); /* 结点中原来存放的角度 */
		ptheta = GetBlock(sizeof(double));
		*ptheta = theta - 60;
        InsertNode(SnowList, ptr1, (void *)ptheta); /* 插入第二个角度结点 */
		ptr1 = NextNode(SnowList, ptr1);            /* 移到刚插入的结点 */
		ptheta = GetBlock(sizeof(double));
		*ptheta = theta + 60;                       
        InsertNode(SnowList, ptr1, (void *)ptheta);  /* 插入第三个角度结点 */
		ptr1 = NextNode(SnowList, ptr1);             /* 移到刚插入的结点 */
		ptheta = GetBlock(sizeof(double));
		*ptheta = theta;
        InsertNode(SnowList, ptr1, (void *)ptheta);  /* 插入第四个角度结点 */
		ptr1 = NextNode(SnowList, ptr1);             /* 移到刚插入的结点 */
		ptr1 = NextNode(SnowList, ptr1);             /* 移到原来的第二个结点 */
	}
}

/* 作用：递归生成n阶Koch雪花各边角度的函数 */
static void KochSnow(linkedlistADT SnowList, int n)
{
	double *ptheta;

	if (n == 0) { /* 0阶雪花即初始三角形，从左下端开始各边角度依次为0，120°，240° */
		ptheta = GetBlock(sizeof(double));
		*ptheta = 0;
        InsertNode(SnowList, NULL, (void *)ptheta);
		ptheta = GetBlock(sizeof(double));
		*ptheta = 120;
        InsertNode(SnowList, NULL, (void *)ptheta);
		ptheta = GetBlock(sizeof(double));
		*ptheta = 240;
        InsertNode(SnowList, NULL, (void *)ptheta);
	} else {
		KochSnow(SnowList, n-1);/* 生成第n-1阶Koch雪花各边 */
        SplitEdges(SnowList);/* 生成n阶同时将各边分裂成四边 */
	}
}

static void KochSnow1(linkedlistADT SnowList, int n)
{
	int i;
	double *ptheta;

	if (n < 0) return; /* 先生成0阶雪花即初始三角形，从左下端开始各边角度依次为0，120°，240° */
	ptheta = GetBlock(sizeof(double));
	*ptheta = 0;
    InsertNode(SnowList, NULL, (void *)ptheta);
	ptheta = GetBlock(sizeof(double));
	*ptheta = 120;
    InsertNode(SnowList, NULL, (void *)ptheta);
	ptheta = GetBlock(sizeof(double));
	*ptheta = 240;
    InsertNode(SnowList, NULL, (void *)ptheta);/* 依次分解各边，逐个生成高阶雪花各边 */
	for (i = 1; i <= n; i++) 
	SplitEdges(SnowList);
}

/*
 * 文件: linkedlist.c
 * -------------
 * 这个文件实现 the linkedlist.h .
 */

#include <stdio.h>

#include "genlib.h"
#include "linkedlist.h"

/* 导出项 */


/* 作用：分配并返回一个空的链表 (只包含一个头节点). */

linkedlistADT NewLinkedList(void)
{
    linkedlistADT head;

    head = New(linkedlistADT);
    head->dataptr = NULL;
	head->next = NULL;
    return (head);
}

/* 作用：释放与链表关联的储存 */

void FreeLinkedList(linkedlistADT head)
{
	linkedlistADT nodeptr, nextnodeptr;

	nodeptr = head;
	while (nodeptr != NULL) {
	    nextnodeptr = nodeptr->next;
		if (nodeptr != head) FreeBlock(nodeptr->dataptr);
		FreeBlock(nodeptr);
		nodeptr = nextnodeptr;
	}
}

/* 作用：搜索节点；找到的话返回节点指针，否则返回NULL */

linkedlistADT SearchNode(linkedlistADT head, void *obj, bool (*equalfunptr)(void *obj1, void *obj2))
{
	linkedlistADT nodeptr;
	
	if (obj == NULL) return NULL;
	nodeptr = head->next;
	while (nodeptr != NULL) {
		if ((*equalfunptr)(nodeptr->dataptr, obj)) return nodeptr;
	}
	return NULL;
}

/* 作用：在被链接的nodeptr节点之后输入数据值；如果nodeptr为空，则将obj附加到链表的尾部 */

void InsertNode(linkedlistADT head, linkedlistADT nodeptr, void *obj)
{
	linkedlistADT ptr;

	if (obj == NULL) return;
	if (nodeptr == NULL) { /* 将obj附加到尾部 */
		nodeptr = head;
		while (nodeptr->next != NULL) nodeptr = nodeptr->next;
	}
	ptr = New(linkedlistADT); /* 新节点的情况 */
	ptr->dataptr = obj;  /* 设置节点的数据ptr */
	ptr->next = nodeptr->next;
	nodeptr->next = ptr;
}

/* 作用：链表的obj数据删除节点；如果找到节点，则返回节点指针，否则返回NULL */

linkedlistADT DeleteNode(linkedlistADT head, void *obj, bool (*equalfunptr)(void *obj1, void *obj2))
{
	linkedlistADT nodeptr, prenodeptr;

	if (obj == NULL) return NULL;
	prenodeptr = head;
    nodeptr = head->next;
	while (nodeptr != NULL) {
		if ((*equalfunptr)(nodeptr->dataptr, obj)) break;
	    prenodeptr = nodeptr;
        nodeptr = nodeptr->next;
	}
	if (nodeptr != NULL) /* 找到的情况 */
	    prenodeptr->next = nodeptr->next;
	return nodeptr;
}

/* 作用：遍历链表，并使用funptr指向的函数处理节点值obj */

void TraverseLinkedList(linkedlistADT head, void (*traversefunptr)(void *obj))
{
	linkedlistADT nodeptr;

	if (traversefunptr == NULL) return;
	nodeptr = head->next;
	while (nodeptr != NULL) {
		(*traversefunptr)(nodeptr->dataptr);
		nodeptr = nodeptr->next;
	}
}

/* 作用：返回链表的index-th节点的指针 */

void *ithNodeobj(linkedlistADT head, int index)
{
	linkedlistADT nodeptr;
	int count = 0;

	nodeptr = head->next;
	while (nodeptr != NULL) {
		if (++count == index) break;
		nodeptr = nodeptr->next;
	}
	if (nodeptr != NULL)
        return nodeptr->dataptr;
	return NULL;
}

/* 作用：返回nodeptr的下一个节点的指针 */

linkedlistADT NextNode(linkedlistADT head, linkedlistADT nodeptr)
{
	if (nodeptr != NULL) return nodeptr->next;
	return NULL;
}

/* 作用：返回nodeptr所指向的节点的dataptr*/

void *NodeObj(linkedlistADT head, linkedlistADT nodeptr)
{
	if (nodeptr != NULL) return nodeptr->dataptr;
	return NULL;
}
