#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ofstream fout("balancing.out");
ifstream fin("balancing.in");


bool SortCowsX(const vector<int>& a, const vector<int>&b) {
    return a[0] < b[0];
}

bool SortCowsY(const vector<int>& a, const vector<int>&b) {
    return a[1] < b[1];
}

int main() {
    int N, Best = 1000;
    fin >> N;
    vector<vector<int> > CowsX(N);
    for (int i = 0; i < N; i++) {
        vector<int> Cow(2);
        fin >> Cow[0] >> Cow[1];
        CowsX[i] = Cow;
    }
    vector<vector<int> > CowsY = CowsX;
    sort(CowsX.begin(), CowsX.end(), SortCowsX);
    sort(CowsY.begin(), CowsY.end(), SortCowsY);
    map<int, vector<int> > XVals, YVals;
    for (vector<int> v : CowsX) {
        if (XVals.count(v[0]) == 0) XVals[v[0]] = {v[1]};
        else XVals[v[0]].push_back(v[1]);
    }
    for (vector<int> v : CowsY) {
        if (YVals.count(v[1]) == 0) YVals[v[1]] = {v[0]};
        else YVals[v[1]].push_back(v[0]);
    }
    int tl = 0, tr = N, bl = 0, br = 0;
    for (auto ity = YVals.begin(); ity != YVals.end(); ity++) {
        tr += tl;
        tl = 0;
        br += bl;
        bl = 0;
        tr -= ity->second.size();
        br += ity->second.size();
        Best = min(max(max(tl, tr), max(bl, br)), Best);
        for (auto itx = XVals.begin(); itx != XVals.end(); itx++) {
            for (int i = 0; i < itx->second.size(); i++) {
                if (itx->second[i] > ity->first) {
                    tr--;
                    tl++;
                }
                else {
                    br--;
                    bl++;
                }
                Best = min(max(max(tl, tr), max(bl, br)), Best);
            }
        }
    }
    fout << Best << "\n";
    return 0;
}
