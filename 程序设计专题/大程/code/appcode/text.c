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

void drawEditText()
{
	MovePen(0,winheight/20);
	if (isSelected){
		if (curList == Rectangle)
		   DrawTextString("The current status is isSelected. The figure is Rectangle.");
		else if (curList == Roundedrectangle)
		   DrawTextString("The current status is isSelected. The figure is Roundedrectangle.");
		else if (curList == Rhombus)
		   DrawTextString("The current status is isSelected. The figure is Rhombus.");
		else if (curList == CenteredEllipse)
		   DrawTextString("The current status is isSelected. The figure is CenteredEllipse.");
		else if (curList == Arrow)
		   DrawTextString("The current status is isSelected. The figure is Arrow.");
		else if (curList == Line)
		   DrawTextString("The current status is isSelected. The figure is Line.");
		else if (curList == Parallelogram)
		   DrawTextString("The current status is isSelected. The figure is Parallelogram.");
		else if (curList == Text)
		   DrawTextString("The current status is isSelected. The figure is Text.");
		else if (curList == NLIST)
		   DrawTextString("The current status is isSelected.");
	}
	else if (isclick1){
		if (isRectangle)
		   DrawTextString("The current status is drawing. The figure is Rectangle.");
		else if (isRoundedrectangle)
		   DrawTextString("The current status is drawing. The figure is Roundedrectangle.");
		else if (isRhombus)
		   DrawTextString("The current status is drawing. The figure is Rhombus.");
		else if (isCenteredEllipse)
		   DrawTextString("The current status is drawing. The figure is CenteredEllipse.");
		else if (isArrow)
		   DrawTextString("The current status is drawing. The figure is Arrow.");
		else if (isLine)
		   DrawTextString("The current status is drawing. The figure is Line.");
		else if (isParallelogram)
		   DrawTextString("The current status is drawing. The figure is Parallelogram.");
		else if (isText)
		   DrawTextString("The current status is drawing. The figure is Text.");
	}
	else{
	    DrawTextString("The current status is Standby.");
	if(usage == TRUE){
	Help(1);
	if(usage == FALSE){
	}}
}
}
