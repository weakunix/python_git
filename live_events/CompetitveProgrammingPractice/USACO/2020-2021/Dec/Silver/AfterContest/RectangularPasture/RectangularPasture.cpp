#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

bool SortX(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

bool SortY(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

int main() {
    int N;
    long long Total = 0;
    cin >> N;
    vector<pair<int, int> > Cows(N);
    unordered_map<int, int> YToX;
    vector<vector<int> > Pre;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        Cows[i] = {a, b};
    }
    sort(all(Cows), SortX);
    for (int i = 0; i < N; i++) Cows[i].first = i + 1;
    sort(all(Cows), SortY);
    for (int i = 0; i < N; i++) Cows[i].second = i + 1;
    for (pair<int, int> p : Cows) YToX[p.second] = p.first;
    for (int y = 0; y <= N; y++) {
        vector<int> NewRow(N + 1);
        if (y > 0) {
            for (int x = 1; x <= N; x++) {
                NewRow[x] = NewRow[x - 1] + Pre[y - 1][x] - Pre[y - 1][x - 1];
                if (YToX[y] == x) NewRow[x]++;
            }
        }
        Pre.push_back(NewRow);
    }
    for (pair<int, int> t : Cows) {
        for (pair<int, int> b : Cows) {
            int MinX = min(t.first, b.first), MinY = b.second, MaxX = max(t.first, b.first), MaxY = t.second;
            Total += (Pre[MaxY][MinX] - Pre[MinY - 1][MinX]) * (Pre[MaxY][N] - Pre[MaxY][MaxX - 1] - Pre[MinY - 1][N] + Pre[MinY - 1][MaxX - 1]);
            if (t == b) break;
        }
    }
    cout << Total + 1 << "\n";
    return 0;
}
