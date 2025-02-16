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

const int N = 305, M = 3000, modval = 1e9 + 7;
ll fac[N], invfac[N];

int n, m = 1, a[N], b[N], rid[N][N], rmp[2 * N];
ll dp[M][2 * N], mul, invmul[N];
bool vis[M];
set<int> vals = {0};
map<int, int> mp;

ll pw(ll p, int q) {
    ll res = 1;
    while (q) {
        if (q & 1) res = res * p % modval;
        q >>= 1;
        p = p * p % modval;
    }
    return res;
}

ll inv(ll p) {
    return pw(p, modval - 2);
}

void dfs(int l, int r) {
    if (rid[l][r] != -1) return;

    if (l > r) {
        rid[l][r] = 0;
        return;
    }

    rid[l][r] = m;
    m++;

    for (int i = max(l, (l + r) / 2 - 1 + (l + r) % 2); i <= min(r, (l + r) / 2 + 1); i++) {
        dfs(l, i - 1);
        dfs(i + 1, r);
    }

    return;
}

void calc(int l, int r, int cnt, int cur) {
    if (vis[rid[l][r]]) return;
    vis[rid[l][r]] = true;

    if (l > r) {
        for (int i = 0; i <= cnt; i++) dp[rid[l][r]][i] = 1;
        return;
    }

    for (int i = 1; i <= cnt; i++) dp[rid[l][r]][i] = 0;

    for (int i = max(l, (l + r) / 2 - 1 + (l + r) % 2); i <= min(r, (l + r) / 2 + 1); i++) {
        calc(l, i - 1, cnt, cur);
        calc(i + 1, r, cnt, cur);
        if (a[i] <= rmp[cur] and b[i] > rmp[cur]) {
            for (int j = 1; j <= cnt; j++) dp[rid[l][r]][j] = (dp[rid[l][r]][j] + dp[rid[l][i - 1]][j] * dp[rid[i + 1][r]][j - 1] % modval) % modval;
        }
    }

    for (int i = 1; i <= cnt; i++) dp[rid[l][r]][i] = (dp[rid[l][r]][i] + dp[rid[l][r]][i - 1]) % modval;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    clr(rid, -1);
    clr(dp, 0);

    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % modval;
    invfac[N - 1] = inv(fac[N - 1]);
    for (int i = N - 2; i >= 0; i--) invfac[i] = invfac[i + 1] * (i + 1) % modval;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        b[i]++;
        vals.insert(a[i]);
        vals.insert(b[i]);
    }

    dfs(1, n);

    for (int i : vals) {
        rmp[mp.size()] = i;
        mp[i] = mp.size();
    }

    for (int i = 0; i < mp.size() - 1; i++) {
        int x = rmp[i + 1] - rmp[i], cnt = min(x, n + 1);

        clr(vis, false);
        calc(1, n, cnt, i);

        mul = 1;
        for (int j = 1; j <= cnt; j++) {
            mul = mul * (x - j) % modval;
            invmul[j] = inv(x - j);
        }

        for (int j = 0; j < m; j++) dp[j][0] = 0;
        
        if (cnt == x) for (int j = 0; j < m; j++) dp[j][0] = dp[j][x];
        else {
            for (int k = 1; k <= cnt; k++) {
                ll cur = (modval + mul % modval * invmul[k] % modval * invfac[k - 1] % modval * invfac[cnt - k] % modval * ((cnt - k) % 2 ? -1 : 1)) % modval;
                for (int j = 0; j < m; j++) dp[j][0] = (dp[j][0] + dp[j][k] * cur % modval) % modval;
            }
        }
    }

    cout << dp[1][0] << "\n";

	return 0;
}
