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

const int N = 31, M = 101, K = 31, modval = 998244353;

int n, m, k, arr[M];
ll fact[N], inv[N], dp[M][N][K][N], ans = 0;

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
    clr(dp, -1);

    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    inv[N - 1] = pw(fact[N - 1], modval - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % modval;

    cin >> n >> m >> k;
    for (int i = 0; i <= m; i++) cin >> arr[i];

    ll curpw = 1;
    for (int i = 0; i <= n; i++) {
        dp[0][i][i & 1][i >> 1] = inv[i] * curpw % modval;
        curpw = curpw * arr[0] % modval;
    }

    for (int i = 0; i < m; i++) {
        curpw = 1;
        for (int c = 0; c <= n; c++) {
            for (int j = 0; j + c <= n; j++) {
                for (int o = 0, cur = c; o < N; o++, cur++) {
                    for (int l = 0; l + (cur & 1) <= k; l++) {
                        ll &curstate = dp[i + 1][j + c][l + (cur & 1)][cur >> 1];
                        if (dp[i][j][l][o] == -1) continue;
                        ll curval = dp[i][j][l][o] * inv[c] % modval * curpw % modval;
                        if (curstate == -1) curstate = curval;
                        else curstate = (curstate + curval) % modval;
                    }
                }
            }
            curpw = curpw * arr[i + 1] % modval;
        }
    }

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < N; j++) {
            ll curval = dp[m][n][i][j];
            if (curval == -1) continue;
            if (__builtin_popcount(j) + i <= k) ans = (ans + curval * fact[n] % modval) % modval;
        }
    }

    cout << ans << "\n";

	return 0;
}
