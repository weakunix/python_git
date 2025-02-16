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

const int N = 300, K = 8, S = (1 << K);

int n, k, w[S];
ll dp[N][N][S], ans = 0;
bool s[N], rep[S];

int main() {
    clr(dp, -1);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s[i] = (c == '1');
    }
    for (int i = 0; i < (1 << k); i++) cin >> rep[i] >> w[i];

    for (int i = 0; i < n; i++) dp[i][i][s[i]] = 0;

    for (int len = 2; len <= n; len++) {
        int fin = len % (k - 1);
        if (fin == 0) fin = k - 1;
        if (fin == 1) fin = k;
        
        for (int l = 0, r = l + len - 1; r < n; l++, r++) {
            for (int mid = r - 1; mid >= l; mid -= k - 1) {
                for (int x = 0; x < (1 << fin); x++) {
                    if (dp[l][mid][x >> 1] == -1 or dp[mid + 1][r][x & 1] == -1) continue;
                    ll cur = dp[l][mid][x >> 1] + dp[mid + 1][r][x & 1];
                    if (fin == k) {
                        cur += w[x];
                        if (dp[l][r][rep[x]] == -1) dp[l][r][rep[x]] = cur;
                        setmx(dp[l][r][rep[x]], cur);
                    }
                    else {
                        if (dp[l][r][x] == -1) dp[l][r][x] = cur;
                        setmx(dp[l][r][x], cur);
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < (1 << ((n - 1) % (k - 1) + 1)); i++) setmx(ans, dp[0][n - 1][i]);

    cout << ans << "\n";

	return 0;
}
