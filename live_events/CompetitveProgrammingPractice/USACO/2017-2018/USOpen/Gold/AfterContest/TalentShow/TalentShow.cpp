#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

const int MaxN = 250;
int N, W, Talents[MaxN], Weights[MaxN];

bool IsPsbl(const ll Ratio) {
    vector<vector<ll> > Dp;
    vector<vector<bool> > Works;
    for (int w = 0; w <= W; w++) {
        vector<ll> DpRow(N);
        vector<bool> WorksRow(N);
        Dp.push_back(DpRow);
        Works.push_back(WorksRow);
    }
    Works[0][0] = true;
    Works[min(Weights[0], W)][0] = true;
    Dp[min(Weights[0], W)][0] = 1000 * Talents[0] - Ratio * Weights[0];
    for (int n = 0; n < N - 1; n++) {
        for (int w = 0; w <= W; w++) {
            if (Works[w][n]) {
                if (Works[w][n + 1]) Dp[w][n + 1] = max(Dp[w][n], Dp[w][n + 1]);
                else {
                    Works[w][n + 1] = true;
                    Dp[w][n + 1] = Dp[w][n];
                }
                int CurW = min(w + Weights[n + 1], W);
                ll CurT = 1000 * Talents[n + 1] - Ratio * Weights[n + 1];
                if (Works[CurW][n + 1]) Dp[CurW][n + 1] = max(Dp[w][n] + CurT, Dp[CurW][n + 1]);
                else {
                    Works[CurW][n + 1] = true;
                    Dp[CurW][n + 1] = Dp[w][n] + CurT;
                }
            }
        }
    }
    return (Works[W][N - 1] and Dp[W][N - 1] >= 0);
}

int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    ll Low = 0, High = 1e6;
    cin >> N >> W;
    for (int i = 0; i < N; i++) cin >> Weights[i] >> Talents[i];
    while (Low < High) {
        ll Mid = Low + (High - Low + 1) / 2;
        if (IsPsbl(Mid)) Low = Mid;
        else High = Mid - 1;
    }
    assert(Low == High);
    cout << Low << "\n";
    return 0;
}
