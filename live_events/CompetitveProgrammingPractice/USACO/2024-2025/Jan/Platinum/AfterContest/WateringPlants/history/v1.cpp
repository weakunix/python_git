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

const int N = 5e5, W = 1e6 + 1;

int n, w[N], c[N], mxw = 0;
ll dp[2][W];

void setbest(ll& best, ll nw) {
    if (nw == -1) return;
    if (best == -1) best = nw;
    else setmn(best, nw);
    return;
}

int main() {
    clr(dp, -1);
    dp[0][0] = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        setmx(mxw, w[i]);
    }
    for (int i = 0; i < n - 1; i++) cin >> c[i];

    for (int i = 0; i < n - 1; i++) {
        int cur = i % 2, nxt = 1 - cur;
        ll best = -1, ans = -1;

        for (int j = mxw; j > w[i]; j--) setbest(best, dp[cur][j]);

        for (int j = 0; j <= mxw; j++) {
            if (w[i] - j >= 0) setbest(best, dp[cur][w[i] - j]);
            if (best != -1) dp[nxt][j] = best + (ll) j * c[i];
            else dp[nxt][j] = -1;
            if (j >= w[i + 1]) setbest(ans, dp[nxt][j]);
        }
        cout << ans << "\n";
    }

	return 0;
}
