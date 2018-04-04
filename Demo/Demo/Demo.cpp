// Demo.cpp : �������̨Ӧ�ó������ڵ㡣
//���������ͼ��
#include "stdafx.h"
#include <iostream>
#include<windows.h>
#include <io.h>
#include <map>
#include <fstream>
#include <atlimage.h>
using namespace std;

//wstringת����string
string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen <= 0) return std::string("");

	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;

	std::string strTemp(pszDst);
	delete[] pszDst;

	return strTemp;
}
//stringת����  wstring
wstring s2ws(string s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r.c_str();
}
//stringת����  LPCWSTR
LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	wstring wstrResult(wcstring);
	//free(wcstring);
	return wstrResult.c_str();
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
}

int main()
{
	while (true)
	{
		draw();
		Sleep(100);
	}
	system("prase");
}

