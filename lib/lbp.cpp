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
            //if(result>=256) cout << result << ' ';
            res[result] ++;
        }
    }
    for(auto re : res) data.push_back(float(re));
}
bool cmp2(const int n1, const int n2) {
    return n1 > n2;
}

void get_neighbors(Mat& I, int& i, int& j, vector<int>& a){
    int neighbors = 12;
    float radius = 1.5;
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

void rotate_lbp(Mat& I, vector<float>& data) {
    int com[352] = {0,1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99,101,103,105,107,109,111,113,115,117,119,121,123,125,127,133,135,137,139,141,143,145,147,149,151,153,155,157,159,163,165,167,169,171,173,175,177,179,181,183,185,187,189,191,195,197,199,201,203,205,207,209,211,213,215,217,219,221,223,227,229,231,233,235,237,239,241,243,245,247,249,251,253,255,273,275,277,279,281,283,285,287,291,293,295,297,299,301,303,307,309,311,313,315,317,319,325,327,329,331,333,335,339,341,343,345,347,349,351,355,357,359,361,363,365,367,371,373,375,377,379,381,383,397,399,403,405,407,409,411,413,415,421,423,425,427,429,431,435,437,439,441,443,445,447,455,457,459,461,463,467,469,471,473,475,477,479,485,487,489,491,493,495,499,501,503,505,507,509,511,585,587,589,591,595,597,599,603,605,607,613,615,619,621,623,627,629,631,635,637,639,661,663,667,669,671,679,683,685,687,691,693,695,699,701,703,715,717,719,723,725,727,731,733,735,743,747,749,751,755,757,759,763,765,767,819,821,823,827,829,831,845,847,853,855,859,861,863,871,875,877,879,885,887,891,893,895,925,927,939,941,943,949,951,955,957,959,975,981,983,987,989,991,1003,1005,1007,1013,1015,1019,1021,1023,1365,1367,1371,1375,1387,1391,1399,1403,1407,1455,1463,1467,1471,1495,1499,1503,1519,1527,1531,1535,1755,1759,1775,1783,1791,1911,1919,1983,2015,2047,4095};
    int rr[352] = {0};
    int k;
    vector<float> res;
    Mat II = I.clone();
    // calculate result
    for(int m = 2; m < I.rows-2; m++) {
        for(int n = 2; n < I.cols-2; n++) {
            vector<int> a;
            get_neighbors(I,m,n,a);
            vector<int> temp(12,0);
            for(int i=0;i<12;i++){
                k=0;
                for(int j=0; j<12;j++){
                    temp[i] += a[(i+j)%12] << k;
                    k++;
                }
            }
            int tmp = *min_element(temp.begin(),temp.end());
            for(int i=0; i<352;i++){
                if(tmp == com[i]){
                    rr[i] ++;
                }
            }
        }
    }
    for(int i=0; i<352;i++) data.push_back(float(rr[i]));


    auto biggest = std::max_element(std::begin(data), std::end(data));
    auto smallest = std::min_element(std::begin(data), std::end(data));
    //std::cout << "Max element is " << *biggest<< " at position " <<std::distance(std::begin(v), biggest) << std::endl;
    // std::cout << "min element is " << *smallest<< " at position " <<std::distance(std::begin(v), smallest) << std::endl;
    float fm = *biggest - *smallest;
    for(int i=0; i<=352;i++){
        data[i] = (data[i]-*smallest) / fm;
    }
}