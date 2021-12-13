#include "../include/test.h"
#include "../include/dft.h"
#include "../include/lbp.h"
void store_dft(string path, int i){
    Mat I = pre_process(path);
    // 循环rings， 保存每一种rings下的特征
    fstream outfile;
    string s = "../src/dft_" +to_string(i) + ".csv";
    outfile.open(s, ios::app);
    outfile << path << ',';
    vector<float> f;
    process_dft(I,f,i);
    for (auto j : f) outfile << j << ',';
    outfile << endl;
    outfile.close();
}

void store_lbp(string path, int i, float d, vector<int> re){
    Mat I = pre_process(path);
    vector<float> f;
    rotate_lbp(I,f,i,d,re);
    d+=0.1;
    fstream outfile;
    string s = "../src/lbp_" + to_string(i) + "_" + to_string(d) + ".csv";
    outfile.open(s, ios::app);
    outfile << path << ',';
    for (auto ii : f) outfile << ii << ',';
    outfile << endl;
    outfile.close();
}