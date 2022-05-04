#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("triangles.out");
ifstream fin ("triangles.in");

int main() {
    int N;
    const int ModVal = 1000000007;
    long long AreaSum = 0;
    vector<pair<int, int> > Points;
    map<pair<int, int>, long long> PointToBase;
    unordered_map<int, vector<int> > XToY, YToX;
    fin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        fin >> a >> b;
        Points.push_back({a, b});
        if (XToY.count(a) == 0) XToY[a] = {b};
        else XToY[a].push_back(b);
        if (YToX.count(b) == 0) YToX[b] = {a};
        else YToX[b].push_back(a);
    }
    for (auto it = XToY.begin(); it != XToY.end(); it++) {
        int x = it->first;
        vector<int>& y = it->second;
        sort(all(y));
        long long Cur = 0;
        for (int i : y) Cur += i - y[0];
        PointToBase[make_pair(x, y[0])] = Cur;
        for (int i = 1; i < y.size(); i++) {
            Cur += (y[i] - y[i - 1]) * (2 * i - y.size());
            PointToBase[make_pair(x, y[i])] = Cur;
        }
    }
    for (auto it = YToX.begin(); it != YToX.end(); it++) {
        int y = it->first;
        vector<int>& x = it->second;
        sort(all(x));
        long long Cur = 0;
        for (int i : x) Cur += i - x[0];
        AreaSum += PointToBase[make_pair(x[0], y)] * Cur;
        AreaSum %= ModVal;
        for (int i = 1; i < x.size(); i++) {
            Cur += (x[i] - x[i - 1]) * (2 * i - x.size());
            AreaSum += PointToBase[make_pair(x[i], y)] * Cur;
            AreaSum %= ModVal;
        }
    }
    fout << AreaSum << "\n";
    return 0;
}
