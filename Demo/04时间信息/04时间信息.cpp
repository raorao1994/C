// 04时间信息.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include "iostream"
#include "ctime"

using namespace std;

int main()
{
	//基于当前系统的当前时间
	time_t now = time(0);
	//把now转换为字符串形式
	char* dt = ctime(&now);
	cout << "本地时间：" << dt << endl;

	tm *ltm = localtime(&now);
	// 输出 tm 结构的各个组成部分
	cout << "年: " << 1900 + ltm->tm_year << endl;
	cout << "月: " << 1 + ltm->tm_mon << endl;
	cout << "日: " << ltm->tm_mday << endl;
	cout << "时间: " << ltm->tm_hour << ":";
	cout << ltm->tm_min << ":";
	cout << ltm->tm_sec << endl;

	system("pause");
    return 0;
}

