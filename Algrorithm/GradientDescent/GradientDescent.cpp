// GradientDescent.cpp : �������̨Ӧ�ó������ڵ㡣
//�ݶ��½�
//���ݶ��½��ķ�����⼫Сֵ��Ҳ�������ݶ�����������⼫��ֵ��,
//�㷨��������ֹ�������ݶ������ķ�ֵ�ӽ�0���ɣ��������ø��ǳ�С�ĳ�����ֵ��
#include "stdafx.h"
#include<iostream>  
#include<cmath>  
#include<ctime> 
using namespace std;
//����
double f(double x)
{
	return x*x - 2 * x + 1;
}
//����
double g(double x)
{
	return  2 * x - 2;
}

double GradientDescent(double x, double rate)
{
	double _x = x;
	double y;
	int i = 0;
	while (++i)
	{
		double grad = -1 * g(_x);
		_x += grad*rate;
		y = f(_x);
		cout << "i=" << i << " grad=" << grad << " x=" << _x << " y=" << y << endl;
		if (abs(grad) < 1E-2)
		{
			break;
		}
	}
	return _x;
}

int main()
{
	double xk = -5, ak = 0.1;
	GradientDescent(xk, ak);
	system("pause");
    return 0;
}

