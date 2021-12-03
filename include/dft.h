#pragma once
#include "init.h"
// discrete fourier transform
void DFT(Mat& I);
// standard deviations of frequencies
void sdof(Mat& I, vector<float>& da, size_t& rings);