#include "euclid.h"
void euclid(vector<float>& d1, vector<vector<string>>& d2, vector<float>& l1, vector<vector<string>>& l2, string& dis) {
	int k1 = 0, k2 = 0;
	vector<float> sum1, sum2;
	for (auto d : d2) {
		k1 = 0;
		float sum = 0;
		for (auto i : d) {
			if (k1 != 0){
				float m = stringToNum<float>(i);
				float n = d1[k1 - 1];
				sum += m * m + n * n;
			}
			k1++;
		}
		sum1.push_back(sqrt(sum));
	}
	for (auto l : l2) {
		k2 = 0;
		float sum = 0;
		for (auto i : l) {
			if (k2 != 0) {
				float m = stringToNum<float>(i);
				float n = l1[k2 - 1];
				sum += m * m + n * n;
			}
			k2++;
		}
		sum2.push_back(sqrt(sum));
	}
	int k = 0;
	vector<float> ed;
	for (auto i : sum1) {
		ed.push_back(i * sum2[k]);
		k++;
	}

	auto smallest = min_element(begin(ed), end(ed));
	dis = d2[distance(begin(ed), smallest)][0];
}