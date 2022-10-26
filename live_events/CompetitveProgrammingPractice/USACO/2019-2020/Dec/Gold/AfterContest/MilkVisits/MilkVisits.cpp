#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

int n, m;
string ans;
vector<int> t, idx, d;
vector<vector<int>> adj, sparse, pathstck;
vector<vector<threesome>> q;

int lg(int x) {
    return log(x) / log(2);
}

void dfslca(int node, int parent, int depth) {
    idx[node] = d.size();
    d.push_back(depth);
    for (int i : adj[node]) {
        if (i != parent) {
            dfslca(i, node, depth + 1);
            d.push_back(depth);
        }
    }
    return;
}

void genlca() {
    dfslca(0, -1, 0);
    sparse.push_back({});
    for (int i = 0; i < d.size(); i++) sparse[0].push_back(d[i]);
    for (int i = 1; 1 << i <= d.size(); i++) {
        sparse.push_back({});
        for (int j = 0; j + (1 << i) <= d.size(); j++) sparse[i].push_back(min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]));
    }
    return;
}

int lca(int a, int b) {
    a = idx[a];
    b = idx[b];
    if (a > b) swap(a, b);
    int len = lg(b - a + 1);
    return min(sparse[len][a], sparse[len][b - (1 << len) + 1]);
}

void dfs(int node, int parent, int depth) {
    pathstck[t[node]].push_back(depth);
    for (const threesome& ts : q[node]) {
        if (pathstck[ts.sec].empty()) continue;
        if (lca(node, ts.first) <= pathstck[ts.sec].back()) ans[ts.third] = '1';
    }
    for (int i : adj[node]) {
        if (i != parent) dfs(i, node, depth + 1);
    }
    pathstck[t[node]].pop_back();
    return;
}

int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    cin >> n >> m;
    ans.resize(m, '0');
    t.resize(n);
    idx.resize(n);
    adj.resize(n);
    pathstck.resize(n);
    q.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        t[i]--;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        c--;
        q[a].push_back({b, {c, i}});
        q[b].push_back({a, {c, i}});
    }

    genlca();

    dfs(0, -1, 0);

    cout << ans << "\n";

	return 0;
}
