/*
Test outputs

1:
3
*/

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("measurement.out");
ifstream fin("measurement.in");

bool CowLogSortCondition(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

int GetPost(const vector<int>& Cows) {
    int MaxMilk = 0, Post = 0;
    for (int i = 0; i < 3; i++) {
        if (Cows[i] > MaxMilk) {
            MaxMilk = Cows[i];
            Post = i * 2 + 1;
        }
        else if (Cows[i] == MaxMilk) {
            Post += i * 2 + 1;
        }
    }
    return Post;
}

int main() {

    //Vars
    int N, CurPost = 9, NewPost, Changes = 0; //B: 1, E: 3, M: 5
    vector<int> Cows = {7, 7, 7};
    vector<vector<int> > CowLog;

    //Temp vars
    int temp_int;
    string temp_str;
    vector<int> temp_vect_int;

    fin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_int.clear();
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        fin >> temp_str;
        if (temp_str == "Bessie")
            temp_vect_int.push_back(0);
        else if (temp_str == "Elsie")
            temp_vect_int.push_back(1);
        else
            temp_vect_int.push_back(2);
        fin >> temp_int;
        temp_vect_int.push_back(temp_int);
        CowLog.push_back(temp_vect_int);
    }
    sort(CowLog.begin(), CowLog.end(), CowLogSortCondition);
    for (vector<int> v : CowLog) {
        Cows[v[1]] += v[2];
        NewPost = GetPost(Cows);
        if (NewPost != CurPost) {
            CurPost = NewPost;
            Changes += 1;
        }
    }
    fout << Changes << "\n";
    return 0;
}
