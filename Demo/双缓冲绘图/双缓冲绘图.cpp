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

//常量
HWND hwnd = NULL;
LONG height, width;

void init() 
{
	hwnd = GetDesktopWindow();
	LPRECT rect;
	GetWindowRect(hwnd, rect);
	height=rect->bottom;
	width = rect->right;
}

void  draw()
{
	// 获取一个可供画图的DC，我这里就直接用桌面算了
	HDC hdc = GetWindowDC(GetDesktopWindow());

	// 创建红色1像素宽度的实线画笔
	HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	// 创建绿色5像素宽度的破折画笔，如果你想创建其他种类的画笔请参阅MSDN
	HPEN hpen2 = CreatePen(PS_DASH, 5, RGB(0, 255, 0));
	// 创建一个实体蓝色画刷
	HBRUSH hbrush1 = CreateSolidBrush(RGB(0, 0, 255));
	// 创造一个透明的画刷，如果你想创建其他种类的画刷请参阅MSDN
	HBRUSH hbrush2 = (HBRUSH)GetStockObject(NULL_BRUSH);

	// 将hpen1和hbrush1选进HDC，并保存HDC原来的画笔和画刷
	HPEN hpen_old = (HPEN)SelectObject(hdc, hpen1);
	HBRUSH hbrush_old = (HBRUSH)SelectObject(hdc, hbrush1);

	// 在(40,30)处画一个宽200像素，高50像素的矩形
	Rectangle(hdc, 40, 30, 40 + 200, 30 + 50);

	// 换hpen1和hbrush1，然后在(40,100)处也画一个矩形，看看有何差别
	SelectObject(hdc, hpen2);
	SelectObject(hdc, hbrush2);
	Rectangle(hdc, 40, 100, 40 + 200, 100 + 50);

	// 画个椭圆看看
	Ellipse(hdc, 40, 200, 40 + 200, 200 + 50);

	// 画个(0,600)到(800,0)的直线看看
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 800, 0);

	// 在(700,500)处画个黄点，不过这个点只有一像素大小，你细细的看才能找到
	SetPixel(hdc, 700, 500, RGB(255, 255, 0));
	//文字，
	//参数：桌面句柄，XY坐标，文字，文字宽度
	TextOutA(hdc, 700, 500, "哈哈哈", 6);
	// 恢复原来的画笔和画刷
	SelectObject(hdc, hpen_old);
	SelectObject(hdc, hbrush_old);

	DeleteObject(hpen1);
	DeleteObject(hpen2);
	DeleteObject(hbrush1);
	DeleteObject(hbrush2);
	DeleteObject(hpen_old);
	DeleteObject(hbrush_old);
	DeleteObject(hdc);
}

void  draw1()
{
	HWND hwdn = GetDesktopWindow();
	HDC pDC= GetWindowDC(hwdn);
	//首先定义一个显示设备对象
	HDC MemDC;
	//定义一个位图对象　
	//随后建立与屏幕显示兼容的内存显示设备
	HBITMAP MemBitmap,oldBitmap;
	//这时还不能绘图，因为没有地方画 ^_^
	MemDC = CreateCompatibleDC(NULL);
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小，也可以自己定义
	MemBitmap = CreateCompatibleBitmap(pDC, 500, 500);
	//将位图选入到内存显示设备中　
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	oldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);
	//SelectObject(MemDC, oldBitmap);
	//先用背景色将位图清除干净，这里我用的是白色作为背景　//你也可以用自己应该用的颜色　
	// 创建红色1像素宽度的实线画笔
	HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hpen_old = (HPEN)SelectObject(pDC, hpen1);
	//FillRect(MemDC, rt, RGB(255, 255, 255));
	TextOutA(MemDC, 200, 300, "哈哈哈", 6);
	Rectangle(MemDC, 40, 30, 40 + 200, 30 + 50);
	//把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(MemDC, 0, 0, 500, 500, pDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, oldBitmap);

	DeleteObject(MemBitmap);
	DeleteObject(MemDC);
}

int main()
{
	init()
	//自己按ctrl+c退出
	while (true) {
		draw1();
		Sleep(100);
	}
	return 0;
}

