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

const int N = 6e5 + 1, modval = 998244353;

int t, n, arr[N];
ll fac[2 * N], invfac[2 * N];
bool vis[N];

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

ll choose(ll a, ll b) {
    if (a < 0) return 0;
    if (b < 0 or b > n) return 0;
    return fac[a] * invfac[b] % modval * invfac[a - b] % modval;
}

ll catnum(ll a, ll b) {
    return (choose(2 * n - a - b, n - b) - choose(2 * n - a - b, n - b - 1) + modval) % modval;
}

void subcase() {
    clr(vis, false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> arr[i];

    int mx = 0, mn = 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + catnum(i - 1, max(mx, arr[i]) + 1)) % modval;

        if (arr[i] > mn and arr[i] < mx) break;
        setmx(mx, arr[i]);
        vis[arr[i]] = true;
        while (vis[mn]) mn++;
    }
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    fac[0] = 1;
    for (int i = 1; i < 2 * N; i++) fac[i] = fac[i - 1] * i % modval;
    invfac[2 * N - 1] = inv(fac[2 * N - 1]);
    for (int i = 2 * N - 2; i >= 0; i--) invfac[i] = invfac[i + 1] * (i + 1) % modval;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();

	return 0;
}
