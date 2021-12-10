#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
#include <io.h>
#include <fstream>

using namespace std;
using namespace cv;
struct info {
    vector<float> data;
    vector<int> n;
};
Mat read_image(string path);
void rgb2hsv_change_v(Mat& I);
Mat pre_process(string path);