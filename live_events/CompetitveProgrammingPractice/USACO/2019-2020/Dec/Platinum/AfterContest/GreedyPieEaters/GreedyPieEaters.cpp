#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int N, M;
vector<vector<vector<int> > > PieRanges;

int main() {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);

    cin >> N >> M;
    PieRanges.resize(N, vector<vector<int> >(N, vector<int>(N)));

    for (int i = 0; i < M; i++) {
        int w, l, r;
        
        cin >> w >> l >> r;
        assert(l <= r);
        l--;
        r--;
        
        for (int j = l; j <= r; j++) PieRanges[j][l][r] = max(w, PieRanges[j][l][r]);
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j + i < N; j++) {
            for (int k = j; k <= j + i; k++) PieRanges[k][j][j + i] = max({PieRanges[k][j + 1][j + i], PieRanges[k][j][j + i - 1], PieRanges[k][j][j + i]});
        }
    }

    vector<vector<int> > Dp(N, vector<int>(N));

    for (int i = 0; i < N; i++) Dp[i][i] = PieRanges[i][i][i];

    for (int i = 1; i < N; i++) {
        for (int j = 0; j + i < N; j++) {
            Dp[j][j + i] = max(Dp[j + 1][j + i] + PieRanges[j][j][j + i], Dp[j][j + i - 1] + PieRanges[j + i][j][j + i]);

            for (int k = j + 1; k < j + i; k++) Dp[j][j + i] = max(Dp[j][k - 1] + Dp[k + 1][j + i] + PieRanges[k][j][j + i], Dp[j][j + i]);
            
            for (int k = j; k < j + i; k++) Dp[j][j + i] = max(Dp[j][k] + Dp[k + 1][j + i], Dp[j][j + i]);
        }
    }

    cout << Dp[0][N - 1] << "\n";

    return 0;
}
