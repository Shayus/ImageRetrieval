#include "../include/euclid.h"
void euclid(vector<float>& d1, vector<vector<string>>& d2, vector<float>& l1, vector<vector<string>>& l2, string& dis) {
	int k1 = 0, k2 = 0;
	vector<float> sum1, sum2;
	for (auto d : d2) {
		k1 = 0;
		float sum = 0;
		for (auto i : d) {
			if (k1 != 0){
				float m = stringToNum<float>(i) - d1[k1-1];
				sum += m * m;
			}
			k1++;
		}
        if(k1==0) sum1.push_back(0);
        else sum1.push_back(sqrt(sum/float(k1)));
	}
	for (auto l : l2) {
		k2 = 0;
		float sum = 0;
		for (auto i : l) {
			if (k2 != 0) {
				float m = stringToNum<float>(i) - l1[k2 - 1];
				sum += m * m;
			}
			k2++;
		}if(k2==0){
            sum2.push_back(0);
        }else{
            sum2.push_back(sqrt(sum/float(k2)));
        }
	}
	int k = 0;
	vector<float> ed;
    /*
    // TODO： 测试一下仅傅里叶或者仅lbp时的算法准确度
    for (auto i : sum2) {
        ed.push_back(i);
        cout << i << endl;
        k++;
    }*/
    for (auto i : sum1) {
		ed.push_back(i * sum2[k]);
        cout << i*sum2[k] << endl;
		k++;
	}

	auto smallest = min_element(begin(ed), end(ed));
	dis = d2[distance(begin(ed), smallest)][0];
}