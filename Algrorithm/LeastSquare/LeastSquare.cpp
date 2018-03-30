// LeastSquare.cpp : 定义控制台应用程序的入口点。
//最小二乘法
//通过最小化误差的平方和寻找数据的最佳函数匹配。
//利用最小二乘法可以简便地求得未知的数据，
//并使得这些求得的数据与实际数据之间误差的平方和为最小。
#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

//定义point类
class Point
{
private:
	float x, y;
public:
	Point(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float GetX() { return x; }
	float GetY() { return y; }
	//friend 友元采用类的机制后实现了数据的隐藏与封装，
	//类的数据成员一般定义为私有成员，成员函数一般定义为公有的，
	//依此提供类与外界间的通信接口。但是，有时需要定义一些函数，
	//这些函数不是类的一部分（注意友元函数不是类的一部分），
	//但又需要频繁地访问类的数据成员，
	//这时可以将这些函数定义为该函数的友元函数。
	//除了友元函数外，还有友元类，两者统称为友元。
	//友元的作用是提高了程序的运行效率
	//（即减少了类型检查和安全性检查等都需要时间开销），
	//但它破坏了类的封装性和隐藏性，使得非成员函数可以访问类的私有成员。
	friend float linefit(Point p1[],int n_point);
};
float linefit(Point ps[], int n_point)
{
	float av_x, av_y; //声明变量  
	float L_xx, L_yy, L_xy;
	//变量初始化  
	av_x = 0; //X的平均值  
	av_y = 0; //Y的平均值  
	L_xx = 0; //Lxx  
	L_yy = 0; //Lyy  
	L_xy = 0; //Lxy  
	for (int i = 0; i<n_point; i++) //计算X、Y的平均值  
	{
		av_x += ps[i].x / n_point;
		av_y += ps[i].y / n_point;
	}
	//计算残差平方和Lxx、Lyy和Lxy
	//（在统计学中，残差平方和函数可以看成n倍的均方误差MSE）
	for (int i = 0; i<n_point; i++)   
	{
		L_xx += (ps[i].x - av_x)*(ps[i].x - av_x);
		L_yy += (ps[i].y - av_y)*(ps[i].y - av_y);
		L_xy += (ps[i].x - av_x)*(ps[i].y - av_y);
	}
	cout << "a=" << L_xy / L_xx << endl; //输出回归系数a  
	cout << "b=" << av_y - L_xy*av_x / L_xx << endl; //输出回归系数b  
	return float(L_xy / sqrt(L_xx*L_yy)); //返回相关系数r 
}

int main()
{

	Point l_p[10] = {
		Point(208,21.6),
		Point(152,15.5),
		Point(113,10.4),
		Point(227,31.0),
		Point(137,13.0),
		Point(238,32.4),
		Point(178,19.0),
		Point(104,10.4),
		Point(191,19.0),
		Point(130,11.8) };
	float r = linefit(l_p, 10); //进行线性回归计算  
	cout << "r=" << r << endl; //输出相关系数  
	system("pause");
}

