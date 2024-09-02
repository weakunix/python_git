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

const int N = 602;

int n, val[N], indeg[N], w[N][N], lev[N], ans = 0;
bool vis[N];
vector<int> adj[N], dadj[N];

void inpt() {
    int r, c;
    cin >> r >> c;
    n = r * c;
    for (int i = 0; i < n; i++) {
        cin >> val[i];

        if (i % c) {
            adj[i].pb(i - 1);
            indeg[i - 1]++;
        }

        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int a, b;
            cin >> a >> b;
            adj[i].pb(a * c + b);
            indeg[a * c + b]++;
        }
    }
    return;
}

int dfs(int node, int flow) {
    if (node == n + 1) return flow;

    for (int i : dadj[node]) {
        if (vis[i]) continue;
        if (lev[i] != lev[node] + 1) continue;
        if (not w[node][i]) continue;

        int cur = dfs(i, min(flow, w[node][i]));
        if (cur == 0) continue;

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
    q.push(n);
    lev[n] = 0;

    while (q.size()) {
        int node = q.front();
        q.pop();
        for (int i : dadj[node]) {
            if (lev[i] != -1 or not w[node][i]) continue;
            lev[i] = lev[node] + 1;
            q.push(i);
        }
    }

    int res = 0;
    while (true) {
        int cur = dfs(n, 1e9);
        if (not cur) break;
        res += cur;
    }

    return res;
}

int main() {
    clr(indeg, 0);

    inpt();

    queue<int> q;
    for (int i = 0; i < n; i++) if (not indeg[i]) q.push(i);

    while (q.size()) {
        int node = q.front();
        q.pop();
        for (int i : adj[node]) {
            indeg[i]--;
            if (not indeg[i]) q.push(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (indeg[i]) continue;

        if (val[i] >= 0) {
            w[n][i] = val[i];
            w[i][n] = 0;
            dadj[n].pb(i);
            dadj[i].pb(n);
            ans += val[i];
        }
        else {
            w[n + 1][i] = 0;
            w[i][n + 1] = -val[i];
            dadj[n + 1].pb(i);
            dadj[i].pb(n + 1);
        }

        for (int j : adj[i]) {
            if (indeg[j]) continue;
            dadj[i].pb(j);
            dadj[j].pb(i);
            w[i][j] = 0;
            w[j][i] = 1e9;
        }
    }

    while (true) {
        int cur = dinic();
        if (not cur) break;
        ans -= cur;
    }

    cout << ans << "\n";

	return 0;
}
