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

const int M = 3001, K = 10, S = 1 << K, modval = 1e9 + 7;

int t, n, m, k;
ll dp[M][S];

void upd(ll& a, ll b) {
    if (a == -1) a = b;
    else a = (a + b) % modval;
    return;
}

void subcase() {
    clr(dp, -1);

    cin >> n >> m >> k;
    for (int i = 0; i < n - 1; i++) cin >> dp[0][0];

    dp[0][0] = 1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < (1 << k); j++) {
            if (dp[i][j] == -1) continue;
            if (j & 1) {
                upd(dp[i + 1][j >> 1], dp[i][j]);
                continue;
            }

            int cnt = n + i + __builtin_popcount(j);
            upd(dp[i + 1][j >> 1], dp[i][j] * (2 * cnt - 1) % modval);

            for (int l = 1; l <= k; l++) {
                if (j & (1 << l)) continue;
                upd(dp[i + 1][(j ^ (1 << l)) >> 1], dp[i][j] * (cnt - 1) % modval);
            }
        }
    }

    cout << dp[m][0] << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
