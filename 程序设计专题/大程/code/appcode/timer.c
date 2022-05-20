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

#include "imgui.h"
#include "x.h" 

void TimerEventProcess(int timerID)
{
	bool erasemode;
	double a,b;
	switch (timerID) {
	  case TIMER_BLINK500: //500ms光标闪烁定时器
	    if (isSelected){
	    	SetPenColor("Green");
	    	erasemode = GetEraseMode();
		    SetEraseMode(isDisplayChar);//擦除模式开启或关闭 
		if(curList == Text){
		    if (curText->x1 > curText->x2)
	           a = curText->x2;
	        else 
	           a = curText->x1;
	        if (curText->y1 > curText->y2)
	           b = curText->y2;
         	else
	           b = curText->y1;
		    MovePen(a+0.3+TextStringWidth(text1),b+fabs(curText->y2-curText->y1)/2);//移动画笔到当前位置 
		}
		if(curList == Rectangle){
		    if (curRectangle->x1 > curRectangle->x2)
	           a = curRectangle->x2;
	        else 
	           a = curRectangle->x1;
	        if (curRectangle->y1 > curRectangle->y2)
	           b = curRectangle->y2;
         	else
	           b = curRectangle->y1;
		    MovePen(a+0.3+TextStringWidth(rect1),b+fabs(curRectangle->y2-curRectangle->y1)/2);//移动画笔到当前位置 
		    }
		if(curList == Roundedrectangle){
		    if (curRoundedrectangle->x1 > curRoundedrectangle->x2)
	           a = curRoundedrectangle->x2;
	        else 
	           a = curRoundedrectangle->x1;
	        if (curRoundedrectangle->y1 > curRoundedrectangle->y2)
	           b = curRoundedrectangle->y2;
         	else
	           b = curRoundedrectangle->y1;
		    MovePen(a+0.3+TextStringWidth(roun1),b+fabs(curRoundedrectangle->y2-curRoundedrectangle->y1)/2);//移动画笔到当前位置 
		}
		if(curList == Rhombus){
		    if (curRhombus->x1 > curRhombus->x2)
	           a = curRhombus->x2;
	        else 
	           a = curRhombus->x1;
	        if (curRhombus->y1 > curRhombus->y2)
	           b = curRhombus->y2;
         	else
	           b = curRhombus->y1;
		    MovePen(a+0.3+TextStringWidth(rhom1),b+fabs(curRhombus->y2-curRhombus->y1)/2);//移动画笔到当前位置 
		}
		if(curList == CenteredEllipse){
		    if (curCenteredEllipse->x1 > curCenteredEllipse->x2)
	           a = curCenteredEllipse->x2;
	        else 
	           a = curCenteredEllipse->x1;
	        if (curCenteredEllipse->y1 > curCenteredEllipse->y2)
	           b = curCenteredEllipse->y2;
         	else
	           b = curCenteredEllipse->y1;
		    MovePen(a+0.3+TextStringWidth(cent1),b+fabs(curCenteredEllipse->y2-curCenteredEllipse->y1)/2);//移动画笔到当前位置 
		}
		if(curList == Parallelogram){
		    if (curParallelogram->x1 > curParallelogram->x2)
	           a = curParallelogram->x2;
	        else 
	           a = curParallelogram->x1;
	        if (curParallelogram->y1 > curParallelogram->y2)
	           b = curParallelogram->y2;
         	else
	           b = curParallelogram->y1;
		    MovePen(a+0.3+TextStringWidth(para1),b+fabs(curParallelogram->y2-curParallelogram->y1)/2);//移动画笔到当前位置 
		}
			DrawTextString("_");
	        SetEraseMode(erasemode);
		    isDisplayChar = !isDisplayChar;
	    }
	    else
	        SetPenColor("Red");
		break;
	  default:
		break;
	  }
}
