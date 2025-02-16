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

const int N = 5e5, K = 20, modval = 1e9 + 7;

int n, k, idx[N];
ll ans[1 << K];
vector<int> cat[1 << K], highest[K];

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

ll f(int msk, int hi) { //FIXME
    ll res = 0;
    for (int i : highest[hi]) res = (res + inv(__builtin_popcount(msk | i))) % modval;
    return res;
}

int main() {
    clr(ans, 0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        idx[i] = cur;
        cat[cur].pb(i);

        int hbit = -1;
        for (int j = 0; j < k; j++) if (cur & (1 << j)) hbit = j;
        highest[hbit].pb(cur);
    }

    for (int i = 1; i < (1 << k); i++) {
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) {
                cout << i << " " << j << " " << f(i ^ (1 << j), j) << "\n";
                ans[i] = (ans[i] + f(i ^ (1 << j), j)) % modval;
            }
        }
    }

    for (int i = 0; i < n; i++) cout << ans[idx[i]] << "\n";

	return 0;
}
