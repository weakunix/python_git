#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    int N, M, C, Day = 0, Ans = 0;
    unordered_set<int> CurCities = {0};
    cin >> N >> M >> C;
    vector<int> Cities(N), Profit(N);
    vector<vector<int> > Roads(N);
    for (int i = 0; i < N; i++) cin >> Cities[i];
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Roads[a].push_back(b);
    }
    while (Day < 1100) {
        vector<int> NewProfit(N, -1e9), TempCurCities;
        Day++;
        for (int i : CurCities) TempCurCities.push_back(i);
        CurCities.clear();
        for (int i : TempCurCities) {
            for (int j : Roads[i]) {
                CurCities.insert(j);
                NewProfit[j] = max(Profit[i] + Cities[j], NewProfit[j]);
            }
        }
        if (CurCities.count(0) > 0) Ans = max(NewProfit[0] - C * Day * Day, Ans);
        for (int i = 0; i < N; i++) Profit[i] = NewProfit[i];
    }
    cout << Ans << "\n";
    return 0;
}
