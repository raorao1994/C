// 02随机数.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

string RandStr(int length);

int main()
{
	int i, j;
	//设置种子
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < 10; i++)
	{
		j = rand();
		cout << "输出随机数:" << j << endl;
	}
	string str=RandStr(20);
	cout << "输出随机数:" << str.c_str() << endl;
	system("pause");
    return 0;
}
//生成固定长度随机字符
string RandStr(int length)
{
	srand((unsigned)time(NULL));
	char* szStr = new char[length + 1];
	szStr[length] = '\0';
	char chars[]= "0123456789qwertyuioplkjghfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
	for (size_t i = 0; i < length; i++)
	{
		int j = rand()%58;
		szStr[i] = chars[j];
	}
	string str(szStr);
	delete[] szStr;
	return str;
}


