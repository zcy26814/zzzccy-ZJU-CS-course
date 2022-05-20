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


void CharEventProcess(char c)
{
	int i,textlen;
	if (curList == Arrow || curList == Line || !isSelected){
	   uiGetChar(c); // GUI字符输入
	   display(); //刷新显示
	}
	else if (isSelected){
	switch (c) {
       case '\r': //VK_RETURN（注意：回车在这里返回的字符是'\r'，不是'\n'） 
   	 	   break;
 	   case 27: //ESC 
 	       break;
 	   case 8: //VK_BACK
 	   	   break;
 	   case 16: //VK_DELETE
 	   	   break;
 	   case 37: //VK_LEFT
 	   	   break;
 	   case 39: //VK_RIGHT
 	   	   break;
       default:
       	if(curList == Text && curText->num2 < 79){
	  	   if (curText->memo[curText->num1]!='\0'){
	  	   	  for (i=curText->num2;i>curText->num1;i--){
	  	   	  	  curText->memo[i+1]=curText->memo[i];
	  	   	  }
	  	   	  curText->memo[curText->num1+1]=c;
	  	   	  curText->num2++;
	  	   }
	  	   else{
	  	   	  curText->memo[curText->num1++]=c;
	  	   	  curText->memo[curText->num1]='\0';
	  	   	  curText->num2++;
	  	   }
	  	   break;
	  }
	  if(curList == Rectangle && curRectangle->num2 < 79){
	  	   if (curRectangle->memo[curRectangle->num1]!='\0'){
	  	   	  for (i=curRectangle->num2;i>curRectangle->num1;i--){
	  	   	  	  curRectangle->memo[i+1]=curRectangle->memo[i];
	  	   	  }
	  	   	  curRectangle->memo[curRectangle->num1+1]=c;
	  	   	  curRectangle->num2++;
	  	   }
	  	   else{
	  	   	  curRectangle->memo[curRectangle->num1++]=c;
	  	   	  curRectangle->memo[curRectangle->num1]='\0';
	  	   	  curRectangle->num2++;
	  	   }
	  	   break;
	  }
	  if(curList == Roundedrectangle && curRoundedrectangle->num2 < 79){
	  	   if (curRoundedrectangle->memo[curRoundedrectangle->num1]!='\0'){
	  	   	  for (i=curRoundedrectangle->num2;i>curRoundedrectangle->num1;i--){
	  	   	  	  curRoundedrectangle->memo[i+1]=curRoundedrectangle->memo[i];
	  	   	  }
	  	   	  curRoundedrectangle->memo[curRoundedrectangle->num1+1]=c;
	  	   	  curRoundedrectangle->num2++;
	  	   }
	  	   else{
	  	   	  curRoundedrectangle->memo[curRoundedrectangle->num1++]=c;
	  	   	  curRoundedrectangle->memo[curRoundedrectangle->num1]='\0';
	  	   	  curRoundedrectangle->num2++;
	  	   }
	  	   break;
	  }
	  if(curList == Rhombus && curRhombus->num2 < 79){
	  	   if (curRhombus->memo[curRhombus->num1]!='\0'){
	  	   	  for (i=curRhombus->num2;i>curRhombus->num1;i--){
	  	   	  	  curRhombus->memo[i+1]=curRhombus->memo[i];
	  	   	  }
	  	   	  curRhombus->memo[curRhombus->num1+1]=c;
	  	   	  curRhombus->num2++;
	  	   }
	  	   else{
	  	   	  curRhombus->memo[curRhombus->num1++]=c;
	  	   	  curRhombus->memo[curRhombus->num1]='\0';
	  	   	  curRhombus->num2++;
	  	   }
	  	   break;
	  }
	  if(curList == CenteredEllipse && curCenteredEllipse->num2 < 79){
	  	   if (curCenteredEllipse->memo[curCenteredEllipse->num1]!='\0'){
	  	   	  for (i=curCenteredEllipse->num2;i>curCenteredEllipse->num1;i--){
	  	   	  	  curCenteredEllipse->memo[i+1]=curCenteredEllipse->memo[i];
	  	   	  }
	  	   	  curCenteredEllipse->memo[curCenteredEllipse->num1+1]=c;
	  	   	  curCenteredEllipse->num2++;
	  	   }
	  	   else{
	  	   	  curCenteredEllipse->memo[curCenteredEllipse->num1++]=c;
	  	   	  curCenteredEllipse->memo[curCenteredEllipse->num1]='\0';
	  	   	  curCenteredEllipse->num2++;
	  	   }
	  	   break;
	  }
	  if(curList == Parallelogram && curParallelogram->num2 < 79){
	  	   if (curParallelogram->memo[curParallelogram->num1]!='\0'){
	  	   	  for (i=curParallelogram->num2;i>curParallelogram->num1;i--){
	  	   	  	  curParallelogram->memo[i+1]=curParallelogram->memo[i];
	  	   	  }
	  	   	  curParallelogram->memo[curParallelogram->num1+1]=c;
	  	   	  curParallelogram->num2++;
	  	   }
	  	   else{
	  	   	  curParallelogram->memo[curParallelogram->num1++]=c;
	  	   	  curParallelogram->memo[curParallelogram->num1]='\0';
	  	   	  curParallelogram->num2++;
	  	   }
	  	   break;
	  }
    }
    }
}
