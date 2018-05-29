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
HDC m_hDC;
HBITMAP m_hBmpOld;
LONG height, width;

void init()
{
	hwnd = GetDesktopWindow();
	HDC hDC = ::GetDC(hwnd);  // 得到屏幕DC  
	m_hDC = CreateCompatibleDC(hDC);
	width = ::GetDeviceCaps(hDC, HORZRES);// 宽  
	height = ::GetDeviceCaps(hDC, VERTRES);// 高   
	::ReleaseDC(HWND(NULL), hDC);// 释放DC
	//创建一个与屏幕设备描述表兼容的 位图
	HBITMAP hbmp = CreateCompatibleBitmap(m_hDC, width, height);
	//把新位图选到内存设备描述表中
	m_hBmpOld = (HBITMAP)SelectObject(m_hDC, hbmp);
}

void UpdateLayeredContent()
{
	

	HDC dcWnd = GetDC(hwnd); 
	Rectangle(dcWnd, 40, 30, 40 + 200, 30 + 50);
	BLENDFUNCTION blf;
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = 255;
	blf.AlphaFormat = AC_SRC_ALPHA;

	RECT rcWnd = { 0 };
	GetWindowRect(hwnd, &rcWnd);
	SIZE sizeWnd = { rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top };
	POINT ptWnd = { rcWnd.left, rcWnd.top };
	POINT ptSrc = { 0 };
	UpdateLayeredWindow(hwnd, dcWnd, &ptWnd, &sizeWnd, m_hDC, &ptSrc, 0, &blf, ULW_ALPHA);
}

//测试
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
	HDC pDC = GetWindowDC(hwdn);
	//首先定义一个显示设备对象
	HDC MemDC;
	//定义一个位图对象　
	//随后建立与屏幕显示兼容的内存显示设备
	HBITMAP MemBitmap, oldBitmap;
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

//截图3
BOOL SaveBitmapToFile(HBITMAP   hBitmap, string szfilename)
{
	HDC hScrDC;
	HDC     hDC;
	//当前分辨率下每象素所占字节数            
	int     iBits;
	//位图中每象素所占字节数            
	WORD     wBitCount;
	//定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数                
	DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	//位图属性结构                
	BITMAP     Bitmap;
	//位图文件头结构            
	BITMAPFILEHEADER     bmfHdr;
	//位图信息头结构                
	BITMAPINFOHEADER     bi;
	//指向位图信息头结构                    
	LPBITMAPINFOHEADER     lpbi;
	//定义文件，分配内存句柄，调色板句柄                
	HANDLE     fh, hDib, hPal, hOldPal = NULL;

	//计算位图文件每个像素所占字节数                
	hDC = ::GetDC(hwnd);
	iBits = GetDeviceCaps(hDC, BITSPIXEL)     *     GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else  if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 0;

	dwBmBitsSize = ((Bitmap.bmWidth *wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//为位图内容分配内存                
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	//     处理调色板                    
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//     获取该调色板下新的像素值                
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);

	//恢复调色板                    
	if (hOldPal)
	{
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	//创建位图文件                    
	/*fh = CreateFile("123", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);*/

	//if (fh == INVALID_HANDLE_VALUE)         return     FALSE;

	//     设置位图文件头                
	bmfHdr.bfType = 0x4D42;     //     "BM"                
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	//     写入位图文件头                
	//WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	//     写入位图文件其余内容                
	//WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//清除                    
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	//CloseHandle(fh);

	return     TRUE;

}

int main()
{
	init(); UpdateLayeredContent();
	//自己按ctrl+c退出
	while (true)
	{
		//UpdateLayeredContent();
		//draw1();
		Sleep(100);
	}
	return 0;
}

