// 04PerceptualHashAlgorithm.cpp : �������̨Ӧ�ó������ڵ㡣
//��֪��ϣ�㷨
//http://www.dewen.net.cn/q/757
//https://zm8.sm-tc.cn/?src=l4uLj8XQ0IiIiNGMl56NmpWM0ZyQktCckJuajNCcj4%2FQx8%2FOzQ%3D%3D&uid=91e12bcf7b8b965866e6bd2a9bd4bca7&hid=98ccbda5975cd189db0993e05e25eff4&pos=4&cid=9&time=1526948519149&from=click&restype=1&pagetype=0000004000000402&bu=web&query=%E5%9B%BE%E7%89%87%E5%AF%B9%E6%AF%94%E7%AE%97%E6%B3%95&mode=&v=1&province=%E5%8C%97%E4%BA%AC%E5%B8%82&city=%E5%8C%97%E4%BA%AC%E5%B8%82&uc_param_str=dnntnwvepffrgibijbprsvdsdichei

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int CalcImagePerceptualHashKey(InputArray input)
{
	Mat _input = input.getMat();
	Mat pTheImage88=Mat::zeros(Size(8, 8), _input.channels());
	Mat pGrayscaleImage = Mat::zeros(Size(8, 8), 1);
	//��ԭͼ�����8*8��ͼƬ
	resize(_input, pTheImage88, Size(8, 8));
	//cvtColor(pTheImage8x8, pGrayscaleImage);
	cvtColor(pTheImage88, pGrayscaleImage, COLOR_RGB2GRAY);
	pTheImage88.release();

	//����ƽ��ֵ
	float ElementMean = 0;
	for (size_t y = 0; y < 8; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			unsigned char& elemet = *(unsigned char*)pGrayscaleImage.at<unsigned char>(x, y);
			ElementMean += elemet;
		}
	}
	ElementMean= ElementMean / 64;
	//�õ�hashֵ
	int64 HashKey = 0;

	for (size_t y = 0; y < 8; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			unsigned char& elemet = *(unsigned char*)pGrayscaleImage.at<unsigned char>(x, y);
			if (elemet > ElementMean)
			{
				//������һλ
				HashKey <<= 1; 
			}
			else 
			{
				//������һλ
				HashKey <<= 1;
				//���һλ����Ϊ1
				HashKey |= 1;//�൱��HashKey =HashKey | 1
			}
		}
	}
	return HashKey;
}

int main()
{
	int a = 11;
	int b = 11;
	a >>= 1;
	b=b >> 1;
	cout << a << endl;
	cout << b << endl;
	system("pause");
    return 0;
}

