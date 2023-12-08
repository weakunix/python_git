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
ll v[N], dp[N], spec = -INF, ans = 0;

int main() {

    cin >> n >> k;
    for (int i = 2; i <= n + 1; i++) cin >> v[i];
    dp[0] = 0;
    dp[1] = -INF;
    for (int i = 2; i < n + 1; i++) {
        dp[i] = -INF;
        if (i == k + 1) dp[1] = spec;
        if (spec < 0) spec = max(v[i], spec);
        else if (v[i] > 0) spec += v[i];
        for (int j = max(i - k, 0); j < i - 1; j++) {
            ll cur = dp[j];
            if (i != k + 1 or j != 1) {
                for (int k = j + 2; k < i; k++) {
                    if (v[k] > 0) cur += v[k];
                }
            }
            dp[i] = max(cur, dp[i]);
        }
        dp[i] += v[i] + v[i + 1];
    }
    dp[1] = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = i + 2; j <= i + k and j <= n + 1; j++) {
            if (v[j] > 0) dp[i] += v[j];
        }
        ans = max(dp[i], ans);
    }
    cout << ans << "\n";
	return 0;
}
