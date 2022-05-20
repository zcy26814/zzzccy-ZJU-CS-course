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

Rec Selectnearest1(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distRectangle(mx, my, (Rec)Node(p));//获取鼠标与当前结点矩形的距离
	range = RecRange((Rec)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distRectangle(mx, my, (Rec)Node(p));
		range = RecRange((Rec)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Rectangle] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Rec)Node(list1));
}

Rou Selectnearest2(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distRoundedrectangle(mx, my, (Rou)Node(p));//获取鼠标与当前结点矩形的距离
	range = RouRange((Rou)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distRoundedrectangle(mx, my, (Rou)Node(p));
		range = RouRange((Rou)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Roundedrectangle] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Rou)Node(list1));
}

Rho Selectnearest3(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distRhombus(mx, my, (Rho)Node(p));//获取鼠标与当前结点矩形的距离
	range = RhoRange((Rho)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distRhombus(mx, my, (Rho)Node(p));
		range = RhoRange((Rho)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Rhombus] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Rho)Node(list1));
}

Cen Selectnearest4(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distCenteredEllipse(mx, my, (Cen)Node(p));//获取鼠标与当前结点矩形的距离
	range = CenRange((Cen)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distCenteredEllipse(mx, my, (Cen)Node(p));
		range = CenRange((Cen)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[CenteredEllipse] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Cen)Node(list1));
}

Arr Selectnearest5(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distArrow(mx, my, (Arr)Node(p));//获取鼠标与当前结点矩形的距离
	range = ArrRange((Arr)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distArrow(mx, my, (Arr)Node(p));
		range = ArrRange((Arr)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Arrow] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Arr)Node(list1));
}

Lin Selectnearest6(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distLine(mx, my, (Lin)Node(p));//获取鼠标与当前结点矩形的距离
	range = LinRange((Lin)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distLine(mx, my, (Lin)Node(p));
		range = LinRange((Lin)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Line] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Lin)Node(list1));
}

Par Selectnearest7(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distParallelogram(mx, my, (Par)Node(p));//获取鼠标与当前结点矩形的距离
	range = ParRange((Par)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distParallelogram(mx, my, (Par)Node(p));
		range = ParRange((Par)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Parallelogram] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Par)Node(list1));
}

Tex Selectnearest8(linklist *list, double mx, double my)
{
	linklist *list1,*p;
	double distance,mindistance,range;
	
	mindistance = 1000000000.0;
	list1 = NULL;
	p = Next(list);
	if (p == NULL) return NULL;//结点为空
	distance = distText(mx, my, (Tex)Node(p));//获取鼠标与当前结点矩形的距离
	range = TexRange((Par)Node(p));//获取当前结点矩形的响应范围 
	if (distance <= range){//若距离小于响应范围则保存距离，获取该结点地址
		mindistance = distance;
		list1 = p;
	}
	while (Next(p) != NULL){//找到距离最小的结点，保存最小距离并获取该结点地址
		p = Next(p);//遍历下一个结点 
		distance = distText(mx, my, (Tex)Node(p));
		range = TexRange((Par)Node(p));
		if (distance <= range){
			if (mindistance == 1000000000.0){
				mindistance = distance;
				list1 = p;
			}
			else {
				if (distance < mindistance){//若当前结点距离小于保存的最小距离，则保存该距离并获取该节点地址 
					mindistance = distance;
					list1 = p;
				}
			}
		}
	}
	mindist[Text] = mindistance;//全局变量赋值与最近矩形结点的距离
	if (mindistance == 1000000000.0) return NULL;
	return ((Tex)Node(list1));
}

void Picknearest(linklist *list[], double omx, double omy)
{
	int i, min;
	
	curRectangle = Selectnearest1(list[Rectangle], omx, omy);
	curRoundedrectangle = Selectnearest2(list[Roundedrectangle], omx, omy);
	curRhombus = Selectnearest3(list[Rhombus], omx, omy);
	curCenteredEllipse = Selectnearest4(list[CenteredEllipse], omx, omy);
	curArrow = Selectnearest5(list[Arrow], omx, omy);
	curLine = Selectnearest6(list[Line], omx, omy);
	curParallelogram = Selectnearest7(list[Parallelogram], omx, omy);
	curText = Selectnearest8(list[Text], omx, omy);
	
	min = 0;
	for (i = 1; i < NLIST; i++) {//循环找到与鼠标距离最近的图形
		if (mindist[i] < mindist[min]) min = i;
	}
	curList = min;
	
}

