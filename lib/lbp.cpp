#include "../include/lbp.h"
#define M_PI 3.1415926
void basic_lbp(Mat& I, vector<float>& data) {
    Mat II = I.clone();
    int sum[8] = {0};
    int res[256] = {0};
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
            res[result] ++;
        }
    }
    for(auto re : res) data.push_back(float(re));
}
bool cmp2(const int n1, const int n2) {
    return n1 > n2;
}

void get_neighbors(Mat& I, int& i, int& j, vector<int>& a,int neighbors, float radius){
    float temp = I.at<float>(i,j);
    for(int n=0; n<neighbors; n++) {
        // sample points
        float x = radius * static_cast<float>(cos(2.0*M_PI*n/static_cast<float>(neighbors)));
        float y = radius * static_cast<float>(-sin(2.0*M_PI*n/static_cast<float>(neighbors)));
        // relative indices
        int fx = static_cast<int>(floor(x));
        int fy = static_cast<int>(floor(y));
        int cx = static_cast<int>(ceil(x));
        int cy = static_cast<int>(ceil(y));
        // fractional part
        float ty = y - float(fy);
        float tx = x - float(fx);
        // set interpolation weights
        float w1 = (1 - tx) * (1 - ty);
        float w2 =      tx  * (1 - ty);
        float w3 = (1 - tx) *      ty;
        float w4 =      tx  *      ty;
        // iterate through your data
        float t = w1*I.at<float>(i+fy,j+fx) + w2*I.at<float>(i+fy,j+cx) + w3*I.at<float>(i+cy,j+fx) + w4*I.at<float>(i+cy,j+cx);
        a.push_back(t>temp?1:0);
    }
}

void rotate_lbp(Mat& I, vector<float>& da, int i, float d, vector<int> com) {
    const size_t size = com.size();
    vector<int> rr(size,0);
    int k;
    vector<float> res,data;
    int wid = ceil(d);
    for(int m = wid; m < I.rows-wid; m++) {
        for(int n = wid; n < I.cols-wid; n++) {
            vector<int> a;
            get_neighbors(I,m,n,a,i,d);
            vector<int> temp(i,0);
            for(int ii=0;ii<i;ii++){
                k=0;
                for(int j=0; j<i;j++){
                    temp[ii] += a[(ii+j)%12] << k;
                    k++;
                }
            }
            int tmp = *min_element(temp.begin(),temp.end());
            for(int ii=0; ii<size;ii++){
                if(tmp == com[ii]){
                    rr[ii] ++;
                }
            }
        }
    }
    for(int ii=0; ii<size;ii++) data.push_back(float(rr[ii]));
    auto biggest = std::max_element(std::begin(data), std::end(data));
    auto smallest = std::min_element(std::begin(data), std::end(data));
    float fm = *biggest - *smallest;
    k=0;
    for(auto ii:data) {
        float tmp = ii - *smallest;
        da.push_back(tmp/fm);
        k++;
    }
}