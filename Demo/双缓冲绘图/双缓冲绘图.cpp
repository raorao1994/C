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
	// �ȴ�������HDC�������
	HDC hdc=NULL, mdc = NULL;
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
	while (true)
	{
		draw();
		Sleep(10);
	}
	system("prase");
}

