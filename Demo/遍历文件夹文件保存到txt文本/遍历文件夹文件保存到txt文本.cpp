// �����ļ����ļ����浽txt�ı�.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "io.h"

using namespace std;

string path = "F:/opencv��������/neg";

int main()
{
	//�����ļ�
	fstream file;
	file.open(path+"/data.txt",ios::out);
	//�����ļ�
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;//io.h
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//������ļ�
			if (!(fileinfo.attrib&_A_SUBDIR))
			{
				string imgPath = p.assign(path).append("\\").append(fileinfo.name);
				cout << "·����" << imgPath.c_str() << endl;
				//д���ı�
				//file << fileinfo.name << " 1 0 0 40 40" << endl;
				file <<"neg/"<< fileinfo.name << endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);

		//�ļ��ر�
		file.close();
	}
	system("pause");
    return 0;
}

