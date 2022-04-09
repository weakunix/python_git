/*
Test outputs

1:
4
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("blist.out");
ifstream fin("blist.in");

bool CompareCow(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

int main() {
    
    //Vars
    int N, Idle = 0, InUse = 0;
    vector<vector<int> > Cows;
    
    //Temp vars
    int temp_int;
    vector<int> temp_vect_int;

    fin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_int.clear();
        for (int k = 0; k < 3; k++) {
            fin >> temp_int;
            temp_vect_int.push_back(temp_int);
        }
        temp_vect_int.push_back(0);
        Cows.push_back(temp_vect_int);
    }
    sort(Cows.begin(), Cows.end(), CompareCow);
    for (int i = 0; i < N; i++) {
        temp_vect_int = Cows[i];
        temp_int = temp_vect_int[0];
        for (int k = 0; k < i; k++) {
            if (Cows[k][1] <= temp_int and Cows[k][3] == 0) {
                Cows[k][3] = 1;
                InUse -= Cows[k][2];
                Idle += Cows[k][2];
            }
        }
        Idle -= temp_vect_int[2];
        InUse += temp_vect_int[2];
        if (Idle < 0) {
            Idle = 0;
        }
    }
    fout << Idle + InUse << "\n";
    return 0;
}
