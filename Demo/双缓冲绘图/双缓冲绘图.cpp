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
	HWND hwnd=NULL;
	RECT rc;
	HDC hdc = GetWindowDC(GetDesktopWindow());
	GetClientRect(hwnd, &rc);
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDc, hBmp);
	//�ڴ�ʹ��hMemDc���� GDI ����  
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, hMemDc, 0, 0, SRCCOPY);
	SelectObject(hMemDc, hOldBmp);
	DeleteObject(hBmp);
	DeleteObject(hMemDc);
}

int main()
{
	//�Լ���ctrl+c�˳�
	while (true) {
		draw1();
	}
	return 0;
}

