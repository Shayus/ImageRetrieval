#pragma once
#include "../include/file.h"
void save_new_feature(String& path,int& type,vector<float>& f) {
    fstream outfile;
    bool flag = true;
    switch (type)
    {
    case 0:
        outfile.open("info/dft_22.csv", ios::app);
        break;
    case 1:
        outfile.open("info/lbp_basic.csv", ios::app);
        break;
    case 2:
        outfile.open("info/lbp_round.csv", ios::app);
        break;
    case 3:
        outfile.open("info/lbp_unit.csv", ios::app);
        break;
    default:
        flag = false;
    }
    if (flag) {
        outfile << path << ',';
        for (auto i : f) outfile << i << ',';
        outfile << endl;
        outfile.close();
    }
}
void read_feature(int& type, vector<vector<string>>& f) {
    fstream infile;
    bool flag = true;
    switch (type)
    {
    case 0:
        infile.open("info/dft_22.csv");
        break;
    case 1:
        infile.open("info/lbp_basic.csv");
        break;
    case 2:
        infile.open("info/lbp_round.csv");
        break;
    case 3:
        infile.open("info/lbp_unit.csv");
        break;
    default:
        flag = false;
    }
    if (flag) {
        if (!infile) {
            cout << "error" << endl;
        }
        String lineStr;
        while (getline(infile, lineStr))
        {
            // ��ɶ�ά��ṹ
            stringstream ss(lineStr);
            string str;
            vector<string> lineArray;
            // ���ն��ŷָ�
            while (getline(ss, str, ','))
                lineArray.push_back(str);
            f.push_back(lineArray);
        }
        infile.close();
    }
}