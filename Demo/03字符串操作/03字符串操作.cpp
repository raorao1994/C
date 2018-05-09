// 03字符串操作.cpp : 定义控制台应用程序的入口点。
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
	//如果 s1 和 s2 是相同的，则返回 0；
	//如果 s1<s2 则返回值小于 0；如果 s1>s2 则返回值大于 0。
	bool islike =strcmp(s1, s2);
	cout << "strcmp=" << islike << endl;
	//return the char index in the s1 
	//char index = strstr(s1, "h");
	//返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置。
	
	char * index=strchr(s1,'a');
	//strstr(s1, s2);
	//返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置。
	index = strstr(s1, s2);

	system("pause");
    return 0;
}

