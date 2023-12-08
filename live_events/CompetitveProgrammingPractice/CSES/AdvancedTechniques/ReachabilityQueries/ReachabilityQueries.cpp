#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <bitset>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 5e4;

int n, m, q, cnt = 0, par[N], outdeg[N];
bool vis[N];
vector<int> adj[N], revadj[N], stck;
queue<int> qu;
set<int> ccadj[N], ccrevadj[N];
bitset<N> reach[N];

void dfs1(int node) {
    vis[node] = true;
    for (int i : adj[node]) if (not vis[i]) dfs1(i);
    stck.push_back(node);
    return;
}

void dfs2(int node, int id) {
    vis[node] = false;
    par[node] = id;
    for (int i : revadj[node]) if (vis[i]) dfs2(i, id);
    return;
}

int main() {
    memset(vis, false, sizeof(vis));

    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        revadj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) if (not vis[i]) dfs1(i);
    for (int i = n - 1; i >= 0; i--) {
        if (not vis[stck[i]]) continue;
        dfs2(stck[i], cnt);
        cnt++;
    }

    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (par[i] != par[j]) {
                ccadj[par[i]].insert(par[j]);
                ccrevadj[par[j]].insert(par[i]);
            }
        }
    }

    for (int i = 0; i < cnt; i++) {
        reach[i].set(i);
        if (ccadj[i].empty()) qu.push(i);
    }

    while (qu.size()) {
        int node = qu.front();
        qu.pop();
        for (int i : ccrevadj[node]) {
            ccadj[i].erase(node);
            reach[i] |= reach[node];
            if (ccadj[i].empty()) qu.push(i);
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (reach[par[a]][par[b]] ? "YES\n" : "NO\n");
    }

	return 0;
}
