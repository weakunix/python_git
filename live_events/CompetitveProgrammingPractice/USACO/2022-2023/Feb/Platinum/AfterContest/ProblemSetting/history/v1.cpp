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

const int N = 1e5 + 1, M = 20, S = 1 << M, modval = 1e9 + 7;
ll fact[N], invfact[N], f[N];

int n, m, arr[N], cnt[S];
ll dp[S], ans = 0;

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll inv(ll a) {
    return pw(a, modval - 2);
}

int main() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;
    f[0] = 0;
    for (int i = 1; i < N; i++) f[i] = (f[i - 1] + invfact[i - 1]) % modval;
    for (int i = 1; i < N; i++) f[i] = f[i] * fact[i] % modval;

    clr(arr, 0);
    clr(cnt, 0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == 'H') arr[j] |= 1 << i;
        }
    }

    for (int i = 0; i < n; i++) cnt[arr[i]]++;

    for (int i = 0; i < S; i++) {
        if (not cnt[i]) continue;
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if ((i & j) != j) continue;
            dp[i] = (dp[i] + dp[j]) % modval;
        }
        dp[i] = dp[i] * f[cnt[i]] % modval;
        ans = (ans + dp[i]) % modval;
    }

    cout << ans << "\n";

	return 0;
}
