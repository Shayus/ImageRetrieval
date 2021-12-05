//
// Created by hao on 2021/12/3.
//
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
int main(){

    int a[12];
    for(int & i : a){
        i = rand()%2;
        cout << i << ' ';
    }
    cout << endl;
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
    for(int i=0; i<12;i++){
        cout << res[i] << endl;
    }
    return 0;
}
