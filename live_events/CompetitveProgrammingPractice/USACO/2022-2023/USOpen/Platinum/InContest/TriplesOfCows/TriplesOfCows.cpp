#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
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
ll ans = 0;
vector<int> par, group;
vector<vector<int>> adj;

void dfs(int node) {
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        dfs(i);
    }
    return;
}

int getroot(int node) {
    if (group[node] < 0) return node;
    group[node] = getroot(group[node]);
    return group[node];
}

void merge(int a, int b) {
    a = getroot(a), b = getroot(b);
    if (a == b) return;
    if (group[a] < group[b]) swap(a, b);
    group[b] += group[a] + 1;
    group[a] = b;
    return;
}

int main() {
    cin >> n;
    par.resize(n, -1);
    group.resize(n - 1, -2); //group[x - 1] = (x, par[x]) initially
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0);
    for (int i = 0; i < n; i++) {
        ll cur = adj[i].size();
        ans += cur * (cur - 1);
    }
    cout << ans << "\n";
    for (int i = 0; i < n - 1; i++) {
        int cur = (i == 0) ? adj[i][0] - 1 : i - 1;
        for (int j : adj[i]) {
            if (j == par[i]) continue;
            merge(cur, j - 1);
        }
        group[cur]++;
        cout << ans << "\n";
    }
	return 0;
}
