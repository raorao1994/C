// LogisticRegression.cpp : 定义控制台应用程序的入口点。
//逻辑回归
//逻辑回归(Logistic Regression, LR)其实就是在线性回归的基础上，
//套用了一个逻辑函数。逻辑回归是属于线性模型的，
//因为逻辑回归的决策边界（decision boundary）是线性的。
//它只是在特征到结果的映射中加入了一个sigmoid函数。
//即先把特征求和，然后使用非线性的函数将连续值映射到0与1之间。
/*
逻辑回归与线性回归的差别：
1）线性回归要求变量服从正态分布，逻辑回归对变量分布没有要求。
2）线性回归要求因变量是连续性数值变量，而逻辑回归要求因变量是分类型变量。
3）线性回归要求自变量和因变量呈线性关系，而逻辑回归不要求自变量和因变量呈线性关系
4）逻辑回归是分析因变量取某个值的概率与自变量的关系，而线性回归是直接分析因变量与自变量的关系
总之, 逻辑回归与线性回归实际上有很多相同之处，最大的区别就在于他们的因变量不同，
其他的基本都差不多，正是因为如此，这两种回归可以归于同一个家族，
即广义线性模型（generalized linear model）。
这一家族中的模型形式基本上都差不多，不同的就是因变量不同，
如果是连续的，就是多重线性回归，如果是二项分布，就是逻辑回归。
逻辑回归的因变量可以是二分类的，也可以是多分类的，但是二分类的更为常用，
也更加容易解释。所以实际中最为常用的就是二分类的逻辑回归。

四、总结
线性模型使用简单的公式通过一组数据点来查找「最优拟合」线。
通过你已知的变量方程，你可以求出你想要预测的变量。
为了求出预测量，我们输入已知的变量得到答案。
线性回归和逻辑回归都有着相同的缺点。
两者都具有「过拟合（overfit）」的趋势，
这意味着模型太适应于数据而牺牲了推广到先前未知的数据的能力。
因此，这两个模型经常需要进行规范，
这意味着它们有一定的惩罚（penalty）以防止过拟合。
还有就是因为它们太简单了，所以往往不能预测更复杂的行为。
*/
#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>  //文件流库函数

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

//Sigmoid函数
double sigmoid(double x)
{
	return 1.0 / (1 + exp(-x));
}
//改进版随机梯度上升，在每次迭代中随机选择样本来更新权重，
//并且随迭代次数增加，权重变化越小。
//Sample pl[]样本，iterations迭代次数，alpha更新率
/*
iterations 迭代次数
alpha 梯度系数
*/
double *stocGradAscent(vector<Sample> pl,int  iterations,double alpha)
{
	//获取数组长度
	int count = pl.size();
	//创建权值,初始化为1
	double weights[2]{1,1};
	//遍历
	for (size_t i = 0; i < iterations; i++)
	{
		//开始矩阵运算
		for (size_t index = 0; index < count; index++)
		{
			//样本、权值矩阵运算
			double _s = pl[index].x*weights[0] + pl[index].y*weights[1];
			//sigmoid运算
			_s = sigmoid(_s);
			//求均差
			double deviation =pl[index].lable - _s;
			//根据均差、更新率、更新权值
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
	ifstream infile;   //输入流
	infile.open(path, ios::in);
	if (!infile.is_open())
		cout << "打开文件失败" << endl;
	char line[100] = {0};
	while (infile.getline(line,sizeof(line)))            // 若未到文件结束一直循环
	{
		//Sample p(x, y, lable);
		//data.push_back(p);
	}
	infile.close();   //关闭文件
	infile.close();   //关闭文件
	return data;
}

int main()
{
	double x = 0.0;
	double y = sigmoid(x);
	//定义数据
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

