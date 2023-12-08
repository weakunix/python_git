#include <iostream>
#include <cstdio>
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

const int N = 1e5 + 1, K = 16, S = 1 << K;

int n, k, coin[K], pfx[N], dp[S], ans = -1;

int main() {
    freopen("nochange.in", "r", stdin);
    freopen("nochange.out", "w", stdout);

    memset(dp, 0, sizeof(dp));
    pfx[0] = 0;

    cin >> k >> n;
    for (int i = 0; i < k; i++) cin >> coin[i];
    for (int i = 1; i <= n; i++) {
        cin >> pfx[i];
        pfx[i] += pfx[i - 1];
    }

    for (int i = 1; i < (1 << k); i++) {
        for (int j = 0; j < k; j++) {
            if (not (i & (1 << j))) continue;
            dp[i] = max((int) (upper_bound(pfx, pfx + n + 1, pfx[dp[i ^ (1 << j)]] + coin[j]) - pfx) - 1, dp[i]);
        }
        if (dp[i] != n) continue;
        int cur = 0;
        for (int j = 0; j < k; j++) {
            if (not (i & (1 << j))) cur += coin[j];
        }
        ans = max(cur, ans);
    }

    cout << ans << "\n";
	return 0;
}
