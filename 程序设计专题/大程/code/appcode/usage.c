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

void Help(bool k){
	if(k==1){
    MovePen(0.2,6);
	DrawTextString("HELLO_这里是小型算法流程图绘制工具的使用说明^ ^");
	MovePen(0.2,5.5);
	DrawTextString("①画图状态下单击鼠标右键退出后可改变图形类型/退出画图状态");
	MovePen(0.2,5);
	DrawTextString("②在画图前选择颜色/填充状况后再使用画图工具可改变图形的属性");
	MovePen(0.2,4.5);
	DrawTextString("③画图状态下可按下Ctrl+Y增大线粗/Ctrl+Z减小线粗");
	MovePen(0.2,4);
	DrawTextString("④选中状态下可以拖动鼠标移动图形；选中状态同样需要单击鼠标右键退出");
	MovePen(0.2,3.5);
	DrawTextString("⑤绘制图形后选中该图形可直接输入文字");
	MovePen(0.2,3);
	DrawTextString("⑥保存/打开单击File->Save/File->Open或Ctrl+S/Ctrl+O,单击File->New或Ctrl+N可清空屏幕");
	MovePen(0.2,2.5);
	DrawTextString("⑦退出选中状态后单击Edit->Copy/Ctrl+C可对退出选中状态前的最后一个图形进行复制");
	MovePen(0.2,2);
	DrawTextString("⑧进行复制后Ctrl+V/单击Edit->Paste可进行粘贴");
	MovePen(0.2,1.5);
	DrawTextString("⑨选中后键盘按下Delete/Ctrl+D可删除图形");
	MovePen(0.2,1);
	DrawTextString("⑩再次单击Help - usage method退出使用说明");
}
}
