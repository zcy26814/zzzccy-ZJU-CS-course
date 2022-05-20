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

static double winwidth, winheight;   // 窗口尺寸
Rec curRec;

void drawMenu()
{
	static char * menuListFile[] = {"File",  
		"Open  | Ctrl-O", 
		"Save  | Ctrl-S",
		"Exit  | Ctrl-E",
		"New   | Ctrl-N"};
	static char * menuListEdit[] = {"Edit",
	    "Select|Ctrl-T",     //选中 
		"Copy  |Ctrl-C",     //复制 
		"Paste |Ctrl-V",     //粘贴 
		"Delete|Ctrl-D"};    //删除 
	static char * menuListAttribute[] = {"Attribute" ,
	    "100%Fill",              //填充 
	    "50%Fill",
		"NotFill",           //不填充 
		"Lwidth+ | Ctrl-Y",  //增加线粗 
		"Lwidth- | Ctrl-Z"}; //减小线粗 
	static char * menuListColor[] = {"Color",
	    "Red",
	    "Yellow", 
	    "Blue",
	    "Green",
	    "Black",
		"Brown",
		"Violet",
		"Magenta",
		"Cyan",
		"Orange",
		"Light Gray",
		"Light Brown"};
	static char * menuListDraw[] = {"Draw",
		"Rectangle|Ctrl-A",          //矩形 
		"Rounded rectangle|Ctrl-B",          //圆角矩形 
		"Rhombus|Ctrl-H",          //菱形 
		"CenteredEllipse|Ctrl-G",          //圆形 
		"Arrow|Ctrl-W",          //箭头
		"Line|Ctrl-L",          //线条 
		"Parallelogram|Ctrl-P",          //平行四边形 
		"Text|Ctrl-X"};         //图形框 
	static char * menuListHelp[] = {"Help",
		"usage method", //使用方法 
		"About"};       //关于本程序 
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListAttribute[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListDraw[2])*1.2;
	double wlist1 = TextStringWidth(menuListAttribute[2]);
	double wlist2 = TextStringWidth(menuListColor[2])*2;
	int selection;
	int selection1;
	int i;
	linklist *p;
	Rec a = NULL;
    Rou b = NULL;
	Rho c = NULL;
	Cen d = NULL;
	Arr e = NULL;
	Lin f = NULL;
	Par g = NULL;
	Tex h1 = NULL;
	
	
	// menu bar
	drawMenuBar(0,y-h,winwidth,h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection>0 ) selectedLabel = menuListFile[selection];
	if( selection==1) {//open
	
		if((fo1=fopen("Rectangle.dat","rb+"))==NULL);
		else //if(fgetc(fo1) != EOF){
			while(feof(fo1)==0){
				a=GetBlock(sizeof(*a));
			    fread(a,sizeof(Rect),1,fo1);
			    Insert(list[Rectangle], NULL, a);
			}
		//}
		if((fo2=fopen("Roundedrectangle.dat","rb+"))==NULL);
		else //if(fgetc(fo2) != EOF){
			while(feof(fo2)==0){
				b=GetBlock(sizeof(*b));
			    fread(b,sizeof(Roun),1,fo2);
			    Insert(list[Roundedrectangle], NULL, b);
			}
		//}
		if((fo3=fopen("Rhombus.dat","rb+"))==NULL);
		else //if(fgetc(fo3) != EOF){
			while(feof(fo3)==0){
				c=GetBlock(sizeof(*c));
			    fread(c,sizeof(Rhom),1,fo3);
			    Insert(list[Rhombus], NULL, c);
			}
		//}
		if((fo4=fopen("CenteredEllipse.dat","rb+"))==NULL);
		else //if(fgetc(fo4) != EOF){
			while(feof(fo4)==0){
				d=GetBlock(sizeof(*d));
			    fread(d,sizeof(Cent),1,fo4);
			    Insert(list[CenteredEllipse], NULL, d);
			}
		//}
		if((fo5=fopen("Arrow.dat","rb+"))==NULL);
		else //if(fgetc(fo5) != EOF){
			while(feof(fo5)==0){
				e=GetBlock(sizeof(*e));
			    fread(e,sizeof(Arro),1,fo5);
			    Insert(list[Arrow], NULL, e);
			}
		//}
		if((fo6=fopen("Line.dat","rb+"))==NULL);
		else //if(fgetc(fo6) != EOF){
			while(feof(fo6)==0){
				f=GetBlock(sizeof(*f));
			    fread(f,sizeof(Line1),1,fo6);
			    Insert(list[Line], NULL, f);
			}
		//}
		if((fo7=fopen("Parallelogram.dat","rb+"))==NULL);
		else //if(fgetc(fo7) != EOF){
			while(feof(fo7)==0){
				g=GetBlock(sizeof(*g));
			    fread(g,sizeof(Para),1,fo7);
			    Insert(list[Parallelogram], NULL, g);
			}
		//}
		if((fo8=fopen("Text.dat","rb+"))==NULL);
		else //if(fgetc(fo8) != EOF){
			while(feof(fo8)==0){
				h1=GetBlock(sizeof(*h1));
			    fread(h1,sizeof(Text1),1,fo8);
			    Insert(list[Text], NULL, h1);
			}
		//}
		
		fclose(fo1);
		fclose(fo2);
		fclose(fo3);
		fclose(fo4);
		fclose(fo5);
		fclose(fo6);
		fclose(fo7);
		fclose(fo8);
		
		display();
		
	}
	else if( selection==2){//save
	
		if((fp1=fopen("Rectangle.dat","wb+"))==NULL);
		else{
			p=list[Rectangle];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Rect),1,fp1);
				p=p->next;
			}
		}
		if((fp2=fopen("Roundedrectangle.dat","wb+"))==NULL);
		else{
			p=list[Roundedrectangle];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Roun),1,fp2);
				p=p->next;
			}
		}
		if((fp3=fopen("Rhombus.dat","wb+"))==NULL);
		else{
			p=list[Rhombus];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Rhom),1,fp3);
				p=p->next;
			}
		}
		if((fp4=fopen("CenteredEllipse.dat","wb+"))==NULL);
		else{
			p=list[CenteredEllipse];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Cent),1,fp4);
				p=p->next;
			}
		}
		if((fp5=fopen("Arrow.dat","wb+"))==NULL);
		else{
			p=list[Arrow];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Arro),1,fp5);
				p=p->next;
			}
		}
		if((fp6=fopen("Line.dat","wb+"))==NULL);
		else{
			p=list[Line];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Line1),1,fp6);
				p=p->next;
			}
		}
		if((fp7=fopen("Parallelogram.dat","wb+"))==NULL);
		else{
			p=list[Parallelogram];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Para),1,fp7);
				p=p->next;
			}
		}
		if((fp8=fopen("Text.dat","wb+"))==NULL);
		else{
			p=list[Text];//->next;
			while(p!=NULL){
				fwrite(p->dataptr,sizeof(Text1),1,fp8);
				p=p->next;
			}
		}
		
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		fclose(fp4);
		fclose(fp5);
		fclose(fp6);
		fclose(fp7);
		fclose(fp8);
		
		display();
		
	}
	if( selection==3 )
		exit(-1); // choose to exit
	if( selection==4 ){
		Deletelink();
		display();
	}
	
	// Edit 菜单
	selection = menuList(GenUIID(0),x+w, y-h, w, wlist,h, menuListEdit,sizeof(menuListEdit)/sizeof(menuListEdit[0]));
	if( selection>0 ) selectedLabel = menuListEdit[selection];
	if( selection ==1 ){isSelected = TRUE;isSelected1 = TRUE;isclick = FALSE;isclick1 = FALSE;isclick2 = TRUE;}
	else if( selection ==2 ){//copy 
	    if (curList1 == Rectangle){
	    	a1 = GetBlock(sizeof(*a1));
		    a1->x1 = curRectangle->x1+1;
         	a1->y1 = curRectangle->y1+1;
         	a1->x2 = curRectangle->x2+1;
         	a1->y2 = curRectangle->y2+1;
         	a1->PenSize = curRectangle->PenSize;
			a1->color = curRectangle->color;
			a1->isSelected = FALSE;
			a1->isfilling = curRectangle->isfilling;
			a1->num1 = curRectangle->num1;
			a1->num2 = curRectangle->num2;
			strcpy(a1->memo,curRectangle->memo);
	    }
	    else if (curList1 == Roundedrectangle){
	    	b1 = GetBlock(sizeof(*b1));
		    b1->x1 = curRoundedrectangle->x1+1;
         	b1->y1 = curRoundedrectangle->y1+1;
         	b1->x2 = curRoundedrectangle->x2+1;
         	b1->y2 = curRoundedrectangle->y2+1;
         	b1->PenSize = curRoundedrectangle->PenSize;
			b1->color = curRoundedrectangle->color;
			b1->isSelected = FALSE;
			b1->isfilling = curRoundedrectangle->isfilling;
			b1->num1 = curRoundedrectangle->num1;
			b1->num2 = curRoundedrectangle->num2;
			strcpy(b1->memo,curRoundedrectangle->memo);
	    }
	    else if (curList1 == Rhombus){
	    	c1 = GetBlock(sizeof(*c1));
		    c1->x1 = curRhombus->x1+1;
         	c1->y1 = curRhombus->y1+1;
         	c1->x2 = curRhombus->x2+1;
         	c1->y2 = curRhombus->y2+1;
         	c1->PenSize = curRhombus->PenSize;
			c1->color = curRhombus->color;
			c1->isSelected = FALSE;
			c1->isfilling = curRhombus->isfilling;
			c1->num1 = curRhombus->num1;
			c1->num2 = curRhombus->num2;
			strcpy(c1->memo,curRhombus->memo);
	    }
	    else if (curList1 == CenteredEllipse){
	    	d1 = GetBlock(sizeof(*d1));
		    d1->x1 = curCenteredEllipse->x1+1;
         	d1->y1 = curCenteredEllipse->y1+1;
         	d1->x2 = curCenteredEllipse->x2+1;
         	d1->y2 = curCenteredEllipse->y2+1;
         	d1->PenSize = curCenteredEllipse->PenSize;
			d1->color = curCenteredEllipse->color;
			d1->isSelected = FALSE;
			d1->isfilling = curCenteredEllipse->isfilling;
			d1->num1 = curCenteredEllipse->num1;
			d1->num2 = curCenteredEllipse->num2;
			strcpy(d1->memo,curCenteredEllipse->memo);
	    }
	    else if (curList1 == Arrow){
	    	e1 = GetBlock(sizeof(*e1));
		    e1->x1 = curArrow->x1+1;
         	e1->y1 = curArrow->y1+1;
         	e1->x2 = curArrow->x2+1;
         	e1->y2 = curArrow->y2+1;
         	e1->PenSize = curArrow->PenSize;
			e1->color = curArrow->color;
			e1->isSelected = FALSE;
			e1->isfilling = curArrow->isfilling;
	    }
	    else if (curList1 == Line){
	    	f1 = GetBlock(sizeof(*f1));
		    f1->x1 = curLine->x1+1;
         	f1->y1 = curLine->y1+1;
         	f1->x2 = curLine->x2+1;
         	f1->y2 = curLine->y2+1;
         	f1->PenSize = curLine->PenSize;
			f1->color = curLine->color;
			f1->isSelected = FALSE;
			f1->isfilling = curLine->isfilling;
	    }
	    else if (curList1 == Parallelogram){
	    	g1 = GetBlock(sizeof(*g1));
		    g1->x1 = curParallelogram->x1+1;
         	g1->y1 = curParallelogram->y1+1;
         	g1->x2 = curParallelogram->x2+1;
         	g1->y2 = curParallelogram->y2+1;
         	g1->PenSize = curParallelogram->PenSize;
			g1->color = curParallelogram->color;
			g1->isSelected = FALSE;
			g1->isfilling = curParallelogram->isfilling;
			g1->num1 = curParallelogram->num1;
			g1->num2 = curParallelogram->num2;
			strcpy(g1->memo,curParallelogram->memo);
	    }
	    else if (curList1 == Text){
	    	h2 = GetBlock(sizeof(*h1));
		    h2->x1 = curText->x1+1;
         	h2->y1 = curText->y1+1;
         	h2->x2 = curText->x2+1;
         	h2->y2 = curText->y2+1;
         	h2->PenSize = curText->PenSize;
			h2->color = curText->color;
			h2->isSelected = FALSE;
			h2->isfilling = curText->isfilling;
			h2->num1=curText->num1;
			h2->num2=curText->num2;
			strcpy(h2->memo,curText->memo);
	    }
	}
	else if( selection ==3 ){//paste 
		if (curList1 == Rectangle && a1 != NULL){
			Insert(list[Rectangle], NULL, a1);
			startTimer(TIMER_BLINK500, mseconds500);
		}
		else if (curList1 == Roundedrectangle && b1 != NULL){
			Insert(list[Roundedrectangle], NULL, b1);
			startTimer(TIMER_BLINK500, mseconds500);
		}
		else if (curList1 == Rhombus && c1 != NULL){
			Insert(list[Rhombus], NULL, c1);
			startTimer(TIMER_BLINK500, mseconds500);
		}
		else if (curList1 == CenteredEllipse && d1 != NULL){	
			Insert(list[CenteredEllipse], NULL, d1);
			startTimer(TIMER_BLINK500, mseconds500);
		}
		else if (curList1 == Arrow && e1 != NULL){
			Insert(list[Arrow], NULL, e1);
		}
		else if (curList1 == Line && f1 != NULL){
			Insert(list[Line], NULL, f1);
		}
		else if (curList1 == Parallelogram && g1 != NULL){
			Insert(list[Parallelogram], NULL, g1);
			startTimer(TIMER_BLINK500, mseconds500);
		}
		else if (curList1 == Text && h1 != NULL){
			Insert(list[Text], NULL, h2);
			startTimer(TIMER_BLINK500, mseconds500);
		}
	}
	
    //Attribute 菜单
	selection = menuList(GenUIID(0),x+2*w, y-h, w, wlist,h, menuListAttribute,sizeof(menuListAttribute)/sizeof(menuListAttribute[0]));
	if( selection>0 ) selectedLabel = menuListAttribute[selection];
	
	if( selection==1) {
		isFill = TRUE;
		fillpercent = 1;
	}
	if( selection==2) {
		isFill = TRUE;
		fillpercent = 0.5;
	}
	if( selection==3) isFill = FALSE;
	if( selection==4) IsPenSize++;
	if( selection==5){
		if(IsPenSize>1)IsPenSize--;
	}
	
	//Color菜单
	selection = menuList(GenUIID(0),x+3*w, y-h, w, wlist,h, menuListColor,sizeof(menuListColor)/sizeof(menuListColor[0]));
	if( selection>0 ) selectedLabel = menuListColor[selection];
    if( selection==1 ) {isColor = 1;}
    else if( selection==2 ) {isColor = 2;}
    else if( selection==3 ) {isColor = 3;}
    else if( selection==4 ) {isColor = 4;}
    else if( selection==5 ) {isColor = 5;}
    else if( selection==6 ) {isColor = 6;}
    else if( selection==7 ) {isColor = 7;}
    else if( selection==8 ) {isColor = 8;}
    else if( selection==9 ) {isColor = 9;}
    else if( selection==10 ) {isColor = 10;}
    else if( selection==11 ) {isColor = 11;}
    else if( selection==12 ) {isColor = 12;}
	
	// Draw 菜单
	selection = menuList(GenUIID(0),x+4*w, y-h, w, wlist,h, menuListDraw,sizeof(menuListDraw)/sizeof(menuListDraw[0]));
	if( selection>0 ) selectedLabel = menuListDraw[selection];
    if( selection==1 ) {isRectangle = TRUE;isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==2 ) {isRoundedrectangle = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==3 ) {isRhombus = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==4 ) {isCenteredEllipse = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==5 ) {isArrow = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==6 ) {isLine = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==7 ) {isParallelogram = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
    else if( selection==8 ) {isText = TRUE; isclick1 = TRUE;isSelected = FALSE;isSelected1 = FALSE;isclick2 = TRUE;}
	
	// Help 菜单
	selection = menuList(GenUIID(0),x+5*w, y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection>0 ) selectedLabel = menuListHelp[selection];
	if( selection == 1) {
		if(usage == FALSE) usage = TRUE;
		else usage = FALSE;
	}
}
