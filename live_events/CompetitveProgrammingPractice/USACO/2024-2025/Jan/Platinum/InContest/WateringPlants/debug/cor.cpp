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

const int N = 5000, W = 201;

int n;
ll w[N], c[N], dp[N][W];

int main() {
    clr(dp, -1);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) cin >> c[i];

    dp[0][w[0]] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < W; j++) {
            if (dp[i][j] == -1) continue;

            for (int k = j; k <= max(w[i + 1], (ll) j); k++) {
                ll& nxt = dp[i + 1][max(w[i + 1] - k, 0ll)];
                if (nxt == -1) nxt = dp[i][j] + k * c[i];
                else setmn(nxt, dp[i][j] + k * c[i]);
            }
        }
    }

    for (int i = 1; i < n; i++) cout << dp[i][0] << "\n";

	return 0;
}
