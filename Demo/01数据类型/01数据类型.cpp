// 01数据类型.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <string>
#include <limits>
#include <iostream>

using namespace std;
enum color {red,green,blue}c;

int main()
{
	//typedef 类型声明，相当于给类型起别名
	typedef int myint;
	myint i = 0;
	c = blue;
	cout << c << endl;
	//cout在iostream头文件中
	cout << "----------sizeof-----------" << endl;
	cout << "int	" << sizeof(int) <<"	最大值"<< (numeric_limits<int>::max) () << "	最小值" << (numeric_limits<int>::min) () << endl;
	cout << "long	" << sizeof(long) << "	最大值" << (numeric_limits<long>::max) () << "	最小值" << (numeric_limits<long>::min) () << endl;
	cout << "double	" << sizeof(double) << "	最大值" << (numeric_limits<double>::max) () << "	最小值" << (numeric_limits<double>::min) () << endl;
	system("pause");
    return 0;
}

