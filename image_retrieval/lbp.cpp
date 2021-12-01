#pragma once
#include "init.h"
#include "lbp.h"
//const int revolve_map[] = { 0,1,3,5,7,9,11,13,15,17,19,21,23,24,27,29,31,37,39,43,45,47,51,53,55,59,61,63,85,87,91,95,111,119,127,255 };
//const int uniform_map[] = {0,1,2,3,4,6,7,8,12,14,15,16,24,28,30,31,32,48,56,60,62,63,64,96,112,120,124,126,127,128,129,131,135,143,159,191,192,193,195,199,207,223,224,225,227,231,239,240,241,243,247,248,249,251,252,253,254,255 };
void point_search(int i, int j, int t) {

}

void basic_lbp(Mat& I, vector<float>& data) {
    Mat II = I.clone();
    int sum[8];
    info d;
    vector<int> temp;
    for (int i = 1; i < I.rows - 1; ++i) {
        for (int j = 1; j < I.cols - 1; ++j) {
            int k = 0;
            uchar tmp = I.at<uchar>(i, j);
            sum[k++] = I.at<uchar>(i - 1, j - 1) > tmp ? 1 : 0;
            sum[k++] = I.at<uchar>(i - 1, j) > tmp > tmp ? 1 : 0;
            sum[k++] = I.at<uchar>(i - 1, j + 1) > tmp > tmp ? 1 : 0;
            sum[k++] = I.at<uchar>(i, j + 1) > tmp ? 1 : 0;
            sum[k++] = I.at<uchar>(i + 1, j + 1) > tmp > tmp ? 1 : 0; 
            sum[k++] = I.at<uchar>(i + 1, j) > tmp > tmp ? 1 :  0;
            sum[k++] = I.at<uchar>(i + 1, j - 1) > tmp ?  1 :  0;
            sum[k++] = I.at<uchar>(i, j - 1) > tmp > tmp ?  1 : 0;
            int result = 0;
            int bit_num = 0;
            for (auto it : sum) {
                result += it << bit_num;
                bit_num += 1;
            }
            II.at<uchar>(i, j) = result;
        }
    }

    MatND dstHist;
    int dims = 1;
    float hranges[] = { 0,255 };
    const float* ranges[] = { hranges };
    int size = 256;
    int channels = 0;

    calcHist(&II, 1, &channels, Mat(), dstHist, dims, &size, ranges);
    int scale = 1;

    Mat dstImage(size * scale, size, CV_8U, Scalar(0));

    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
    data = dstHist;
    /*
    int hpt = saturate_cast<int>(0.9 * size);
    for (int i = 0; i < 256; i++) {
        float binValue = dstHist.at<float>(i);
        int realValue = saturate_cast<int>(binValue * hpt / maxValue);
        rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
    }
    imshow("一维直方图", dstImage);
    */
}

//旋转不变圆形LBP特征计算
void getRotationInvariantLBPFeature(Mat &src, int radius, int neighbors)
{
	for (int k = 0; k < neighbors; k++)
	{
		//计算采样点对于中心点坐标的偏移量rx，ry
		float rx = static_cast<float>(radius * cos(2.0 * CV_PI * k / neighbors));
		float ry = -static_cast<float>(radius * sin(2.0 * CV_PI * k / neighbors));
		//为双线性插值做准备
		//对采样点偏移量分别进行上下取整
		int x1 = static_cast<int>(floor(rx));
		int x2 = static_cast<int>(ceil(rx));
		int y1 = static_cast<int>(floor(ry));
		int y2 = static_cast<int>(ceil(ry));
		//将坐标偏移量映射到0-1之间
		float tx = rx - x1;
		float ty = ry - y1;
		//根据0-1之间的x，y的权重计算公式计算权重，权重与坐标具体位置无关，与坐标间的差值有关
		float w1 = (1 - tx) * (1 - ty);
		float w2 = tx * (1 - ty);
		float w3 = (1 - tx) * ty;
		float w4 = tx * ty;
		//循环处理每个像素
		for (int i = radius; i < src.rows - radius; i++)
		{
			for (int j = radius; j < src.cols - radius; j++)
			{
				//获得中心像素点的灰度值
				uchar center = src.at<uchar>(i, j);
				//根据双线性插值公式计算第k个采样点的灰度值
				float neighbor = src.at<uchar>(i + x1, j + y1) * w1 + src.at<uchar>(i + x1, j + y2) * w2 \
					+ src.at<uchar>(i + x2, j + y1) * w3 + src.at<uchar>(i + x2, j + y2) * w4;
				//LBP特征图像的每个邻居的LBP值累加，累加通过与操作完成，对应的LBP值通过移位取得
				src.at<uchar>(i - radius, j - radius) |= (neighbor > center) << (neighbors - k - 1);//dst默认为CV_8UC1,因此只支持8个采样点
			}
		}
	}
	//进行旋转不变处理
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			unsigned char currentValue = src.at<uchar>(i, j);
			unsigned char minValue = currentValue;
			for (int k = 1; k < neighbors; k++)
			{
				//循环左移
				unsigned char temp = (currentValue >> (neighbors - k)) | (currentValue << k);
				if (temp < minValue)
				{
					minValue = temp;
				}
			}
			src.at<uchar>(i, j) = minValue;
		}
	}
}