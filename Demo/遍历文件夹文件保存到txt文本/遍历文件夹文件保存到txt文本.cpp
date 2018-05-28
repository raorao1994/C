// 遍历文件夹文件保存到txt文本.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "io.h"

using namespace std;

string path = "F:/opencv练级分类/neg";

int main()
{
	//创建文件
	fstream file;
	file.open(path+"/data.txt",ios::out);
	//遍历文件
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;//io.h
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是文件
			if (!(fileinfo.attrib&_A_SUBDIR))
			{
				string imgPath = p.assign(path).append("\\").append(fileinfo.name);
				cout << "路径：" << imgPath.c_str() << endl;
				//写入文本
				//file << fileinfo.name << " 1 0 0 40 40" << endl;
				file <<"neg/"<< fileinfo.name << endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);

		//文件关闭
		file.close();
	}
	system("pause");
    return 0;
}

