// 双缓冲绘图.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include<windows.h>
#include <io.h>
#include <map>
#include <fstream>
#include <atlimage.h>
#include "afxwin.h"
#include <string.h>
using namespace std;

int flag = 0;
//词汇库
char textlib[] = "焦虑 紧张 愤怒 沮丧 悲伤 痛苦 愤怒 抱怨 自责 悔恨 担忧 不安 郁闷 伤心 难过 失望 堕落 烦躁 生气 ";
char text[100];

//字符大小
int textw = 100;
int texth = 60;
RECT rect;

void getnextchar() {
	int n = flag;
	while (textlib[n] != ' ')
	{
		n++;
		if (n >= strlen(textlib))
		{
			n = 0;
			flag = 0;
		}
	}
	strncpy(text, textlib + flag, n - flag);
	flag = n + 1;
}

void drawtop(int x, int y)
{
	HDC hdc = GetWindowDC(GetForegroundWindow());
	//根据绘图点设定颜色	COLORREF clr=GetPixel(hdc,x,y);	
	//根据获得的颜色修正，暗色加亮，亮色减弱	
	int bright;
	int r = 100, g = 100, b = 100;
	bright = 0.299*r + 0.587*g + 0.114*b;
	if (bright > 127) {
		r = r * 2 / 3;
		g = g * 2 / 3;
		b = b * 2 / 3;
	}
	else if (bright > 20 && bright <= 127)
	{
		r = r * 3 / 2;
		g = g * 3 / 2;
		b = b * 3 / 2;
	}
	else
	{
		r += 20;
		g += 20;
		b += 20;
	}
	//	
	CFont font;	 
	font.CreateFont(
		textw,                                                  //   nHeight      
		texth,                                                   //   nWidth     
		0,                                                   //   nEscapement   
		0,                                                   //   nOrientation    
		FW_NORMAL,                                   //   nWeight   
		FALSE,                                           //   bItalic      
		FALSE,                                           //   bUnderline    
		0,                                                   //   cStrikeOut     
		ANSI_CHARSET,                             //   nCharSet      
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision      
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision     
		DEFAULT_QUALITY,                       //   nQuality      
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily        
		_T("宋体"));	 getnextchar();	 //  // 使用双缓冲避免屏幕刷新时闪烁	
	CDC dc;	 dc.Attach(hdc);      CDC dcMem;// 内存dc   
	CBitmap bmpMem; // 位图	
	dcMem.CreateCompatibleDC(NULL);// 创建兼容dc  
	bmpMem.CreateCompatibleBitmap(&dc, rect.right - rect.left + textw, rect.bottom - rect.top + texth);
	//创建跟客户区域大小一样的(空)位图    
	// 把位图选到设备上下文环境中  
	CBitmap *pOld = dcMem.SelectObject(&bmpMem);
	//设置一下基本参数	
	//设置颜色	
	dcMem.SetTextColor(RGB(r, g, b));	//背景色透明	
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SelectObject(font);	 //先把背景复制下来
	dcMem.BitBlt(0, 0, rect.right - rect.left + textw, rect.bottom - rect.top + texth, &dc, 0, 0, SRCCOPY);
	//画图	
	dcMem.TextOutW(x, y, text);
	//dcMem.TextOutW(x, y, text, sizeof(text));
	// 从内存拷贝到设备dc    
	dc.BitBlt(0, 0, rect.right - rect.left + textw, rect.bottom - rect.top + texth, &dcMem, 0, 0, SRCCOPY);
	dc.SelectObject(pOld);
	// 释放资源   
	bmpMem.DeleteObject();
	dcMem.DeleteDC();
	ReleaseDC(NULL, hdc);
}

void  draw()
{
	// 先创建三个HDC缓冲对象
	HDC hdc = NULL, mdc = NULL;
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
		int seed; 	
		int randomx;	
		int randomy;	
		srand(unsigned(time(0)));
		//自己按ctrl+c退出
		while(true)	{	
			HWND hwnd=GetForegroundWindow();  	
			GetWindowRect(hwnd,&rect); 		
			seed=rand();		
			srand(seed);		
			randomx=rand()%(rect.right-rect.left-textw);	
			seed=rand();		
			srand(seed);	
			randomy=rand()%(rect.bottom-rect.top-texth);	
			if(randomx<0)		
				randomx=(-1)*randomx;	
			if(randomy<0)		
				randomy=(-1)*randomy;	
			drawtop(randomx+textw/2,randomy+texth/2);	
			Sleep(10);		
			//RedrawWindow(hwnd,&rect,0,RDW_ERASE|RDW_INVALIDATE|RDW_ALLCHILDREN);	
			RedrawWindow(hwnd,NULL,0,RDW_ERASE|RDW_INVALIDATE|RDW_ALLCHILDREN);	
			//InvalidateRect(hwnd, &rect, false);	
			Sleep(1000);	
		}  
		return 0;
}

