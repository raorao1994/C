// 05结构体.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include "iostream"

using namespace std;

struct MyStruct
{
	char name[20];
	int age;
};


void printBook(struct MyStruct book);

int main()
{
	MyStruct me;
	strcpy(me.name, "jack");
	me.age = 12;

	cout << me.name << endl;
	printBook(me);
	system("pause");
    return 0;
}

void printBook( MyStruct book)
{
	cout << book.name << endl;
}
