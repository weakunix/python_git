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

const int N = 1e5 + 5, C = 5;
const ll MX = 1e15;

int n, d[N], c[N];
ll dp[2][N], cost[C * N];
vector<int> adj[N];

void dfs(int node, int parent, int parc) {
    for (int i : adj[node]) {
        if (i == parent) continue;
        dfs(i, node, c[node]);
    }

    fill(cost, cost + C * N, MX);
    cost[0] = 0;

    ll req = 0;

    for (int i : adj[node]) {
        if (i == parent) continue;

        req += dp[1][i];
        
        for (int j = C * n; j >= 0; j--) setmn(cost[j + c[i]], cost[j] + dp[0][i] - dp[1][i]);
    }

    for (int i = 0; i <= C * n; i++) setmn(dp[0][node], req + cost[i] + max(d[node] - i, 0));
    for (int i = 0; i <= C * n; i++) setmn(dp[1][node], req + cost[i] + max(d[node] - parc - i, 0));

    return;
}

void dfsspec(int node, int parent, int parc) {
    ll req = 0, free = 0;

    for (int i : adj[node]) {
        if (i == parent) continue;
        dfsspec(i, node, c[node]);
        req += dp[1][i];
        if (dp[0][i] == dp[1][i]) free += c[i];
    }

    dp[0][node] = req + max(d[node] - free, 0ll);
    dp[1][node] = req + max(d[node] - parc - free, 0ll);

    return;
}

int main() {
    fill(dp[0], dp[0] + N, MX);
    fill(dp[1], dp[1] + N, MX);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> d[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    if (n > 2000) dfsspec(0, -1, 0);
    else dfs(0, -1, 0);

    cout << dp[0][0] << "\n";

	return 0;
}
