#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5, K = 21, M = 1 << 20, modval = 1e9 + 7;
ll inv[K];

int n, k, arr[M];
ll dp[M][K][2];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    for (int i = 0; i < K; i++) inv[i] = pw(i, modval - 2);

    clr(dp, 0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        dp[arr[i]][0][0]++;
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < (1 << k); j++) {
            if (j & (1 << i)) continue;
            for (int l = k; l >= 0; l--) {
                if (l > 0) {
                    dp[j][l][0] = (dp[j][l][0] + dp[j ^ (1 << i)][l - 1][0]) % modval;
                    dp[j][l][1] = (dp[j][l][1] + dp[j ^ (1 << i)][l - 1][1]) % modval;

                    dp[j ^ (1 << i)][l][0] = (dp[j ^ (1 << i)][l - 1][0] + dp[j][l - 1][0]) % modval;
                    dp[j ^ (1 << i)][l][1] = (dp[j ^ (1 << i)][l - 1][1] + dp[j ^ (1 << i)][l - 1][0] + dp[j][l - 1][1]) % modval;
                }
                else {
                    dp[j ^ (1 << i)][l][0] = 0;
                    dp[j ^ (1 << i)][l][1] = 0;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ll ans = 0;
        for (int j = 0; j <= k; j++) {
            ans = (ans + dp[arr[i]][j][1] * inv[j] % modval) % modval;
        }
        cout << ans << "\n";
    }

	return 0;
}
