//
// Created by hao on 2021/12/3.
// Used to generate n-points min map
//
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
int main(){
    vector<int> re;
    int a[12];
    for(int i=0; i< 10000000; i++){
        for(int & i : a){
            i = rand()%2;
        }
        //cout << endl;
        int res[12];
        int k;
        for(int i=0;i<12;i++){
            k=0;
            res[i]=0;
            for(int j=0; j<12;j++){
                //cout << (i+j)%12;
                res[i] += a[(i+j)%12] << k;
                k++;
            }
        }
        int temp =*min_element(res,res+12);
        bool flag = true;
        for(auto it : re) if(it == temp ) flag= false;
        if(flag) re.push_back(temp);
    }
    sort(re.begin(),re.end());
    for(auto it : re) cout << it << ' ';
    cout << endl;
    cout << re.size();
    return 0;
}
