#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    int N, K, CurMax = 0, Total = 0;
    cin >> N >> K;
    vector<int> Snakes(N);
    vector<vector<int> > Dp(K + 1);
    for (int i = 0; i < N; i++) cin >> Snakes[i];
    for (int n = 0; n < N; n++) {
        int MaxNet = 0;
        CurMax = max(Snakes[n], CurMax);
        Total += Snakes[n];
        for (int k = 0; k <= K; k++) Dp[k].push_back((n + 1) * CurMax);
        for (int i = n - 1; i >= 0; i--) {
            MaxNet = max(Snakes[i + 1], MaxNet);
            for (int k = 1; k <= K; k++) {
                Dp[k][n] = min(Dp[k - 1][i] + (n - i) * MaxNet, Dp[k][n]);
            }
        }
    }
    cout << Dp[K][N - 1] - Total << "\n";
    return 0;
}
