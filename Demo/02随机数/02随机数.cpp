// 02�����.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

string RandStr(int length);

int main()
{
	int i, j;
	//��������
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < 10; i++)
	{
		j = rand();
		cout << "��������:" << j << endl;
	}
	string str=RandStr(20);
	cout << "��������:" << str.c_str() << endl;
	system("pause");
    return 0;
}
//���ɹ̶���������ַ�
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


