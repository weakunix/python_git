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
vector<ll> par, sz, sub, ans;
vector<vector<int>> adj;

void dfs1(int node) {
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        dfs1(i);
        sz[node] += sz[i];
        sub[node] += sub[i] + sz[i];
    }
    return;
}

void dfs2(int node, ll sm) {
    ans[node] = sm;
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        dfs2(i, sm + n - 2 * sz[i]);
    }
    return;
}

int main() {
    cin >> n;
    par.resize(n, -1);
    sz.resize(n, 1);
    sub.resize(n);
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
    dfs2(0, sub[0]);
    for (ll i : ans) cout << i << " ";
    cout << "\n";
	return 0;
}
