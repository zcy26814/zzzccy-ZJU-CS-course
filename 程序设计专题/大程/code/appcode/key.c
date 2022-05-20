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


void KeyboardEventProcess(int key, int event)
{
	int i;
	int textlen;
	int rectlen;
	int rounlen;
	int rhomlen;
	int centlen;
	int paralen; 
	if (!isSelected){
		uiGetKeyboard(key,event);
	    display();
	}
	else if (isSelected){
	switch (event) {
	 	case KEY_DOWN://键盘按下 
			 switch (key) {
			 	case VK_LEFT://若是左键，则当前位置前移一个字符 
			 	if(curList == Text){
			      if (curText->num1!=0){//若已到字符串头部则不移动 
					 curText->num1--;}
                  break;}
                  if(curList == Rectangle){
			      if (curRectangle->num1!=0){//若已到字符串头部则不移动 
					 curRectangle->num1--;}
                  break;}
                  if(curList == Roundedrectangle){
			      if (curRoundedrectangle->num1!=0){//若已到字符串头部则不移动 
					 curRoundedrectangle->num1--;}
                  break;}
                  if(curList == Rhombus){
			      if (curRhombus->num1!=0){//若已到字符串头部则不移动 
					 curRhombus->num1--;}
                  break;}
                  if(curList == CenteredEllipse){
			      if (curCenteredEllipse->num1!=0){//若已到字符串头部则不移动 
					 curCenteredEllipse->num1--;}
                  break;}
                  if(curList == Parallelogram){
			      if (curParallelogram->num1!=0){//若已到字符串头部则不移动 
					 curParallelogram->num1--;}
                  break;}
			    case VK_RIGHT://若是右键，则当前位置后移一个字符 
			    if(curList == Text){
			      if (curText->memo[curText->num1]!='\0'){//若已到字符串尾部则不移动 
					 curText->num1++;}
                  break;}
                if(curList == Rectangle){
			      if (curRectangle->memo[curRectangle->num1]!='\0'){//若已到字符串尾部则不移动 
					 curRectangle->num1++;}
                  break;}
                if(curList == Roundedrectangle){
			      if (curRoundedrectangle->memo[curRoundedrectangle->num1]!='\0'){//若已到字符串尾部则不移动 
					 curRoundedrectangle->num1++;}
                  break;}
                if(curList == Rhombus){
			      if (curRhombus->memo[curRhombus->num1]!='\0'){//若已到字符串尾部则不移动 
					 curRhombus->num1++;}
                  break;}
                if(curList == CenteredEllipse){
			      if (curCenteredEllipse->memo[curCenteredEllipse->num1]!='\0'){//若已到字符串尾部则不移动 
					 curCenteredEllipse->num1++;}
                  break;}
                if(curList == Parallelogram){
			      if (curParallelogram->memo[curParallelogram->num1]!='\0'){//若已到字符串尾部则不移动 
					 curParallelogram->num1++;}
                  break;}
			    case VK_BACK://若是退格键，则删除前一个字符 
			    if(curList == Text){
			      if (curText->num1>0){//若当前位置不为字符串头部，则记录当前位置 
					 textlen=curText->num1;
					 curText->num2--;//字符串长度减一 
                     while (1){//删除当前位置之前的一个字符
                     	if (curText->memo[curText->num1]=='\0'){
                     	   curText->memo[curText->num1-1]=curText->memo[curText->num1];
                     	   curText->num1--;
						   break;
                     	}
						curText->memo[curText->num1-1]=curText->memo[curText->num1];
						curText->num1++;
                     }
                     if (textlen<=curText->num1)//若删除后字符串长度大于记录的当前位置，当前位置向前移一位 
                        curText->num1=textlen-1;
				  }
                  break;}
                if(curList == Rectangle){
			      if (curRectangle->num1>0){//若当前位置不为字符串头部，则记录当前位置 
					 rectlen=curRectangle->num1;
					 curRectangle->num2--;//字符串长度减一 
                     while (1){//删除当前位置之前的一个字符
                     	if (curRectangle->memo[curRectangle->num1]=='\0'){
                     	   curRectangle->memo[curRectangle->num1-1]=curRectangle->memo[curRectangle->num1];
                     	   curRectangle->num1--;
						   break;
                     	}
						curRectangle->memo[curRectangle->num1-1]=curRectangle->memo[curRectangle->num1];
						curRectangle->num1++;
                     }
                     if (rectlen<=curRectangle->num1)//若删除后字符串长度大于记录的当前位置，当前位置向前移一位 
                        curRectangle->num1=rectlen-1;
				  }
                  break;}
                if(curList == Roundedrectangle){
			      if (curRoundedrectangle->num1>0){//若当前位置不为字符串头部，则记录当前位置 
					 rounlen=curRoundedrectangle->num1;
					 curRoundedrectangle->num2--;//字符串长度减一 
                     while (1){//删除当前位置之前的一个字符
                     	if (curRoundedrectangle->memo[curRoundedrectangle->num1]=='\0'){
                     	   curRoundedrectangle->memo[curRoundedrectangle->num1-1]=curRoundedrectangle->memo[curRoundedrectangle->num1];
                     	   curRoundedrectangle->num1--;
						   break;
                     	}
						curRoundedrectangle->memo[curRoundedrectangle->num1-1]=curRoundedrectangle->memo[curRoundedrectangle->num1];
						curRoundedrectangle->num1++;
                     }
                     if (rounlen<=curRoundedrectangle->num1)//若删除后字符串长度大于记录的当前位置，当前位置向前移一位 
                        curRoundedrectangle->num1=rounlen-1;
				  }
                  break;}
                if(curList == Rhombus){
			      if (curRhombus->num1>0){//若当前位置不为字符串头部，则记录当前位置 
					 rhomlen=curRhombus->num1;
					 curRhombus->num2--;//字符串长度减一 
                     while (1){//删除当前位置之前的一个字符
                     	if (curRhombus->memo[curRhombus->num1]=='\0'){
                     	   curRhombus->memo[curRhombus->num1-1]=curRhombus->memo[curRhombus->num1];
                     	   curRhombus->num1--;
						   break;
                     	}
						curRhombus->memo[curRhombus->num1-1]=curRhombus->memo[curRhombus->num1];
						curRhombus->num1++;
                     }
                     if (rhomlen<=curRhombus->num1)//若删除后字符串长度大于记录的当前位置，当前位置向前移一位 
                        curRhombus->num1=rhomlen-1;
				  }
                  break;}
                if(curList == CenteredEllipse){
			      if (curCenteredEllipse->num1>0){//若当前位置不为字符串头部，则记录当前位置 
					 centlen=curCenteredEllipse->num1;
					 curCenteredEllipse->num2--;//字符串长度减一 
                     while (1){//删除当前位置之前的一个字符
                     	if (curCenteredEllipse->memo[curCenteredEllipse->num1]=='\0'){
                     	   curCenteredEllipse->memo[curCenteredEllipse->num1-1]=curCenteredEllipse->memo[curCenteredEllipse->num1];
                     	   curCenteredEllipse->num1--;
						   break;
                     	}
						curCenteredEllipse->memo[curCenteredEllipse->num1-1]=curCenteredEllipse->memo[curCenteredEllipse->num1];
						curCenteredEllipse->num1++;
                     }
                     if (centlen<=curCenteredEllipse->num1)//若删除后字符串长度大于记录的当前位置，当前位置向前移一位 
                        curCenteredEllipse->num1=centlen-1;
				  }
                  break;}
                if(curList == Parallelogram){
			      if (curParallelogram->num1>0){//若当前位置不为字符串头部，则记录当前位置 
					 paralen=curText->num1;
					 curParallelogram->num2--;//字符串长度减一 
                     while (1){//删除当前位置之前的一个字符
                     	if (curParallelogram->memo[curParallelogram->num1]=='\0'){
                     	   curParallelogram->memo[curParallelogram->num1-1]=curParallelogram->memo[curParallelogram->num1];
                     	   curParallelogram->num1--;
						   break;
                     	}
						curParallelogram->memo[curParallelogram->num1-1]=curParallelogram->memo[curParallelogram->num1];
						curParallelogram->num1++;
                     }
                     if (paralen<=curParallelogram->num1)//若删除后字符串长度大于记录的当前位置，当前位置向前移一位 
                        curParallelogram->num1=paralen-1;
				  }
                  break;}
			    case VK_DELETE://若是删除键，则删除后一个字符 
			    if(curList == Text){
			      curText->x1=curText->x2=0;
			      curText->y1=curText->y2=0;
			      curText->num1=0;
			      curText->num2=0;
			      strcpy(curText->memo,"");
			      break;
			 	 }
			 	if(curList == Rectangle){
			      curRectangle->x1=curRectangle->x2=0;
			      curRectangle->y1=curRectangle->y2=0;
			      curRectangle->num1=0;
			      curRectangle->num2=0;
			      strcpy(curRectangle->memo,"");
			      break;
			 	 }
			 	if(curList == Roundedrectangle){
			      curRoundedrectangle->x1=curRoundedrectangle->x2=0;
			      curRoundedrectangle->y1=curRoundedrectangle->y2=0;
			      curRoundedrectangle->num1=0;
			      curRoundedrectangle->num2=0;
			      strcpy(curRoundedrectangle->memo,"");
			      break;
			 	 }
			 	if(curList == Rhombus){
			      curRhombus->x1=curRhombus->x2=0;
			      curRhombus->y1=curRhombus->y2=0;
			      curRhombus->num1=0;
			      curRhombus->num2=0;
			      strcpy(curRhombus->memo,"");
			      break;
			 	 }
			 	if(curList == CenteredEllipse){
			      curCenteredEllipse->x1=curCenteredEllipse->x2=0;
			      curCenteredEllipse->y1=curCenteredEllipse->y2=0;
			      curCenteredEllipse->num1=0;
			      curCenteredEllipse->num2=0;
			      strcpy(curCenteredEllipse->memo,"");
			      break;
			 	 }
			 	if(curList == Parallelogram){
			      curParallelogram->x1=curParallelogram->x2=0;
			      curParallelogram->y1=curParallelogram->y2=0;
			      curParallelogram->num1=0;
			      curParallelogram->num2=0;
			      strcpy(curText->memo,"");
			      break;
			 	 }
			 break;
			 }
	    case KEY_UP:
	    	if(curList == Text){
	    	 for (i=0;i<curText->num1;i++)//记录当前位置前的字符串 
		        text1[i]=curText->memo[i];
	         text1[i]='\0';
	         display();
			 break;
			 }
			if(curList == Rectangle){
	    	 for (i=0;i<curRectangle->num1;i++)//记录当前位置前的字符串 
		        rect1[i]=curRectangle->memo[i];
	         rect1[i]='\0';
	         display();
			 break;
			 }
			if(curList == Roundedrectangle){
	    	 for (i=0;i<curRoundedrectangle->num1;i++)//记录当前位置前的字符串 
		        roun1[i]=curRoundedrectangle->memo[i];
	         roun1[i]='\0';
	         display();
			 break;
			 }
			if(curList == Rhombus){
	    	 for (i=0;i<curRhombus->num1;i++)//记录当前位置前的字符串 
		        rhom1[i]=curRhombus->memo[i];
	         rhom1[i]='\0';
	         display();
			 break;
			 }
			if(curList == CenteredEllipse){
	    	 for (i=0;i<curCenteredEllipse->num1;i++)//记录当前位置前的字符串 
		        cent1[i]=curCenteredEllipse->memo[i];
	         cent1[i]='\0';
	         display();
			 break;
			 }
			if(curList == Parallelogram){
	    	 for (i=0;i<curParallelogram->num1;i++)//记录当前位置前的字符串 
		        para1[i]=curParallelogram->memo[i];
	         para1[i]='\0';
	         display();
			 break;
			 }
    }
    if (isSelected && (curList == Arrow || curList == Line)){
    	switch (event) {
    		case KEY_DOWN:
    			switch (key) {
    				case VK_DELETE:
    					if (curList == Arrow){
    						curArrow->x1=curArrow->x2=0;
    						curArrow->y1=curArrow->y2=0;
    					}
    					else if (curList == Line){
    						curLine->x1=curLine->x2=0;
    						curLine->y1=curLine->y2=0;
    					}
    					display();
    					break;
    			}
    		break;
    	}
    }
    }
}
