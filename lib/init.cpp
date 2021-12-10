#include "../include/init.h"
Mat read_image(string path) {
    Mat I = imread(path, IMREAD_COLOR);
    if (I.empty()) {
        cerr << "Can't find the image, Please input the correct path of the image!" << endl;
        exit(1);
    }
    int co = I.cols, ro = I.rows;
    int i_size = co < ro ? co : ro;
    Mat N(i_size, i_size, CV_8UC3);
    if (co > ro) {
        Rect area((co - ro) / 2, 0, i_size, i_size);
        N = I(area);
    } else {
        Rect area(0, (ro - co) / 2, i_size, i_size);
        N = I(area);
    }
    resize(N, N, Size(256, 256));
    //imshow(path, N);
    return N;
}

void rgb2hsv_change_v(Mat& I){
    cvtColor(I,I,COLOR_BGR2HSV);
    vector<Mat> channels;
    split(I,channels);
    equalizeHist(channels[2],channels[2]);
    merge(channels,I);
}

Mat pre_process(string path){
    Mat I = read_image(path);
    rgb2hsv_change_v(I);
    Mat dst;
    cvtColor(I,I,COLOR_HSV2BGR);
    cvtColor(I,dst,COLOR_BGR2GRAY);
    return dst;
}