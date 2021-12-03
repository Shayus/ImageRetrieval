#pragma once
#include "init.h"
#include <fstream>
void save_new_feature(String& path,int& type, vector<float>& f);
void read_feature(int& type, vector<vector<string>>& f);