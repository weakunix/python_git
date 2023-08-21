#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
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

int n;
vector<int> par, mx1, mx2, mxchild, ans;
vector<vector<int>> adj;

int dfs1(int node) {
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        mx2[node] = max(dfs1(i), mx2[node]);
        if (mx2[node] > mx1[node]) {
            swap(mx1[node], mx2[node]);
            mxchild[node] = i;
        }
    }
    return mx1[node] + 1;
}

void dfs2(int node, int mx, int tp) {
    if (tp != -1 and mxchild[par[node]] != node) {
        int cnt = 1;
        for (int i = par[node]; i != par[tp]; i = par[i]) {
            mx = max(mx1[i] + cnt, mx);
            cnt++;
        }
        tp = -1;
    }
    ans[node] = max(mx1[node], mx);
    if (mxchild[node] == -1) return;
    dfs2(mxchild[node], max(mx + 1, mx2[node] + 1), tp == -1 ? node : tp);
    for (int i : adj[node]) {
        if (i == par[node] or i == mxchild[node]) continue;
        dfs2(i, max(mx + 1, mx1[node] + 1), -1);
    }
    return;
}

int main() {
    cin >> n;
    par.resize(n, -1);
    mx1.resize(n);
    mx2.resize(n);
    mxchild.resize(n, -1);
    ans.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(0);
    dfs2(0, 0, -1);
    for (int i : ans) cout << i << " ";
	return 0;
}
