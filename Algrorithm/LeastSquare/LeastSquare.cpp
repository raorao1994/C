// LeastSquare.cpp : �������̨Ӧ�ó������ڵ㡣
//��С���˷�
//ͨ����С������ƽ����Ѱ�����ݵ���Ѻ���ƥ�䡣
//������С���˷����Լ������δ֪�����ݣ�
//��ʹ����Щ��õ�������ʵ������֮������ƽ����Ϊ��С��
#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

//����point��
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
	//friend ��Ԫ������Ļ��ƺ�ʵ�������ݵ��������װ��
	//������ݳ�Աһ�㶨��Ϊ˽�г�Ա����Ա����һ�㶨��Ϊ���еģ�
	//�����ṩ���������ͨ�Žӿڡ����ǣ���ʱ��Ҫ����һЩ������
	//��Щ�����������һ���֣�ע����Ԫ�����������һ���֣���
	//������ҪƵ���ط���������ݳ�Ա��
	//��ʱ���Խ���Щ��������Ϊ�ú�������Ԫ������
	//������Ԫ�����⣬������Ԫ�࣬����ͳ��Ϊ��Ԫ��
	//��Ԫ������������˳��������Ч��
	//�������������ͼ��Ͱ�ȫ�Լ��ȶ���Ҫʱ�俪������
	//�����ƻ�����ķ�װ�Ժ������ԣ�ʹ�÷ǳ�Ա�������Է������˽�г�Ա��
	friend float linefit(Point p1[],int n_point);
};
float linefit(Point ps[], int n_point)
{
	float av_x, av_y; //��������  
	float L_xx, L_yy, L_xy;
	//������ʼ��  
	av_x = 0; //X��ƽ��ֵ  
	av_y = 0; //Y��ƽ��ֵ  
	L_xx = 0; //Lxx  
	L_yy = 0; //Lyy  
	L_xy = 0; //Lxy  
	for (int i = 0; i<n_point; i++) //����X��Y��ƽ��ֵ  
	{
		av_x += ps[i].x / n_point;
		av_y += ps[i].y / n_point;
	}
	//����в�ƽ����Lxx��Lyy��Lxy
	//����ͳ��ѧ�У��в�ƽ���ͺ������Կ���n���ľ������MSE��
	for (int i = 0; i<n_point; i++)   
	{
		L_xx += (ps[i].x - av_x)*(ps[i].x - av_x);
		L_yy += (ps[i].y - av_y)*(ps[i].y - av_y);
		L_xy += (ps[i].x - av_x)*(ps[i].y - av_y);
	}
	cout << "a=" << L_xy / L_xx << endl; //����ع�ϵ��a  
	cout << "b=" << av_y - L_xy*av_x / L_xx << endl; //����ع�ϵ��b  
	return float(L_xy / sqrt(L_xx*L_yy)); //�������ϵ��r 
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
	float r = linefit(l_p, 10); //�������Իع����  
	cout << "r=" << r << endl; //������ϵ��  
	system("pause");
}

