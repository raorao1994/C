// 03�ַ�������.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	string str1 = "abcdefg";
	string str2 = "cde";
	
	char s1[11] = "hello";
	char s2[11] = "ll";
	char s3[11] = "1321323";
	//copy s1 to s3
	strcpy(s3,s1);
	cout << "strcpy=" << s3 << endl;
	//connect s1 and s2
	strcat(s1, s2);
	cout << "strcat=" << s1 << endl;
	//calculate s1 length
	int len=strlen(s1);
	cout << "strlen=" << len << endl;
	//judge s1 ang s2 the same like (erro)
	//Determine whether 1 and 2 are the same
	//��� s1 �� s2 ����ͬ�ģ��򷵻� 0��
	//��� s1<s2 �򷵻�ֵС�� 0����� s1>s2 �򷵻�ֵ���� 0��
	bool islike =strcmp(s1, s2);
	cout << "strcmp=" << islike << endl;
	//return the char index in the s1 
	//char index = strstr(s1, "h");
	//����һ��ָ�룬ָ���ַ��� s1 ���ַ� ch �ĵ�һ�γ��ֵ�λ�á�
	
	char * index=strchr(s1,'a');
	//strstr(s1, s2);
	//����һ��ָ�룬ָ���ַ��� s1 ���ַ��� s2 �ĵ�һ�γ��ֵ�λ�á�
	index = strstr(s1, s2);

	system("pause");
    return 0;
}

