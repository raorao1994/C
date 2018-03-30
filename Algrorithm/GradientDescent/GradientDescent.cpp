// GradientDescent.cpp : 定义控制台应用程序的入口点。
//梯度下降
//沿梯度下降的方向求解极小值（也可以沿梯度上升方向求解极大值）,
//算法迭代的终止条件是梯度向量的幅值接近0即可，可以设置个非常小的常数阈值。
#include "stdafx.h"
#include<iostream>  
#include<cmath>  
#include<ctime> 
using namespace std;
//函数
double f(double x)
{
	return x*x - 2 * x + 1;
}
//求导数
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

