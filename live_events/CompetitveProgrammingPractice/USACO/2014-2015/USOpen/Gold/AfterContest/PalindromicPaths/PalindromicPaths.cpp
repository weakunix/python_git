#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);

    const int ModVal = 1e9 + 7;
    int N;
    cin >> N;
    vector<string> Grid(N);
    vector<vector<ll> > Dp(N), NewDp;
    for (int i = 0; i < N; i++) Dp[i].resize(N);
    NewDp = Dp;
    
    for (int i = 0; i < N; i++) cin >> Grid[i];

    for (int i = 0; i < N; i++) Dp[i][i] = 1;
    for (int d = 1; d < N; d++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) NewDp[i][j] = 0;
        }
        for (int i = 0; i < N - d; i++) {
            if (d == 1 and i == 2)
                cout << "";
            int j = N - i - 1 - d;
            for (int k = d; k < N; k++) {
                int l = N - k - 1 + d;
                if (Grid[i][j] != Grid[k][l] or j > l) continue;
                NewDp[i][k] += Dp[i][k] + Dp[i + 1][k] + Dp[i][k - 1] + Dp[i + 1][k - 1];
                NewDp[i][k] %= ModVal;
            }
        }
        Dp = NewDp;
    }

    cout << Dp[0][N - 1] << "\n";
    return 0;
}
