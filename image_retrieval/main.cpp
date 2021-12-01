#include "dft.h"
#include "lbp.h"
#include "file.h"
#include "euclid.h"
#include "lbp_git.hpp"
#define dtf 0
#define lbp_1 1
#define lbp_2 2
#define lbp_3 3
/*
    �������룺
    0 | exe
    1 | type ���ͼƬ - 0/����ͼƬ -1
    2 | path ͼƬ·��
*/
int main(int argc, char *argv[]){
    if (argc < 3){
        cerr << "Need more arguments!!!"<< endl;
        return 0;
    }
    String path(argv[2]);
    Mat I = imread(path, IMREAD_GRAYSCALE);
    if (I.empty()) {
        cerr << "Can't find the iamge, Please input the correct path of the image!" << endl;
        return 0;
    }
    switch (atoi(argv[1]))
    {
    case 0: {
        for (int i = 0; i < argc - 2; i++) {
            String path(argv[2+i]);
            Mat I = imread(path, IMREAD_GRAYSCALE);
            Mat J = I.clone();
            DFT(I);
            size_t rings = 22;
            vector<float> f;
            sdof(I, f, rings);
            //for (auto i : f) cout << i << endl;
            //vector<float> data(256);
            //basic_lbp(J, data);
            //for (auto i : data) cout << i << endl;
            getRotationInvariantLBPFeature(J, 1, 8);
            imshow("elbp", J);
            int a = 0, b = 1;
            //save_new_feature(path, a, f);
            //save_new_feature(path, b, data);
        }
        break;
    }
    case 1:
    {
        // ���ݿ���������
        vector<vector<string>> dft_feature;
        vector<vector<string>> lbp_1_feature;
        int a = 0, b = 1;
        read_feature(a, dft_feature);
        read_feature(b, lbp_1_feature);
        // Ŀ��ͼƬ����
        Mat J = I.clone();
        DFT(I);
        size_t rings = 22;
        vector<float> f;
        sdof(I, f, rings);
        vector<float> data(256);
        basic_lbp(J, data);

        string dis;
        euclid(f, dft_feature, data, lbp_1_feature, dis);
        cout<< dis;
    }
        break;
    default:{
        cerr << "Please input the correct data" << endl << " 0 - Add Image" << endl << " 1 - Search Image" << endl;
    }
    }
    

    waitKey(0);
    return 0;
}



