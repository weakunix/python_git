#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

int main() {
    int N, FirstVal;
    vector<pii> Points;
    set<int> XVals, YVals;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        XVals.insert(x);
        YVals.insert(y);
        Points.push_back({x, y});
    }
    if (XVals.size() <= 3 or YVals.size() <= 3) {
        cout << "1\n";
        return 0;
    }
    XVals.clear();
    YVals.clear();
    FirstVal = Points[0].first;
    for (const pii& p : Points) {
        if (p.first != FirstVal) {
            XVals.insert(p.first);
            YVals.insert(p.second);
        }
    }
    if (XVals.size() <= 2 or YVals.size() <= 2) {
        cout << "1\n";
        return 0;
    }
    XVals.clear();
    YVals.clear();
    FirstVal = Points[0].second;
    for (const pii& p : Points) {
        if (p.second != FirstVal) {
            XVals.insert(p.first);
            YVals.insert(p.second);
        }
    }
    if (XVals.size() <= 2 or YVals.size() <= 2) {
        cout << "1\n";
        return 0;
    }
    cout << "0\n";
    return 0;
}
