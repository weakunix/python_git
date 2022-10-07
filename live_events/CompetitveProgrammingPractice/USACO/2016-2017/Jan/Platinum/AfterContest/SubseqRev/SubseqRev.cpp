#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int n, ans = 0;
vector<int> a;

int main() {
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);
    
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(n, vector<vector<int>>(50, vector<int>(50))));

    for (int i = 0; i < n; i++) dp[i][i][a[i]][a[i]] = 1;
    for (int i = 0; i < n - 1; i++) {
        dp[i][i + 1][a[i]][a[i]] = 1;
        dp[i][i + 1][a[i + 1]][a[i + 1]] = 1;
        dp[i][i + 1][min(a[i], a[i + 1])][max(a[i], a[i + 1])] = 2;
    }

    for (int i = 2; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            int end = j + i, left = a[j], right = a[end];
            for (int k = 0; k < 50; k++) {
                for (int l = k; l < 50; l++) {
                    dp[j][end][k][l] = max({dp[j + 1][end][k][l], dp[j][end - 1][k][l], dp[j][end][k][l]});
                    if (left <= k and right >= l) dp[j][end][left][right] = max(dp[j + 1][end - 1][k][l] + 2, dp[j][end][left][right]);
                    if (left <= k) dp[j][end][left][l] = max(dp[j + 1][end][k][l] + 1, dp[j][end][left][l]);
                    if (right >= l) dp[j][end][k][right] = max(dp[j][end - 1][k][l] + 1, dp[j][end][k][right]);
                    if (right <= k) dp[j][end][right][l] = max(dp[j + 1][end - 1][k][l] + 1, dp[j][end][right][l]);
                    if (left >= l) dp[j][end][k][left] = max(dp[j + 1][end - 1][k][l] + 1, dp[j][end][k][left]);
                    if (right <= k and left >= l) dp[j][end][right][left] = max(dp[j + 1][end - 1][k][l] + 2, dp[j][end][right][left]);
                }
            }
        }
    }

    for (int i = 0; i < 50; i++) {
        for (int j = i; j < 50; j++) ans = max(dp[0][n - 1][i][j], ans);
    }
    
    cout << ans << "\n";

    return 0;
}
