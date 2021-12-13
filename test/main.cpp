#include "../include/dft.h"
#include "../include/lbp.h"
#include "../include/file.h"
#include "../include/euclid.h"
#include "../include/test.h"
/*
    Command Arguments
    0 | exe
    1 | type 0 - Add images
             1 - Search Image
    2 | path image path
*/
int main(int argc, char *argv[]){
    if (argc < 3){
        cerr << "Need more arguments!!!"<< endl;
        return 0;
    }
    switch (atoi(argv[1]))
    {
    case 0: {
        for (int i = 0; i < argc - 2; i++) {
            String path(argv[2+i]);
            Mat I = pre_process(path);
            Mat J = I.clone();

            size_t rings = 22;
            vector<float> f;
            //process_dft(I, f, rings);
            //for (auto i : f) cout << i << endl;

            vector<float> data;
            //rotate_lbp(J, data);
            //for (auto i : data) cout << i << endl;
            //imshow("elbp", J);
            int a = 0, b = 2;
            save_new_feature(path, a, f);
            save_new_feature(path, b, data);

        }
        break;
    }
    case 2: {
        String path(argv[2]);
        vector<string> files;
        string filepath = path + "*.jpg";
        glob(filepath, files, false);
        size_t count = files.size();

        for(size_t si=5;si<30;si++) {
            for (int i = 0; i < count; i++) {
                store_dft(files[i], si);
                cout << "process " << files[i] << ' ' << "size = " << si << "dft" <<endl;
            }
        }
        vector<vector<int>> re;
        for(int k=4; k< 12;k++){
            vector<int> rere;
            int a[k];
            for(int i=0; i< 10000000; i++){
                for(int & j : a) j = rand()%2;
                int res[k];
                int t;
                for(int ii=0;ii<k;ii++){
                    t=0;
                    res[ii]=0;
                    for(int j=0; j<k;j++){
                        res[ii] += a[(ii+j)%k] << t;
                        t++;
                    }
                }
                int temp =*min_element(res,res+k);
                bool flag = true;
                for(auto it : rere) if(it == temp ) flag= false;
                if(flag) rere.push_back(temp);
                sort(rere.begin(),rere.end());
                re.push_back(rere);
            }
        }
        for(int i=4;i<=12;i++){
            for(float d=0.5;d<5.0;) {
                store_lbp(files[i],i,d,re[i-4]);
                cout << "process " << files[i] << ' ' <<  "points = " << i << "dis=" << d << "lbp" <<endl;
                d+=0.1;
            }
        }
        /* INFO: group images input(path)
        for (int i = 0; i < count; i++){
            cout << "Processing " << files[i] << endl;
            Mat I = pre_process(files[i]);
            Mat J = I.clone();
            size_t rings = 22;
            vector<float> f;
            process_dft(I, f, rings);
            //for (auto i : f) cout << i << endl;
            vector<float> data;
            rotate_lbp(J, data);
            //for (auto i : data) cout << i << endl;
            //imshow("elbp", J);
            int a = 0, b = 2;

            save_new_feature(files[i], a, f);
            save_new_feature(files[i], b, data);
            cout << "done" << endl;
        }
        */
        break;
    }

    case 1:
    {
        String path(argv[2]);
        Mat I = pre_process(path);
        Mat J = I.clone();
        vector<vector<string>> dft_feature;
        vector<vector<string>> lbp_feature;
        int a = 0, b = 2;
        read_feature(a, dft_feature);
        read_feature(b, lbp_feature);

        size_t rings = 22;
        vector<float> f;
        //process_dft(I, f, rings);
        //for (auto i : f) cout << i << endl;

        vector<float> data;
        //rotate_lbp(J, data);

        string dis;
        euclid(f, dft_feature, data, lbp_feature, dis);
        cout<< dis;
    }
        break;
    default: {
        cerr << "Please input the correct data" << endl << " 0 - Add Image" << endl << " 1 - Search Image" << endl;
    }
    }
    

    waitKey(0);
    return 0;
}