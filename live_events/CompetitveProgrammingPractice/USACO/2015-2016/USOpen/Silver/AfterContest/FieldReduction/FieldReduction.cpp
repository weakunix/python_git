#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("reduce.out");
ifstream fin("reduce.in");

bool SortX(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

bool SortY(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

int GetMinArea(const vector<vector<int> >& CowsX, const vector<vector<int> >& CowsY, const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    int MinX = 0, MinY = 0, MaxX = 0, MaxY = 0;
    for (vector<int> v : CowsX) {
        if (v != a and v != b and v != c) {
            MinX = v[0];
            break;
        }
    }
    for (vector<int> v : CowsY) {
        if (v != a and v != b and v != c) {
            MinY = v[1];
            break;
        }
    }
    for (int i = CowsX.size() - 1; i >= 0; i--) {
        vector<int> v = CowsX[i];
        if (v != a and v != b and v != c) {
            MaxX = v[0];
            break;
        }
    }
    for (int i = CowsY.size() - 1; i >= 0; i--) {
        vector<int> v = CowsY[i];
        if (v != a and v != b and v != c) {
            MaxY = v[1];
            break;
        }
    }
    return (MaxX - MinX) * (MaxY - MinY);
}

int main() {
    int N, MinArea = -1;
    vector<vector<int> > CowsX, CowsY;
    set<vector<int> > ToRemove;
    fin >> N;
    for (int i = 0; i < N; i++) {
        vector<int> NewCow(2);
        fin >> NewCow[0] >> NewCow[1];
        CowsX.push_back(NewCow);
    }
    sort(all(CowsX), SortX);
    CowsY = CowsX;
    sort(all(CowsY), SortY);
    for (int i = 0; i < 4; i++) {
        ToRemove.insert(CowsX[i]);
        ToRemove.insert(CowsY[i]);
        ToRemove.insert(CowsX[CowsX.size() - i - 1]);
        ToRemove.insert(CowsY[CowsY.size() - i - 1]);
    }
    vector<vector<int> > VectToRemove(all(ToRemove));
    for (int i = 0; i < VectToRemove.size() - 2; i++) {
        vector<int> a = VectToRemove[i];
        for (int k = i + 1; k < VectToRemove.size() - 1; k++) {
            vector<int> b = VectToRemove[k];
            for (int j = k + 1; j < ToRemove.size(); j++) {
                vector<int> c = VectToRemove[j];
                if (MinArea == -1) MinArea = GetMinArea(CowsX, CowsY, a, b, c);
                else MinArea = min(GetMinArea(CowsX, CowsY, a, b, c), MinArea);
            }
        }
    }
    fout << MinArea << "\n";
    return 0;
}
