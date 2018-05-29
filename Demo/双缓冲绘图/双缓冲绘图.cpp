// ˫�����ͼ.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>
#include<windows.h>
#include <io.h>
#include <map>
#include <fstream>
#include <atlimage.h>
using namespace std;

//����
HWND hwnd = NULL;
HDC m_hDC;
HBITMAP m_hBmpOld;
LONG height, width;

void init()
{
	hwnd = GetDesktopWindow();
	HDC hDC = ::GetDC(hwnd);  // �õ���ĻDC  
	m_hDC = CreateCompatibleDC(hDC);
	width = ::GetDeviceCaps(hDC, HORZRES);// ��  
	height = ::GetDeviceCaps(hDC, VERTRES);// ��   
	::ReleaseDC(HWND(NULL), hDC);// �ͷ�DC
	//����һ������Ļ�豸��������ݵ� λͼ
	HBITMAP hbmp = CreateCompatibleBitmap(m_hDC, width, height);
	//����λͼѡ���ڴ��豸��������
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

//����
void  draw()
{
	// ��ȡһ���ɹ���ͼ��DC���������ֱ������������
	HDC hdc = GetWindowDC(GetDesktopWindow());

	// ������ɫ1���ؿ�ȵ�ʵ�߻���
	HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	// ������ɫ5���ؿ�ȵ����ۻ��ʣ�������봴����������Ļ��������MSDN
	HPEN hpen2 = CreatePen(PS_DASH, 5, RGB(0, 255, 0));
	// ����һ��ʵ����ɫ��ˢ
	HBRUSH hbrush1 = CreateSolidBrush(RGB(0, 0, 255));
	// ����һ��͸���Ļ�ˢ��������봴����������Ļ�ˢ�����MSDN
	HBRUSH hbrush2 = (HBRUSH)GetStockObject(NULL_BRUSH);

	// ��hpen1��hbrush1ѡ��HDC��������HDCԭ���Ļ��ʺͻ�ˢ
	HPEN hpen_old = (HPEN)SelectObject(hdc, hpen1);
	HBRUSH hbrush_old = (HBRUSH)SelectObject(hdc, hbrush1);

	// ��(40,30)����һ����200���أ���50���صľ���
	Rectangle(hdc, 40, 30, 40 + 200, 30 + 50);

	// ��hpen1��hbrush1��Ȼ����(40,100)��Ҳ��һ�����Σ������кβ��
	SelectObject(hdc, hpen2);
	SelectObject(hdc, hbrush2);
	Rectangle(hdc, 40, 100, 40 + 200, 100 + 50);

	// ������Բ����
	Ellipse(hdc, 40, 200, 40 + 200, 200 + 50);

	// ����(0,600)��(800,0)��ֱ�߿���
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 800, 0);

	// ��(700,500)�������Ƶ㣬���������ֻ��һ���ش�С����ϸϸ�Ŀ������ҵ�
	SetPixel(hdc, 700, 500, RGB(255, 255, 0));
	//���֣�
	//��������������XY���꣬���֣����ֿ��
	TextOutA(hdc, 700, 500, "������", 6);
	// �ָ�ԭ���Ļ��ʺͻ�ˢ
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
	//���ȶ���һ����ʾ�豸����
	HDC MemDC;
	//����һ��λͼ����
	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	HBITMAP MemBitmap, oldBitmap;
	//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
	MemDC = CreateCompatibleDC(NULL);
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С��Ҳ�����Լ�����
	MemBitmap = CreateCompatibleBitmap(pDC, 500, 500);
	//��λͼѡ�뵽�ڴ���ʾ�豸�С�
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	oldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);
	//SelectObject(MemDC, oldBitmap);
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ������//��Ҳ�������Լ�Ӧ���õ���ɫ��
	// ������ɫ1���ؿ�ȵ�ʵ�߻���
	HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hpen_old = (HPEN)SelectObject(pDC, hpen1);
	//FillRect(MemDC, rt, RGB(255, 255, 255));
	TextOutA(MemDC, 200, 300, "������", 6);
	Rectangle(MemDC, 40, 30, 40 + 200, 30 + 50);
	//����Ļ�豸�����������ڴ��豸��������
	BitBlt(MemDC, 0, 0, 500, 500, pDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, oldBitmap);

	DeleteObject(MemBitmap);
	DeleteObject(MemDC);
}

//��ͼ3
BOOL SaveBitmapToFile(HBITMAP   hBitmap, string szfilename)
{
	HDC hScrDC;
	HDC     hDC;
	//��ǰ�ֱ�����ÿ������ռ�ֽ���            
	int     iBits;
	//λͼ��ÿ������ռ�ֽ���            
	WORD     wBitCount;
	//�����ɫ���С��     λͼ�������ֽڴ�С     ��λͼ�ļ���С     ��     д���ļ��ֽ���                
	DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	//λͼ���Խṹ                
	BITMAP     Bitmap;
	//λͼ�ļ�ͷ�ṹ            
	BITMAPFILEHEADER     bmfHdr;
	//λͼ��Ϣͷ�ṹ                
	BITMAPINFOHEADER     bi;
	//ָ��λͼ��Ϣͷ�ṹ                    
	LPBITMAPINFOHEADER     lpbi;
	//�����ļ��������ڴ�������ɫ����                
	HANDLE     fh, hDib, hPal, hOldPal = NULL;

	//����λͼ�ļ�ÿ��������ռ�ֽ���                
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

	//Ϊλͼ���ݷ����ڴ�                
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	//     �����ɫ��                    
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//     ��ȡ�õ�ɫ�����µ�����ֵ                
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);

	//�ָ���ɫ��                    
	if (hOldPal)
	{
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	//����λͼ�ļ�                    
	/*fh = CreateFile("123", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);*/

	//if (fh == INVALID_HANDLE_VALUE)         return     FALSE;

	//     ����λͼ�ļ�ͷ                
	bmfHdr.bfType = 0x4D42;     //     "BM"                
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	//     д��λͼ�ļ�ͷ                
	//WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	//     д��λͼ�ļ���������                
	//WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//���                    
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	//CloseHandle(fh);

	return     TRUE;

}

int main()
{
	init(); UpdateLayeredContent();
	//�Լ���ctrl+c�˳�
	while (true)
	{
		//UpdateLayeredContent();
		//draw1();
		Sleep(100);
	}
	return 0;
}

