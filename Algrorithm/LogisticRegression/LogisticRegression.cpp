// LogisticRegression.cpp : �������̨Ӧ�ó������ڵ㡣
//�߼��ع�
//�߼��ع�(Logistic Regression, LR)��ʵ���������Իع�Ļ����ϣ�
//������һ���߼��������߼��ع�����������ģ�͵ģ�
//��Ϊ�߼��ع�ľ��߽߱磨decision boundary�������Եġ�
//��ֻ���������������ӳ���м�����һ��sigmoid������
//���Ȱ�������ͣ�Ȼ��ʹ�÷����Եĺ���������ֵӳ�䵽0��1֮�䡣
/*
�߼��ع������Իع�Ĳ��
1�����Իع�Ҫ�����������̬�ֲ����߼��ع�Ա����ֲ�û��Ҫ��
2�����Իع�Ҫ�����������������ֵ���������߼��ع�Ҫ��������Ƿ����ͱ�����
3�����Իع�Ҫ���Ա���������������Թ�ϵ�����߼��ع鲻Ҫ���Ա���������������Թ�ϵ
4���߼��ع��Ƿ��������ȡĳ��ֵ�ĸ������Ա����Ĺ�ϵ�������Իع���ֱ�ӷ�����������Ա����Ĺ�ϵ
��֮, �߼��ع������Իع�ʵ�����кܶ���֮ͬ��������������������ǵ��������ͬ��
�����Ļ�������࣬������Ϊ��ˣ������ֻع���Թ���ͬһ�����壬
����������ģ�ͣ�generalized linear model����
��һ�����е�ģ����ʽ�����϶���࣬��ͬ�ľ����������ͬ��
����������ģ����Ƕ������Իع飬����Ƕ���ֲ��������߼��ع顣
�߼��ع������������Ƕ�����ģ�Ҳ�����Ƕ����ģ����Ƕ�����ĸ�Ϊ���ã�
Ҳ�������׽��͡�����ʵ������Ϊ���õľ��Ƕ�������߼��ع顣

�ġ��ܽ�
����ģ��ʹ�ü򵥵Ĺ�ʽͨ��һ�����ݵ������ҡ�������ϡ��ߡ�
ͨ������֪�ı������̣�������������ҪԤ��ı�����
Ϊ�����Ԥ����������������֪�ı����õ��𰸡�
���Իع���߼��ع鶼������ͬ��ȱ�㡣
���߶����С�����ϣ�overfit���������ƣ�
����ζ��ģ��̫��Ӧ�����ݶ��������ƹ㵽��ǰδ֪�����ݵ�������
��ˣ�������ģ�;�����Ҫ���й淶��
����ζ��������һ���ĳͷ���penalty���Է�ֹ����ϡ�
���о�����Ϊ����̫���ˣ�������������Ԥ������ӵ���Ϊ��
*/
#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>  //�ļ����⺯��

using namespace std;

class Sample
{
public:
	Sample(double x, double y,int lable)
	{
		Sample::x = x;
		Sample::y = y;
		Sample::lable = lable;
	}
	double x;
	double y;
	int lable;
};

//Sigmoid����
double sigmoid(double x)
{
	return 1.0 / (1 + exp(-x));
}
//�Ľ�������ݶ���������ÿ�ε��������ѡ������������Ȩ�أ�
//����������������ӣ�Ȩ�ر仯ԽС��
//Sample pl[]������iterations����������alpha������
/*
iterations ��������
alpha �ݶ�ϵ��
*/
double *stocGradAscent(vector<Sample> pl,int  iterations,double alpha)
{
	//��ȡ���鳤��
	int count = pl.size();
	//����Ȩֵ,��ʼ��Ϊ1
	double weights[2]{1,1};
	//����
	for (size_t i = 0; i < iterations; i++)
	{
		//��ʼ��������
		for (size_t index = 0; index < count; index++)
		{
			//������Ȩֵ��������
			double _s = pl[index].x*weights[0] + pl[index].y*weights[1];
			//sigmoid����
			_s = sigmoid(_s);
			//�����
			double deviation =pl[index].lable - _s;
			//���ݾ�������ʡ�����Ȩֵ
			weights[0] = weights[0] + alpha*pl[index].x*deviation;
			weights[1] = weights[1] + alpha*pl[index].y*deviation;
		}
	}
	return weights;
}

vector<Sample> GetData(string path)
{
	int v, w, weight;
	vector<Sample> data;
	ifstream infile;   //������
	infile.open(path, ios::in);
	if (!infile.is_open())
		cout << "���ļ�ʧ��" << endl;
	char line[100] = {0};
	while (infile.getline(line,sizeof(line)))            // ��δ���ļ�����һֱѭ��
	{
		//Sample p(x, y, lable);
		//data.push_back(p);
	}
	infile.close();   //�ر��ļ�
	infile.close();   //�ر��ļ�
	return data;
}

int main()
{
	double x = 0.0;
	double y = sigmoid(x);
	//��������
	//vector<Sample> data = GetData("LogisticRegression.txt");
	vector<Sample> data;
	data.push_back(Sample(-0.017612, 14.053064, 0));
	data.push_back(Sample(-1.395634, 4.662541, 1));
	data.push_back(Sample(-0.752157, 6.538620, 0));
	data.push_back(Sample(-1.322371, 7.152853, 0));
	data.push_back(Sample(0.423363, 11.054677, 0));
	data.push_back(Sample(0.406704, 7.067335, 1));
	data.push_back(Sample(0.667394, 12.741452, 0));
	double *weights;
	weights = stocGradAscent(data,20,0.001);
	cout << weights[0] <<":"<< weights[1] << endl;
	system("pause");
    return 0;
}

