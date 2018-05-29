// 04PerceptualHashAlgorithm.cpp : 定义控制台应用程序的入口点。
//感知哈希算法
//http://www.dewen.net.cn/q/757
//https://zm8.sm-tc.cn/?src=l4uLj8XQ0IiIiNGMl56NmpWM0ZyQktCckJuajNCcj4%2FQx8%2FOzQ%3D%3D&uid=91e12bcf7b8b965866e6bd2a9bd4bca7&hid=98ccbda5975cd189db0993e05e25eff4&pos=4&cid=9&time=1526948519149&from=click&restype=1&pagetype=0000004000000402&bu=web&query=%E5%9B%BE%E7%89%87%E5%AF%B9%E6%AF%94%E7%AE%97%E6%B3%95&mode=&v=1&province=%E5%8C%97%E4%BA%AC%E5%B8%82&city=%E5%8C%97%E4%BA%AC%E5%B8%82&uc_param_str=dnntnwvepffrgibijbprsvdsdichei

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
//根据图片生成64位hash码
int CalcImagePerceptualHashKey(InputArray input)
{
	Mat _input = input.getMat();
	Mat pTheImage88=Mat::zeros(Size(8, 8), _input.channels());
	Mat pGrayscaleImage = Mat::zeros(Size(8, 8), 1);
	//将原图处理成8*8的图片
	resize(_input, pTheImage88, Size(8, 8));
	//cvtColor(pTheImage8x8, pGrayscaleImage);
	cvtColor(pTheImage88, pGrayscaleImage, COLOR_RGB2GRAY);
	pTheImage88.release();

	//计算平均值
	float ElementMean = 0;
	for (size_t y = 0; y < 8; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			unsigned char elemet = pGrayscaleImage.at<unsigned char>(x, y);
			ElementMean += elemet;
		}
	}
	ElementMean= ElementMean / 64;
	//得到hash值
	int64 HashKey = 0;

	for (size_t y = 0; y < 8; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			unsigned char elemet = pGrayscaleImage.at<unsigned char>(x, y);
			if (elemet > ElementMean)
			{
				//向左移一位
				HashKey <<= 1; 
			}
			else 
			{
				//向左移一位
				HashKey <<= 1;
				//最后一位复制为1
				HashKey |= 1;//相当于HashKey =HashKey | 1
			}
		}
	}
	return HashKey;
}
//指纹hash码比对
float CompareImageSimilarity(int64 key1, int64 key2)
{
	//两组hash码对比
	int64 result = key1^key2;
	int count = 0;
	int i = 64;
	while (i--)
	{
		//判断最后一位是否为1，即是否相同
		if ((result & 1) == 1)
			count++;
		//右移一位，进入下一位
		result >>= 1;
	}
	return count == 0 ? 1 : (64 - count) / (float)64;
}

int main()
{
	Mat img1 = imread("1.jpg");
	Mat img2 = imread("2.jpg");

	int64 key1 = CalcImagePerceptualHashKey(img1);
	int64 key2 = CalcImagePerceptualHashKey(img2);

	float lv = CompareImageSimilarity(key1, key2);

	cout << "匹配度：" << lv << endl;
	waitKey(2000);
	system("pause");
    return 0;
}

