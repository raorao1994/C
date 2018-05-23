// 双缓冲绘图.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include<windows.h>
#include <io.h>
#include <map>
#include <fstream>
#include <atlimage.h>
using namespace std;

void  draw()
{
	// 先创建三个HDC缓冲对象
	HDC hdc=NULL, mdc = NULL;
	// 创建位图对象
	HBITMAP hBitmap;
	// 获取一个可供画图的DC，我这里就直接用桌面算了
	hdc = GetWindowDC(GetDesktopWindow());//获取设备环境句柄
	mdc = CreateCompatibleDC(hdc);//创建一个和g_hdc兼容的内存DC 
	//创建一个很窗口兼容的空位图对象
	//hBitmap = CreateCompatibleBitmap(hdc, 800, 600);
	// 创建绿色5像素宽度的破折画笔，如果你想创建其他种类的画笔请参阅MSDN
	HPEN hpen = CreatePen(PS_DASH, 5, RGB(0, 255, 0));
	// 换hpen1和hbrush1，然后在(40,100)处也画一个矩形，看看有何差别
	SelectObject(mdc, hpen);
	Rectangle(mdc, 0, 0, 300, 400);
	BitBlt(hdc, 0, 0, 300, 400, mdc, 0, 0, SRCCOPY);
	// 恢复原来的画笔和画刷
	DeleteObject(hpen);
	DeleteObject(hdc);

	//SelectObject(mdc, hBitmap);//将位图放在g_mdc中 
	//electObject(bdc, bitmap);//bitmap代表位图对象，指将要绘制的图片.放入g_bdc中.
	//Bitble(g_mdc, 0, 0, WIN_WIDTH, WIN_HIGHT, g_bdc, 0, 0, SRCCOPY);//将g_bdc放到g_mdc中 
	//Bitble(g_hdc, 0, 0, WIN_WIDTH, WIN_HIGHT, g_mdc, 0, 0, SRCCOPY);//最后将g_mdc放入g_hdc中，这样就可以将图片显示在窗口中  
	//DeleteDC();
}

int main()
{
	while (true)
	{
		draw();
		Sleep(10);
	}
	system("prase");
}

