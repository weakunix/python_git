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

const int N = 5000, M = 50000, S = N + M + 2, C = 100;

int n, m, ans = 0, lev[S];
bool vis[S];
vector<int> adj[S];
map<int, int> w[S];

int dfs(int node, int flow) {
    if (node == n + m + 1) return flow;

    for (int i : adj[node]) {
        if (vis[i]) continue;
        if (lev[i] != lev[node] + 1) continue;
        if (not w[node][i]) continue;

        int cur = dfs(i, min(flow, w[node][i]));
        if (not cur) continue;

        w[node][i] -= cur;
        w[i][node] += cur;
        return cur;
    }

    vis[node] = true;

    return 0;
}

int dinic() {
    clr(lev, -1);
    clr(vis, false);
    
    queue<int> q;
    q.push(0);
    lev[0] = 0;

    while (q.size()) {
        int node = q.front();
        q.pop();
        for (int i : adj[node]) {
            if (lev[i] != -1 or not w[node][i]) continue;
            lev[i] = lev[node] + 1;
            q.push(i);
        }
    }

    int res = 0;
    while (true) {
        int cur = dfs(0, C);
        if (not cur) break;
        res += cur;
    }

    return res;
}

int main() {
    cin >> n >> m;
    for (int i = m + 1; i <= m + n; i++) {
        int c;
        cin >> c;

        adj[i].pb(n + m + 1);
        adj[n + m + 1].pb(i);
        w[i][n + m + 1] = c;
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a += m; b += m;
        ans += c;

        adj[i].pb(0);
        adj[0].pb(i);
        w[0][i] = c;

        adj[i].pb(a);
        adj[a].pb(i);
        w[i][a] = C;

        adj[i].pb(b);
        adj[b].pb(i);
        w[i][b] = C;
    }

    while (true) {
        int cur = dinic();
        if (not cur) break;
        ans -= cur;
    }

    cout << ans << "\n";

	return 0;
}
