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


void MouseEventProcess(int x, int y, int button, int event)
{
    double mx, my;/*当前鼠标坐标*/
	static Rec a = NULL;
	static Rou b = NULL;
	static Rho c = NULL;
	static Cen d = NULL;
	static Arr e = NULL;
	static Lin f = NULL;
	static Par g = NULL;
	static Tex h = NULL;
	int i;
	static double omy;
    static double omx;
    double dx,dy,x1,y1,x2,y2;
	
 	mx = ScaleXInches(x);/*pixels --> inches*/
	my = ScaleYInches(y);/*pixels --> inches*/
    
    if (isclick2 == FALSE){
    	uiGetMouse(x,y,button,event); //GUI获取鼠标
	    display(); // 刷新显示
    }
    else if (isclick2){
	switch (event) {
		case BUTTON_DOWN:
			  if (button == LEFT_BUTTON){
				 if (isSelected){
				 	ismove = TRUE;
				 	omx = mx;
			        omy = my;
			 	 if (isSelected1){
				 	Picknearest(list, mx, my);
		            switch (curList) {
         	            case Rectangle:
         	  		        if (curRectangle != NULL){
         	  	     	       curRectangle->isSelected = TRUE;
         	  	     	       for(i=0;i<curRectangle->num1;i++)
         	  	     	       rect1[i]=curRectangle->memo[i];
         	  	     	       rect1[i]='\0';
         	  		        }
         	  		        break;
         	  	        case Roundedrectangle:
         	  	    	    if (curRoundedrectangle != NULL){
         	  	    	 	   curRoundedrectangle->isSelected = TRUE;
         	  	    	 	   for (i=0;i<curRoundedrectangle->num1;i++)//记录当前位置前的字符串 
		                           roun1[i]=curRoundedrectangle->memo[i];
	                           roun1[i]='\0';
         	  	    	    }
         	  		        break;
         	  	        case Rhombus:
         	  	    	    if (curRhombus != NULL){
         	  	    	 	   curRhombus->isSelected = TRUE;
         	  	    	 	   for (i=0;i<curRhombus->num1;i++)//记录当前位置前的字符串 
		                           rhom1[i]=curRhombus->memo[i];
	                           rhom1[i]='\0';
         	  	    	    }
         	  		        break;
         	  	        case CenteredEllipse:
         	  	    	    if (curCenteredEllipse != NULL){
         	  	    	 	   curCenteredEllipse->isSelected = TRUE;
         	  	    	 	   for (i=0;i<curCenteredEllipse->num1;i++)//记录当前位置前的字符串 
		                           cent1[i]=curCenteredEllipse->memo[i];
	                           cent1[i]='\0';
         	  	    	    }
         	  		        break;
         	  	        case Arrow:
         	  	    	    if (curArrow != NULL){
         	  	    	 	   curArrow->isSelected = TRUE;
         	  	    	    }
         	  		        break;
         	  	        case Line:
         	  	    	    if (curLine != NULL){
         	  	    	       curLine->isSelected = TRUE;
         	  	    	    }
         	  		        break;
         	  	        case Parallelogram:
         	  	    	    if (curParallelogram != NULL){
         	  	    	 	   curParallelogram->isSelected = TRUE;
         	  	    	 	   for (i=0;i<curParallelogram->num1;i++)//记录当前位置前的字符串 
		                           para1[i]=curParallelogram->memo[i];
	                           para1[i]='\0';
         	  	    	    }
         	  		        break;
         	  	        case Text:
         	  	    	    if (curText != NULL){
         	  	    	 	   curText->isSelected = TRUE;
         	  	    	 	   for (i=0;i<curText->num1;i++)//记录当前位置前的字符串 
		                           text1[i]=curText->memo[i];
	                           text1[i]='\0';
         	  	    	    }
         	  		        break;
         	        }
         	        isSelected1 = FALSE;
         	     }
                 }
                 if (isclick1){
                 	isclick = TRUE;
         	     if (isclick && isRectangle){
         	 	     a = GetBlock(sizeof(*a));
				     a->x1 = mx;
         		     a->y1 = my;
         		     a->x2 = mx;
         		     a->y2 = my;
         		     a->PenSize = IsPenSize;
					 a->color = isColor;
					 a->isSelected = FALSE;
					 a->isfilling = isFill;
					 a->fillpercent = fillpercent;
					 strcpy(a->memo,"");
					 a->num1 = 0;
					 a->num2 = 0;
         		     Insert(list[Rectangle], NULL, a);
         		     startTimer(TIMER_BLINK500, mseconds500);
         	      }
         	      else if (isclick && isRoundedrectangle){
         	      	 b = GetBlock(sizeof(*b));
				     b->x1 = mx;
         		     b->y1 = my;
         		     b->x2 = mx;
         		     b->y2 = my;
         		     b->PenSize = IsPenSize;
					 b->color = isColor;
					 b->isSelected = FALSE;
					 b->isfilling = isFill;
					 b->fillpercent = fillpercent;
					 strcpy(b->memo,"");
					 b->num1 = 0;
					 b->num2 = 0;
         		     Insert(list[Roundedrectangle], NULL, b);
         		     startTimer(TIMER_BLINK500, mseconds500);
         	      }
         	      else if (isclick && isRhombus){
         	      	 c = GetBlock(sizeof(*c));
				     c->x1 = mx;
         		     c->y1 = my;
         		     c->x2 = mx;
         		     c->y2 = my;
         		     c->PenSize = IsPenSize;
					 c->color = isColor;
					 c->isSelected = FALSE;
					 c->isfilling = isFill;
					 c->fillpercent = fillpercent;
					 strcpy(c->memo,"");
					 c->num1 = 0;
					 c->num2 = 0;
         		     Insert(list[Rhombus], NULL, c);
         		     startTimer(TIMER_BLINK500, mseconds500);
         	      }
         	      else if (isclick && isCenteredEllipse){
         	      	 d = GetBlock(sizeof(*d));
				     d->x1 = mx;
         		     d->y1 = my;
         		     d->x2 = mx;
         		     d->y2 = my;
         		     d->PenSize = IsPenSize;
					 d->color = isColor;
					 d->isSelected = FALSE;
					 d->isfilling = isFill;
					 d->fillpercent = fillpercent;
					 strcpy(d->memo,"");
					 d->num1 = 0;
					 d->num2 = 0;
         		     Insert(list[CenteredEllipse], NULL, d);
         		     startTimer(TIMER_BLINK500, mseconds500);
         	      }
         	      else if (isclick && isArrow){
         	      	 e = GetBlock(sizeof(*e));
				     e->x1 = mx;
         		     e->y1 = my;
         		     e->x2 = mx;
         		     e->y2 = my;
         		     e->PenSize = IsPenSize;
					 e->color = isColor;
					 e->isSelected = FALSE;
					 e->isfilling = isFill;
         		     Insert(list[Arrow], NULL, e);
         	      }
         	      else if (isclick && isLine){
         	      	 f = GetBlock(sizeof(*f));
				     f->x1 = mx;
         		     f->y1 = my;
         		     f->x2 = mx;
         		     f->y2 = my;
         		     f->PenSize = IsPenSize;
					 f->color = isColor;
					 f->isSelected = FALSE;
					 f->isfilling = isFill;
         		     Insert(list[Line], NULL, f);
         	      }
         	      else if (isclick && isParallelogram){
         	      	 g = GetBlock(sizeof(*g));
				     g->x1 = mx;
         		     g->y1 = my;
         		     g->x2 = mx;
         		     g->y2 = my;
         		     g->PenSize = IsPenSize;
					 g->color = isColor;
					 g->isSelected = FALSE;
					 g->isfilling = isFill;
					 g->fillpercent = fillpercent;
					 strcpy(g->memo,"");
					 g->num1 = 0;
					 g->num2 = 0;
         		     Insert(list[Parallelogram], NULL, g);
         		     startTimer(TIMER_BLINK500, mseconds500);
         	      }
         	      else if (isclick && isText){
         	      	 h = GetBlock(sizeof(*h));
				     h->x1 = mx;
         		     h->y1 = my;
         		     h->x2 = mx;
         		     h->y2 = my;
         		     h->PenSize = IsPenSize;
					 h->color = isColor;
					 h->isSelected = FALSE;
					 strcpy(h->memo,"");
					 h->num1 = 0;
					 h->num2 = 0;
         		     Insert(list[Text], NULL, h);
         		     startTimer(TIMER_BLINK500, mseconds500);
         	      }
             }
             }
             else if (button == RIGHT_BUTTON){
			 	 switch (curList) {
         	            case Rectangle:
         	  		        if (curRectangle != NULL){
         	  	     	       curRectangle->isSelected = FALSE;
         	  		        }
         	  		        break;
         	  	        case Roundedrectangle:
         	  	    	    if (curRoundedrectangle != NULL){
         	  	    	 	   curRoundedrectangle->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	  	        case Rhombus:
         	  	    	    if (curRhombus != NULL){
         	  	    	 	   curRhombus->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	  	        case CenteredEllipse:
         	  	    	    if (curCenteredEllipse != NULL){
         	  	    	 	   curCenteredEllipse->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	  	        case Arrow:
         	  	    	    if (curArrow != NULL){
         	  	    	 	   curArrow->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	  	        case Line:
         	  	    	    if (curLine != NULL){
         	  	    	       curLine->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	  	        case Parallelogram:
         	  	    	    if (curParallelogram != NULL){
         	  	    	 	   curParallelogram->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	  	        case Text:
         	  	    	    if (curText != NULL){
         	  	    	 	   curText->isSelected = FALSE;
         	  	    	    }
         	  		        break;
         	      }
				 isSelected = FALSE;
				 isclick1 = FALSE;
			 	 isclick = FALSE;
			 	 isRectangle = FALSE;
			 	 isRoundedrectangle = FALSE;
			 	 isRhombus = FALSE;
			 	 isCenteredEllipse = FALSE;
			 	 isArrow = FALSE;
			 	 isLine = FALSE;
			 	 isParallelogram = FALSE;
			 	 curList1 = curList;
				 curList = NLIST;
			 	 isText = FALSE;
			 	 isclick2 = FALSE;
			 }
            break;
		case BUTTON_DOUBLECLICK:
			break;
		case BUTTON_UP:
			if (isclick){
				isclick = FALSE;
			}
			if (ismove){
				ismove = FALSE;
			}
            break;
		case MOUSEMOVE:
			if (isclick && isRectangle){
				if (a!=NULL){
					a->x2 = mx;
         		    a->y2 = my;
				}
			}
			else if (isclick && isRoundedrectangle){
				if (b!=NULL){
					b->x2 = mx;
         		    b->y2 = my;
				}
			}
			else if (isclick && isRhombus){
				if (c!=NULL){
					c->x2 = mx;
         		    c->y2 = my;
				}
			}
			else if (isclick && isCenteredEllipse){
				if (d!=NULL){
					d->x2 = mx;
         		    d->y2 = my;
				}
			}
			else if (isclick && isArrow){
				if (e!=NULL){
					e->x2 = mx;
         		    e->y2 = my;
				}
			}
			else if (isclick && isLine){
				if (f!=NULL){
					f->x2 = mx;
         		    f->y2 = my;
				}
			}
			else if (isclick && isParallelogram){
				if (g!=NULL){
					g->x2 = mx;
         		    g->y2 = my;
				}
			}
			else if (isclick && isText){
				if (h!=NULL){
					h->x2 = mx;
         		    h->y2 = my;
				}
			}
			if (isSelected){
				if (ismove){
					dx=mx-omx;
					dy=my-omy;
					switch (curList){
						case Rectangle:
							if (curRectangle != NULL){
								curRectangle->x1+=(0.000001*dx);
								curRectangle->y1+=(0.000001*dy);
								curRectangle->x2+=(0.000001*dx);
								curRectangle->y2+=(0.000001*dy);
							}
							break;
						case Roundedrectangle:
							if (curRoundedrectangle != NULL){
								curRoundedrectangle->x1+=(0.000001*dx);
								curRoundedrectangle->y1+=(0.000001*dy);
								curRoundedrectangle->x2+=(0.000001*dx);
								curRoundedrectangle->y2+=(0.000001*dy);
							}
							break;
						case Rhombus:
							if (curRhombus != NULL){
								curRhombus->x1+=(0.000001*dx);
								curRhombus->y1+=(0.000001*dy);
								curRhombus->x2+=(0.000001*dx);
								curRhombus->y2+=(0.000001*dy);
							}
							break;
						case CenteredEllipse:
							if (curCenteredEllipse != NULL){
								curCenteredEllipse->x1+=(0.000001*dx);
								curCenteredEllipse->y1+=(0.000001*dy);
								curCenteredEllipse->x2+=(0.000001*dx);
								curCenteredEllipse->y2+=(0.000001*dy);
							}
							break;
						case Arrow:
							if (curArrow != NULL){
								curArrow->x1+=(0.000001*dx);
								curArrow->y1+=(0.000001*dy);
								curArrow->x2+=(0.000001*dx);
								curArrow->y2+=(0.000001*dy);
							}
							break;
						case Line:
							if (curLine != NULL){
								curLine->x1+=(0.000001*dx);
								curLine->y1+=(0.000001*dy);
								curLine->x2+=(0.000001*dx);
								curLine->y2+=(0.000001*dy);
							}
							break;
						case Parallelogram:
							if (curParallelogram != NULL){
								curParallelogram->x1+=(0.000001*dx);
								curParallelogram->y1+=(0.000001*dy);
								curParallelogram->x2+=(0.000001*dx);
								curParallelogram->y2+=(0.000001*dy);
							}
							break;
						case Text:
							if (curText != NULL){
								curText->x1+=(0.000001*dx);
								curText->y1+=(0.000001*dy);
								curText->x2+=(0.000001*dx);
								curText->y2+=(0.000001*dy);
							}
							break;
					}
				}
			}
		    break;
	}
	display();
    }
}
