#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

#define all(v) v.begin(), v.end()

int main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    int N, M, K;
    const int ModVal = 1e9 + 9;
    cin >> N >> M >> K;
    vector<int> John(N), Paul(M);
    const vector<ll> DpRow(M + 1);
    const vector<vector<ll> > DpSection(N + 1, DpRow);
    vector<vector<vector<ll> > > Dp(K, DpSection);
    for (int i = 0; i < N; i++) cin >> John[i];
    for (int i = 0; i < M; i++) cin >> Paul[i];
    sort(all(John));
    sort(all(Paul));
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) Dp[0][n + 1][m + 1] = ((John[n] > Paul[m]) + Dp[0][n][m + 1] + Dp[0][n + 1][m] - Dp[0][n][m]) % ModVal;
    }
    for (int k = 1; k < K; k++) {
        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                Dp[k][n + 1][m + 1] = (((John[n] > Paul[m]) * Dp[k - 1][n][m] + Dp[k][n][m + 1]) % ModVal + (ModVal + Dp[k][n + 1][m] - Dp[k][n][m]) % ModVal) % ModVal;
            }
        }
    }
    cout << Dp[K - 1][N][M] << "\n";
    return 0;
}
