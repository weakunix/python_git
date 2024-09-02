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

const int N = 10, M = 1 << N;

int n, m, c[M], f[M][M], cost[M][N];
ll ans = 2e9;
bool arr[M];
unordered_map<int, unordered_map<int, ll>> dp[2 * M];

int getcost(int node, int st) {
    if (node >= m) return f[st][node - m];
    return getcost(2 * node, st) + getcost(2 * node + 1, st);
}

ll getdp(int node, int cnt, int par, int dep, int leafcnt) {
    if (dp[node].count(cnt) and dp[node][cnt].count(par)) return dp[node][cnt][par];

    if (dep < n) {
        dp[node][cnt][par] = 2e9;
        int newpar = (par << 1) | (2 * cnt > leafcnt);
        for (int i = 0; i <= cnt; i++) {
            if (i > leafcnt / 2 or cnt - i > leafcnt / 2) continue;
            setmn(dp[node][cnt][par], getdp(2 * node, i, newpar, dep + 1, leafcnt / 2) + getdp(2 * node + 1, cnt - i, newpar, dep + 1, leafcnt / 2));
        }
        return dp[node][cnt][par];
    }

    assert(cnt == 0 or cnt == 1);
    dp[node][cnt][par] = (arr[node - m] == cnt ? 0 : c[node - m]);
    for (int i = 0; i < n; i++) {
        if (((par & (1 << i)) > 0) xor cnt) {
            dp[node][cnt][par] += cost[node - m][i];
        }
    }
    return dp[node][cnt][par];
}

int main() {
    cin >> n;
    m = 1 << n;
    for (int i = 0; i < m; i++) cin >> arr[i];
    for (int i = 0; i < m; i++) cin >> c[i];
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            cin >> f[i][j];
            f[j][i] = f[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        int prv = i + m;
        for (int j = 0; j < n; j++) {
            int cur = prv / 2;
            cost[i][j] = getcost((2 * cur == prv) ? 2 * cur + 1 : 2 * cur, i);
            prv = cur;
        }
    }

    for (int i = 0; i <= m; i++) setmn(ans, getdp(1, i, 0, 0, m));
    cout << ans << "\n";

	return 0;
}
