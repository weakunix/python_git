/*
Test outputs

1:
2
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("balancing.out");
ifstream fin("balancing.in");

int MaxQuarter(const vector<vector<int> >& Points, int x, int y) {
    int a = 0, b = 0, c = 0, d = 0;
    for (vector<int> v : Points) {
        if (v[0] < x and v[1] < y)
            a++;
        else if (v[0] > x and v[1] < y)
            b++;
        else if (v[0] < x and v[1] > y)
            c++;
        else
            d++;
    }
    return max(max(a, b), max(c, d));
}

int main() {
    int N, B, Best = 100;
    vector<vector<int> > Points;
    vector<int> XVals, YVals;
    fin >> N >> B;
    for (int i = 0; i < N; i++) {
        vector<int> temp_vect_int(2);
        fin >> temp_vect_int[0] >> temp_vect_int[1];
        Points.push_back(temp_vect_int);
        if (count(XVals.begin(), XVals.end(), temp_vect_int[0]) == 0)
            XVals.push_back(temp_vect_int[0]);
        if (count(YVals.begin(), YVals.end(), temp_vect_int[1]) == 0)
            YVals.push_back(temp_vect_int[1]);
    }
    sort(YVals.begin(), YVals.end());
    sort(XVals.begin(), XVals.end());
    for (int x : XVals) {
        for (int y : YVals)
            Best = min(MaxQuarter(Points, x + 1, y + 1), Best);
    }
    fout << Best << "\n";
    return 0;
}
