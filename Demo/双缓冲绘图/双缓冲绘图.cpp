// ˫�����ͼ.cpp : �������̨Ӧ�ó������ڵ㡣
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
//�ʻ��
char textlib[] = "���� ���� ��ŭ ��ɥ ���� ʹ�� ��ŭ ��Թ ���� �ں� ���� ���� ���� ���� �ѹ� ʧ�� ���� ���� ���� ";
char text[100];

//�ַ���С
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
	//���ݻ�ͼ���趨��ɫ	COLORREF clr=GetPixel(hdc,x,y);	
	//���ݻ�õ���ɫ��������ɫ��������ɫ����	
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
		_T("����"));	 getnextchar();	 //  // ʹ��˫���������Ļˢ��ʱ��˸	
	CDC dc;	 dc.Attach(hdc);      CDC dcMem;// �ڴ�dc   
	CBitmap bmpMem; // λͼ	
	dcMem.CreateCompatibleDC(NULL);// ��������dc  
	bmpMem.CreateCompatibleBitmap(&dc, rect.right - rect.left + textw, rect.bottom - rect.top + texth);
	//�������ͻ������Сһ����(��)λͼ    
	// ��λͼѡ���豸�����Ļ�����  
	CBitmap *pOld = dcMem.SelectObject(&bmpMem);
	//����һ�»�������	
	//������ɫ	
	dcMem.SetTextColor(RGB(r, g, b));	//����ɫ͸��	
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SelectObject(font);	 //�Ȱѱ�����������
	dcMem.BitBlt(0, 0, rect.right - rect.left + textw, rect.bottom - rect.top + texth, &dc, 0, 0, SRCCOPY);
	//��ͼ	
	dcMem.TextOutW(x, y, text);
	//dcMem.TextOutW(x, y, text, sizeof(text));
	// ���ڴ濽�����豸dc    
	dc.BitBlt(0, 0, rect.right - rect.left + textw, rect.bottom - rect.top + texth, &dcMem, 0, 0, SRCCOPY);
	dc.SelectObject(pOld);
	// �ͷ���Դ   
	bmpMem.DeleteObject();
	dcMem.DeleteDC();
	ReleaseDC(NULL, hdc);
}

void  draw()
{
	// �ȴ�������HDC�������
	HDC hdc = NULL, mdc = NULL;
	// ����λͼ����
	HBITMAP hBitmap;
	// ��ȡһ���ɹ���ͼ��DC���������ֱ������������
	hdc = GetWindowDC(GetDesktopWindow());//��ȡ�豸�������
	mdc = CreateCompatibleDC(hdc);//����һ����g_hdc���ݵ��ڴ�DC 
	//����һ���ܴ��ڼ��ݵĿ�λͼ����
	//hBitmap = CreateCompatibleBitmap(hdc, 800, 600);
	// ������ɫ5���ؿ�ȵ����ۻ��ʣ�������봴����������Ļ��������MSDN
	HPEN hpen = CreatePen(PS_DASH, 5, RGB(0, 255, 0));
	// ��hpen1��hbrush1��Ȼ����(40,100)��Ҳ��һ�����Σ������кβ��
	SelectObject(mdc, hpen);
	Rectangle(mdc, 0, 0, 300, 400);
	BitBlt(hdc, 0, 0, 300, 400, mdc, 0, 0, SRCCOPY);
	// �ָ�ԭ���Ļ��ʺͻ�ˢ
	DeleteObject(hpen);
	DeleteObject(hdc);

	//SelectObject(mdc, hBitmap);//��λͼ����g_mdc�� 
	//electObject(bdc, bitmap);//bitmap����λͼ����ָ��Ҫ���Ƶ�ͼƬ.����g_bdc��.
	//Bitble(g_mdc, 0, 0, WIN_WIDTH, WIN_HIGHT, g_bdc, 0, 0, SRCCOPY);//��g_bdc�ŵ�g_mdc�� 
	//Bitble(g_hdc, 0, 0, WIN_WIDTH, WIN_HIGHT, g_mdc, 0, 0, SRCCOPY);//���g_mdc����g_hdc�У������Ϳ��Խ�ͼƬ��ʾ�ڴ�����  
	//DeleteDC();
}

int main()
{
		int seed; 	
		int randomx;	
		int randomy;	
		srand(unsigned(time(0)));
		//�Լ���ctrl+c�˳�
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

