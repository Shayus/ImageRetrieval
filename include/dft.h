#pragma once
#include "init.h"
// discrete fourier transform
void DFT(Mat& I);
// standard deviations of frequencies
void sdof(Mat& I, vector<float>& da, int& rings);
// process dft and output features
void process_dft(Mat& I, vector<float>& da, int& rings);