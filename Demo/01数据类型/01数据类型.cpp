// 01数据类型.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <string>
#include <limits>
#include <iostream>

using namespace std;
enum color {red,green,blue}c;

void func(char c[100])
{
	cout<<sizeof(c)<<endl;//8
}

struct  ST_ABC
{
	int a;
	char b;
	double c;
};

class A {
public:
	void modify(int n) {
		cout << n << endl;
	}
	void modify1(int n) const {
		cout << n << endl;
	}
};

void test(void)
{
	char *str = (char*)malloc(100);
	printf(str);//
	strcpy(str, "hellow");
	printf(str);//hellow
	free(str);
	printf(str);//
	if (str != NULL) {
		strcpy(str, "world");
		printf(str);//world
	}
}

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
	cout << "char	" << sizeof(char) << "	最大值" << (numeric_limits<char>::max) () << "	最小值" << (numeric_limits<char>::min) () << endl;
	cout << "double	" << sizeof(double) << "	最大值" << (numeric_limits<double>::max) () << "	最小值" << (numeric_limits<double>::min) () << endl;
	


	cout << "----------sizeof-----------" << endl;
	float x = 0.0f;
	if (x >= 0.0F)
	{

	}
	
	char c[100];
	func(c);

	char str[] = "hello";
	char *p = str;
	int n = 10;
	void *pp = malloc(100);
	cout<<"str[]=" << sizeof(str) << endl;//6 末尾有/0
	cout << "*p =" << sizeof(p) << endl;//8
	cout << "n" << sizeof(n) << endl;//4
	cout << "*pp =" << sizeof(pp) << endl;//8
	cout << "ST_ABC =" << sizeof(ST_ABC) << endl;//16


	cout << "----------sizeof-----------" << endl;
	double val = 10.47831;
	cout << val<<endl;
	printf("%.2f", val);


	A a;
	a.modify(3);
	a.modify1(4);
	cout << "----------test-----------" << endl;
	test();
	
	system("pause");
    return 0;
}

