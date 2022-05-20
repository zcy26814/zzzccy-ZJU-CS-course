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

// 清屏函数，provided in libgraphics
void DisplayClear(void); 

// 菜单演示程序
void drawMenu(void);

void drawEditText(void);

// 用户的显示函数
void display(void);

// 用户的字符事件响应函数
void CharEventProcess(char c);

void TimerEventProcess(int timerID);

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event);

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event);

// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("");
	
    InitGraphics();
    
    int i;
    
    SetPenColor("Red"); 
    SetPenSize(1);
    
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);
	// 打开控制台，方便用printf/scanf输出/入变量信息，方便调试
	// InitConsole(); 
	for (i = 0; i < NLIST; i++) list[i] = Newlink();
}
