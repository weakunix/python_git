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

ofstream fout("guess.out");
ifstream fin("guess.in");

int GetIntersection(const vector<string>& a, const vector<string>& b) {
    int Intersection = 0;
    for (string s : a) {
        if (count(b.begin(), b.end(), s) > 0)
            Intersection++;
    }
    return Intersection;
}

int main() {

    //Vars
    int N, MaxYes = 0;
    vector<vector<string> > Characteristics;

    //Temp vars
    int temp_int;
    string temp_str;
    vector<string> temp_vect_str;

    fin >> N;
    for (int i = 0; i < N; i++) {
        temp_vect_str.clear();
        fin >> temp_str >> temp_int;
        for (int k = 0; k < temp_int; k++) {
            fin >> temp_str;
            temp_vect_str.push_back(temp_str);
        }
        Characteristics.push_back(temp_vect_str);
    }
    for (int i = 0; i < N - 1; i++) {
        for (int k = i + 1; k < N; k++) {
            MaxYes = max(GetIntersection(Characteristics[i], Characteristics[k]), MaxYes);
        }
    }
    fout << MaxYes + 1 << "\n";
    return 0;
}
