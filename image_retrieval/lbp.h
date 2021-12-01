#pragma once
#include "init.h"
//const int revolve_map[] = { 0,1,3,5,7,9,11,13,15,17,19,21,23,24,27,29,31,37,39,43,45,47,51,53,55,59,61,63,85,87,91,95,111,119,127,255 };
//const int uniform_map[] = {0,1,2,3,4,6,7,8,12,14,15,16,24,28,30,31,32,48,56,60,62,63,64,96,112,120,124,126,127,128,129,131,135,143,159,191,192,193,195,199,207,223,224,225,227,231,239,240,241,243,247,248,249,251,252,253,254,255 };
void basic_lbp(Mat& I, vector<float>& data);
void getRotationInvariantLBPFeature(Mat& src, int radius, int neighbors);