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

const int N = 1e7 + 1, M = 5e5 + 1, modval = 998244353;
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
    if (cur < 0 or cur > tot) return 0;
    return fact[tot] * invfact[cur] % modval * invfact[tot - cur] % modval;
}

struct Poly {
    ll a, b, c;

    Poly() : a(0), b(0), c(0) {}

    Poly(ll _a, ll _b, ll _c) : a(_a), b(_b), c(_c) {}

    ~Poly() {}

    ll get(ll x) {
        return (a * (x - 1) % modval * (x - 2) % modval + b * (x - 1) % modval + c) % modval;
    }
};

int n, m, t, q;
Poly p;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;

    cin >> n >> m >> t;
    p = (t == 1 ? Poly(0, 1, 1) : Poly(1, 3, 1));
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;

        ll nwa = (p.a * choose(n - 3, a - 3) % modval + p.a * choose(n - 3, n - a - 3) % modval) % modval;
        ll nwb = (p.b * choose (n - 2, a - 2) % modval + (2 * p.a % modval * a % modval + p.b) % modval * choose(n - 2, n - a - 2) % modval) % modval;
        ll nwc = (p.c * choose(n - 1, a - 1) % modval + ((p.c + p.a * a % modval * a % modval + p.b * a % modval - p.a * a % modval) % modval + modval) % modval * choose(n - 1, n - a - 1) % modval) % modval;

        ll div = inv(choose(n, a));
        nwa = nwa * div % modval;
        nwb = nwb * div % modval;
        nwc = nwc * div % modval;

        p = Poly(nwa, nwb, nwc);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int cur;
        cin >> cur;
        cout << p.get(cur) << "\n";
    }

	return 0;
}
