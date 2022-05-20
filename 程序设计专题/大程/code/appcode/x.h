#ifndef _chart_h
#define _chart_h

#define NLIST                 8
#define Rectangle             0
#define Roundedrectangle      1
#define Rhombus               2
#define CenteredEllipse       3
#define Arrow                 4
#define Line                  5
#define Parallelogram         6
#define Text                  7
#define PI                    3.1415926
#define TIMER_BLINK500        1     //500ms定时器事件标志号

typedef struct {//矩形类型
	double x1, y1;//左下角坐标
    double x2, y2;//右上角坐标
    int PenSize; //粗细
    int color; //颜色
    bool isSelected; //选中
    bool isfilling; //填充
    char memo[80];
	int num1;
	int num2; 
	double fillpercent;
}Rect,*Rec;

typedef struct {//圆角矩形类型
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
	char memo[80];
	int num1;
	int num2; 
	double fillpercent;
}Roun,*Rou;

typedef struct {//菱形类型 
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
	char memo[80];
	int num1;
	int num2; 
	double fillpercent;
}Rhom,*Rho;

typedef struct {//椭圆类型 
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
	char memo[80];
	int num1;
	int num2; 
	double fillpercent;
}Cent,*Cen;

typedef struct {//箭头类型 
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
}Arro,*Arr;

typedef struct {//直线类型 
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
}Line1,*Lin;

typedef struct {//平行四边形类型 
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
	char memo[80];
	int num1;
	int num2; 
	double fillpercent;
}Para,*Par;

typedef struct {//文本框类型 
	double x1,y1;//左下角坐标
	double x2,y2;//右上角坐标
	int PenSize;//粗细
	int color;//颜色
	bool isSelected;//选中
	bool isfilling;//填充
	char memo[80];//文本 
	int num1;//文本当前输入位置 
	int num2;//文本字数
}Text1,*Tex;

typedef struct linklist//链表 
{
	void *dataptr;//图表数据 
	struct linklist *next;//下一个指针 
}linklist;

Rec a1 = NULL;
Rou b1 = NULL;
Rho c1 = NULL;
Cen d1 = NULL;
Arr e1 = NULL;
Lin f1 = NULL;
Par g1 = NULL;
Tex h2 = NULL;
bool usage = FALSE;//帮助开关 
int isColor=3;//绘图颜色 
int IsPenSize;//笔画粗细 
FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7,*fp8;//文件指针 
FILE *fo1,*fo2,*fo3,*fo4,*fo5,*fo6,*fo7,*fo8;//文件指针 
int curList1 = NLIST;//当前选中的图表类型 
bool isFill = FALSE; //是否填充 
double fillpercent = 1; //填充程度 
FILE *fp;//文件指针 
char text1[80];//光标位置
char rect1[80];
char rhom1[80];
char cent1[80];
char para1[80];
char roun1[80];
const int mseconds500 = 250;//定时器定时时间 
bool isDisplayChar = TRUE;//擦除开关 
bool ismove = FALSE;//移动开关 
bool ischange = FALSE;//缩放开关 
bool isSelected = FALSE;//选中功能开关 
bool isSelected1 = FALSE;//选中开关 
int curList = NLIST;//当前选中的图表类型 
bool isRectangle = FALSE;//绘制矩形开关 
bool isRoundedrectangle = FALSE;//绘制圆角矩形开关 
bool isRhombus = FALSE;//绘制菱形开关 
bool isCenteredEllipse = FALSE;//绘制椭圆开关 
bool isArrow = FALSE;//绘制箭头开关 
bool isLine = FALSE;//绘制直线开关 
bool isParallelogram = FALSE;//绘制平行四边形开关 
bool isText = FALSE;//绘制文本开关 
bool isclick = FALSE;//绘图开关 
bool isclick1 = FALSE;//绘图功能开关 
bool isclick2 = FALSE;//菜单选中开关 
linklist *list[NLIST]={NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};//图表类型头指针数组 
double mindist[NLIST]={1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0, 1000000000.0};//鼠标与图表距离数组 
Rec curRectangle = NULL;//选中矩形指针 
Rou curRoundedrectangle = NULL;//选中圆角矩形指针 
Rho curRhombus = NULL;//选中平行四边形指针 
Cen curCenteredEllipse = NULL;//选中椭圆指针 
Arr curArrow = NULL;//选中箭头指针 
Lin curLine = NULL;//选中直线指针 
Par curParallelogram = NULL;//选中平行四边形指针 
Tex curText = NULL;//选中文本指针 

void DefineColor(string name,double red, double green, double blue);

//新建链表 
linklist *Newlink(void);

//删除链表 
void Deletelink(void);

//插入结点 
void Insert(linklist* head, linklist* p, void *q);

//遍历链表并绘制图形 
void travellink(linklist* head, void (*traveler)(void *p));

//遍历所有链表并绘制图形 
void travel(void);

//绘制矩形 
void DrawRectangle(void *p);

//绘制圆角矩形 
void DrawRoundedrectangle(void *p);

//绘制菱形 
void DrawRhombus(void *p);

//绘制椭圆 
void DrawCenteredEllipse(void *p);

//绘制箭头 
void DrawArrow(void *p);

//绘制直线 
void DrawLine1(void *p);

//绘制平行四边形 
void DrawParallelogram(void *p);

//绘制文本 
void DrawText1(void *p);

//查找下一个结点 
linklist *Next(linklist *p);

//获取当前结点的数据 
void *Node(linklist *p);

//计算鼠标与矩形之间的距离 
double distRectangle(double x, double y, Rec a);

//矩形响应范围 
double RecRage(Rec a);

//计算鼠标与圆角矩形之间的距离 
double distRoundedrectangle(double x, double y, Rou a);

//圆角矩形响应范围 
double RouRange(Rou a);

//计算鼠标与菱形之间的距离 
double distRhombus(double x, double y, Rho a);

//菱形响应范围 
double RhoRange(Rho a);

//计算鼠标与椭圆之间的距离 
double distCenteredEllipse(double x, double y, Cen a);

//椭圆响应范围 
double CenRange(Cen a);

//计算鼠标与箭头之间的距离 
double distArrow(double x, double y, Arr a);

//箭头响应范围 
double ArrRange(Arr a);

//计算鼠标与直线之间的距离 
double distLine(double x, double y, Lin a);

//直线响应范围 
double LinRange(Lin a);

//计算鼠标与平行四边形之间的距离 
double distParallelogram(double x, double y, Par a);

//平行四边形响应范围 
double ParRange(Par a);

//计算鼠标与文本框之间的距离 
double distText(double x, double y, Tex a);

//文本框响应范围 
double TexRange(Tex a);

//查找最近的矩形 
Rec Selectnearest1(linklist *list, double mx, double my);

//查找最近的圆角矩形 
Rou Selectnearest2(linklist *list, double mx, double my);

//查找最近的菱形 
Rho Selectnearest3(linklist *list, double mx, double my);

//查找最近的椭圆 
Cen Selectnearest4(linklist *list, double mx, double my);

//查找最近的箭头 
Arr Selectnearest5(linklist *list, double mx, double my);

//查找最近的直线 
Lin Selectnearest6(linklist *list, double mx, double my);

//查找最近的平行四边形 
Par Selectnearest7(linklist *list, double mx, double my);

//查找最近的图形 
void Picknearest(linklist *list[], double omx, double omy);

//使用说明提示 
void Help();

#endif
