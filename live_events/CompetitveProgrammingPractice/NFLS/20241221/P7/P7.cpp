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

const int N = 3001;

int n, k, sz[N];
ll dp[N][N][3], cur[N][3], ans = 1e9;
vector<simps> adj[N];

void dfs(int node, int parent) {
    sz[node] = 1;

    for (simps s : adj[node]) {
        int nxt = s.first, w = s.second;
        if (nxt == parent) continue;

        dfs(nxt, node);

        memcpy(cur, dp[node], sizeof(cur));

        for (int j = 0; j <= sz[node]; j++) {
            for (int l = 0; l <= sz[nxt] and j + l <= k; l++) {
                for (int p = 0; p <= 2; p++) {
                    for (int q = 0; p + q <= 2; q++) {
                        setmn(dp[node][j + l][p + q], cur[j][p] + dp[nxt][l][q] + (1 + (q != 1)) * w);
                    }
                }
            }
        }

        sz[node] += sz[nxt];
    }

    setmn(ans, dp[node][k][2]);

    return;
}

int main() {
    clr(dp, 0);
    for (int i = 0; i < N; i++) for (int j = 2; j < N; j++) fill(dp[i][j], dp[i][j] + 3, 1e9);

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    dfs(0, -1);

    cout << ans << "\n";

	return 0;
}
