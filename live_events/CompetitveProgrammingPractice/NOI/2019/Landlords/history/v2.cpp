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

const int N = 1e7 + 1, M = 5e5 + 1, modval = 998244353; //FIXME
ll fact[N], invfact[N];

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

struct Poly {
    ll a, b, c;

    Poly() : a(0), b(0), c(0) {}

    Poly(ll y1, ll y2, ll y3) : a(((y1 + y3 - 2 * y2) % modval + modval) % modval * inv(2) % modval), b(((-5 * y1 + 8 * y2 - 3 * y3) % modval + modval) % modval * inv(2) % modval), c(((3 * y1 - 3 * y2 + y3) % modval + modval) % modval) {}

    ~Poly() {}

    ll get(ll x) {
        return (a * x % modval * x % modval + b * x % modval + c) % modval;
    }
};

int n, m, t, q;
ll ans[N]; //FIXME
Poly p;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;

    cin >> n >> m >> t;
    p = (t == 1 ? Poly(1, 2, 3) : Poly(1, 4, 9));
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;

        for (int j = 1; j <= n; j++) ans[j] = p.get(j);

        ll cur[4] = {0, 0, 0, 0};
        for (int j = 1; j <= 3; j++) {
            for (int k = 1; k <= a; k++) cur[j] = (cur[j] + choose(j - 1, k - 1) * choose(n - j, a - k) % modval * ans[k] % modval) % modval;
            for (int k = 1; k <= n - a; k++) cur[j] = (cur[j] + choose(j - 1, k - 1) * choose(n - j, n - a - k) % modval * ans[a + k]) % modval;
            cur[j] = cur[j] * inv(choose(n, a)) % modval;
        }
        p = Poly(cur[1], cur[2], cur[3]);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int cur;
        cin >> cur;
        cout << p.get(cur) << "\n";
    }

	return 0;
}
