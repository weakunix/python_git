#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 250005;
const ll INF = 1e18;

int n, k;
ll v[N], pospfx[N], dp[N], spec = -INF, ans = 0;

int main() {
    dp[0] = 0; dp[1] = -INF;
    pospfx[0] = 0; pospfx[1] = 0;

    cin >> n >> k;
    for (int i = 2; i <= n + 1; i++) {
        cin >> v[i];
        pospfx[i] = pospfx[i - 1] + max(v[i], (ll) 0);
    }

    for (int i = 2; i < n + 1; i++) {
        dp[i] = -INF;

        if (i == k + 1) dp[1] = spec;
        if (spec < 0) spec = max(v[i], spec);
        else if (v[i] > 0) spec += v[i];

        for (int j = max(i - k, 0); j < i - 1; j++) {
            ll cur = dp[j];
            if (i != k + 1 or j != 1) cur += pospfx[i - 1] - pospfx[j + 1];
            dp[i] = max(cur, dp[i]);
        }
        dp[i] += v[i] + v[i + 1];
    }

    dp[1] = 0;
    for (int i = 1; i < n + 1; i++) {
        dp[i] += pospfx[min(i + k, n + 1)] - pospfx[i + 1];
        ans = max(dp[i], ans);
    }

    cout << ans << "\n";
	return 0;
}
