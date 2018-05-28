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
	HWND hwnd=NULL;
	RECT rc;
	HDC hdc = GetWindowDC(GetDesktopWindow());
	GetClientRect(hwnd, &rc);
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDc, hBmp);
	//在此使用hMemDc进行 GDI 绘制  
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, hMemDc, 0, 0, SRCCOPY);
	SelectObject(hMemDc, hOldBmp);
	DeleteObject(hBmp);
	DeleteObject(hMemDc);
}

int main()
{
	//自己按ctrl+c退出
	while (true) {
		draw1();
	}
	return 0;
}

