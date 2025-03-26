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

int n, p;
ll m;
vector<ll> cows, pack, dp[2];

ll getval(int idx) {
    if (idx == -1) return -1;
    if (idx >= pack.size()) return 2e18;
    return pack[idx];
}

int main() {
    cin >> m >> n >> p;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        for (ll j = l; j <= r; j += m) cows.pb(j);
    }
    for (int i = 0; i < p; i++) {
        ll l, r;
        cin >> l >> r;
        for (ll j = l; j <= r; j += m) pack.pb(j);
    }
    
    n = cows.size();
    p = pack.size();
    
    dp[0].resize(n);
    dp[1].resize(n);

    if (pack[0] <= cows[0]) {
        dp[0] = cows[0] - pack[0];
        dp[1] = 2 * dp[0];
    }

    for (int i = 1; i < n; i++) {
        ll prv = cows[i - 1], cur = cows[i];

        ll h = prv + (cur - prv) / 2
        ll ft = prv + (cur - prv) / 3
        ll lt = prv + (2 * (cur - prv) + 2) / 3

        int idxh = (ub(all(pack), h) - pack.begin()) - 1;
        int idxft = (ub(all(pack), ft) - pack.begin()) - 1;
        int idxlt = (ub(all(pack), lt) - pack.begin()) - 1;

        dp[0][i] = min(dp[0][i - 1] + 2 * max(getval(idx) - prv) + max(cur - getval(idx + 1)), dp[1][i - 1] + );
    }
    
	return 0;
}
