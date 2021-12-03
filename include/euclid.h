#pragma once
#include "init.h"
void euclid(vector<float>& d1, vector<vector<string>>& d2, vector<float>& l1, vector<vector<string>>& l2, string& dis);
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}