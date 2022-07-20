#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define all(v) v.begin(), v.end()

bool PtsSort(const pii& a, const pii& b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int main() {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);
    int N, CurEnd = -2e9, Ans;
    vector<pii> Pts;
    cin >> N;
    Ans = N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        Pts.push_back({x - y, x + y});
    }
    sort(all(Pts), PtsSort);
    for (const pii& p : Pts) {
        if (p.second <= CurEnd) Ans--;
        else CurEnd = p.second;
    }
    cout << Ans << "\n";
    return 0;
}
