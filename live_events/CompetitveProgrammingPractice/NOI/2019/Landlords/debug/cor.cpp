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

const int N = 101, M = 5e5 + 1, modval = 998244353; //FIXME
ll fact[N], invfact[N];

int n, m, t, q;
ll ans[M][N]; //FIXME

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

ll choose(int tot, int cur) {
    if (cur < 0 or cur > tot) return 0; //FIXME
    return fact[tot] * invfact[cur] % modval * invfact[tot - cur] % modval;
}

int main() {
    clr(ans, 0);

    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;

    cin >> n >> m >> t;
    for (ll i = 1; i <= n; i++) ans[0][i] = (t == 1 ? i : i * i % modval);
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= a; k++) ans[i + 1][j] = (ans[i + 1][j] + choose(j - 1, k - 1) * choose(n - j, a - k) % modval * ans[i][k] % modval) % modval;
            for (int k = 1; k <= n - a; k++) ans[i + 1][j] = (ans[i + 1][j] + choose(j - 1, k - 1) * choose(n - j, n - a - k) % modval * ans[i][a + k]) % modval;
            ans[i + 1][j] = ans[i + 1][j] * inv(choose(n, a)) % modval;
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int cur;
        cin >> cur;
        cout << ans[m][cur] << "\n";
    }

	return 0;
}
