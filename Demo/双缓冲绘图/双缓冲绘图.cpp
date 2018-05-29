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
	HDC pDC= GetWindowDC(hwdn);
	//���ȶ���һ����ʾ�豸����
	HDC MemDC;
	//����һ��λͼ����
	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	HBITMAP MemBitmap,oldBitmap;
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

int main()
{
	init()
	//�Լ���ctrl+c�˳�
	while (true) {
		draw1();
		Sleep(100);
	}
	return 0;
}

