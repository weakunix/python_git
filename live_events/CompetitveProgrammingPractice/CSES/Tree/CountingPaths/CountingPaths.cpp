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

int n, m;
vector<int> par, idx, ord, lg, st, en, ans;
vector<vector<int>> adj;
vector<vector<simps>> sparse = {{}};

void dfs(int node, int ht) {
    idx[node] = sparse[0].size();
    sparse[0].push_back({ht, node});
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        dfs(i, ht + 1);
        sparse[0].push_back({ht, node});
    }
    ord.push_back(node);
    return;
}

int getmin(int a, int b) {
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    return min(sparse[len][a], sparse[len][b - (1 << len) + 1]).second;
}

int main() {
    cin >> n >> m;
    par.resize(n, -1);
    idx.resize(n);
    st.resize(n);
    en.resize(n);
    ans.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, 0);
    lg.resize(sparse[0].size() + 1);
    for (int i = 2; i <= sparse[0].size(); i++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; (1 << i) <= sparse[0].size(); i++) {
        sparse.push_back({});
        for (int j = 0; j + (1 << i) <= sparse[0].size(); j++) sparse[i].push_back(min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]));
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        st[a]++; st[b]++;
        en[getmin(idx[a], idx[b])]++;
    }
    for (int i : ord) {
        ans[i] = st[i] - en[i];
        if (par[i] != -1) st[par[i]] += st[i] -= 2 * en[i];
    }
    for (int i : ans) cout << i << " ";
    cout << "\n";
	return 0;
}
