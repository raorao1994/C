// 01��������.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <string>
#include <limits>
#include <iostream>

using namespace std;
enum color {red,green,blue}c;

int main()
{
	//typedef �����������൱�ڸ����������
	typedef int myint;
	myint i = 0;
	c = blue;
	cout << c << endl;
	//cout��iostreamͷ�ļ���
	cout << "----------sizeof-----------" << endl;
	cout << "int	" << sizeof(int) <<"	���ֵ"<< (numeric_limits<int>::max) () << "	��Сֵ" << (numeric_limits<int>::min) () << endl;
	cout << "long	" << sizeof(long) << "	���ֵ" << (numeric_limits<long>::max) () << "	��Сֵ" << (numeric_limits<long>::min) () << endl;
	cout << "double	" << sizeof(double) << "	���ֵ" << (numeric_limits<double>::max) () << "	��Сֵ" << (numeric_limits<double>::min) () << endl;
	system("pause");
    return 0;
}

