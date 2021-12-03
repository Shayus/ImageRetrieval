#include "../include/dft.h"
void DFT(Mat& I) {
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols);
    //cout << "before f   " << m << " " << n << endl;
    Mat padded;
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);
    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];
    magnitudeImage += Scalar::all(1);
    for (int i = 0; i < magnitudeImage.rows; ++i) {
        for (int j = 0; j < magnitudeImage.cols; ++j) {
            magnitudeImage.at<float>(i, j) = log(abs(magnitudeImage.at<float>(i, j)) + 1);
        }
    }
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
    I = magnitudeImage;
}
// standard deviations of frequencies
void sdof(Mat& I, vector<float>& da, size_t& rings) {
    Mat II = I.clone();
    //normalize(II, II, 0, 1, NORM_MINMAX);
    //cout << "before f   " << II.rows << " " << II.cols << endl;
    //imshow("test", I);
    int a = I.rows <= I.cols ? I.rows : I.cols;
    //cout << a;
    float step = a / rings / 2;
    int a2 = a / 2;
    vector<info> m;
    info Info;
    for (int i = 0; i <= rings; i++) m.push_back(Info);
    int i, j;
    for (i = 0; i < a; ++i) {
        float* p = II.ptr<float>(i);
        for (j = 0; j < a; ++j) {
            int k;
            int r = (i - a2) * (i - a2) + (j - a2) * (j - a2);
            //int r = i * i + j * j;
            float pixel = p[j];
            //cout << pixel <<" ";
            for (k = 0; k <= rings; k++) {
                //float pixel = 10 * (p[j] / 10); // ���ַ������Լӿ��㷨�������Ȼ��½�
                if (r > (k * step * k * step) && r < (k + 1) * step * (k + 1) * step) {
                    vector<float>::iterator it = find(m[k].data.begin(), m[k].data.end(), pixel);
                    if (it == m[k].data.end()) {
                        m[k].data.push_back(pixel);
                        m[k].n.push_back(1);
                    }
                    else {
                        int index = &*it - &m[k].data[0];
                        m[k].n[index]++;
                    }
                }
            }
        }
    }

    //imshow("rings", II);
    i = 0;
    for (auto it : m) {
        float a = 0, b = 0;
        int k = 0;
        int dk = 0;
        for (auto itt : it.data) {
            a += m[i].n[k] * itt;
            b += m[i].n[k] * itt * itt;
            dk += m[i].n[k];
            k++;
        }
        da.push_back(sqrt((dk * b - a * a) / ((dk - 1) * dk)));
        //cout << i << " ring: " << da[i] << "with dk:" << dk <<endl;
        i++;
    }
}