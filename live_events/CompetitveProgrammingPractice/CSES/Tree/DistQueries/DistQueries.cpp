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

int n, q;
vector<int> idx, ht, lg;
vector<vector<int>> adj;
vector<vector<int>> sparse = {{}};

void dfs(int node, int par) {
    idx[node] = sparse[0].size();
    sparse[0].push_back(ht[node]);
    for (int i : adj[node]) {
        if (i == par) continue;
        ht[i] = ht[node] + 1;
        dfs(i, node);
        sparse[0].push_back(ht[node]);
    }
    return;
}

int getmin(int a, int b) {
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    return min(sparse[len][a], sparse[len][b - (1 << len) + 1]);
}

int main() {
    cin >> n >> q;
    idx.resize(n);
    ht.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);

    }
    dfs(0, -1);
    lg.resize(sparse[0].size() + 1);
    for (int i = 2; i <= sparse[0].size(); i++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; (1 << i) <= sparse[0].size(); i++) {
        sparse.push_back({});
        for (int j = 0; j + (1 << i) <= sparse[0].size(); j++) sparse[i].push_back(min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]));
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << ht[a] + ht[b] - 2 * getmin(idx[a], idx[b]) << "\n";
    }
	return 0;
}
