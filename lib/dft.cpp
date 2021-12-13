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
void sdof(Mat& I, vector<float>& da, int& rings) {
    Mat II = I.clone();
    //normalize(II, II, 0, 1, NORM_MINMAX);
    //cout << "before f   " << II.rows << " " << II.cols << endl;
    //imshow("test", I);
    int a = I.rows <= I.cols ? I.rows : I.cols;
    //cout << a;
    float step = float(a) / float(rings) / 2;
    float a2 = float(a) / 2;
    vector<info> m;
    info Info;
    for (int i = 0; i <= rings; i++) m.push_back(Info);
    int i, j;
    for (i = 0; i < a; ++i) {
        auto* p = II.ptr<float>(i);
        for (j = 0; j < a; ++j) {
            int k;
            auto ii = float(i);
            auto jj = float(j);
            float r = (ii - a2) * (ii - a2) + (jj - a2) * (jj - a2);
            float pixel = p[j];
            for (k = 0; k <= rings; k++) {
                //float pixel = 10 * (p[j] / 10); // make the process quicker but less accuracy
                if (r > (float(k*k) * step * step) && r < float((k + 1)*(k + 1)) * step *  step) {
                    auto it = find(m[k].data.begin(), m[k].data.end(), pixel);
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

    i = 0;
    for (const auto& it : m) {
        float sum_a = 0, sum_b = 0;
        int k = 0;
        float dk = 0;
        for (auto itt : it.data) {
            auto tmp = float(m[i].n[k]);
            sum_a += tmp * itt;
            sum_b += tmp * itt * itt;
            dk += tmp;
            k++;
        }
        da.push_back(sqrt((dk * sum_b - sum_a * sum_a) / ((dk - 1) * dk)));
        i++;
    }
}

void process_dft(Mat& I, vector<float>& da, int& rings){
    rings = rings-1;
    vector<float> data;
    DFT(I);
    sdof(I,data,rings);
    auto biggest = std::max_element(std::begin(data), std::end(data));
    auto smallest = std::min_element(std::begin(data), std::end(data));
    float fm = *biggest - *smallest;
    int k=0;
    for(auto i:data) {
        float tmp = i - *smallest;
        da.push_back(tmp/fm);
        k++;
    }
}