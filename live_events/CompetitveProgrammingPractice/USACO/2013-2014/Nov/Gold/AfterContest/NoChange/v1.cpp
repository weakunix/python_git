#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 1e5 + 1, K = 16;

int n, k, coin[K], cost[N], ans = -1;
vector<vector<int>> dp;

int main() {
    cin >> k >> n;
    dp.resize(n + 1, vector<int>(1 << k, 2e9));
    for (int i = 0; i < k; i++) cin >> coin[i];
    for (int i = 0; i < n; i++) cin >> cost[i];

    for (int i = 0; i < (1 << k); i++) dp[0][i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << k); j++) dp[i][j] += cost[i];
        for (int j = 0; j < (1 << k); j++) {
            dp[i + 1][j] = min(dp[i][j], dp[i + 1][j]);
            for (int l = 0; l < k; l++) {
                if (j & (1 << l)) continue;
                if (coin[l] < dp[i][j]) continue;
                dp[i + 1][j ^ (1 << l)] = 0;
            }
        }
    }
    for (int i = 0; i < (1 << k); i++) {
        if (dp[n][i] > 0) continue;
        int cur = 0;
        for (int j = 0; j < k; j++) {
            if (not (i & (1 << j))) cur += coin[j];
        }
        ans = max(cur, ans);
    }
    cout << ans << "\n";
	return 0;
}
