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

ll getans(int rnd) {
    ll ans = 0;
    for (int i = rnd; i < n; i++) {
        ll cnt = 0;
        unordered_set<int> connected;
        for (int j : adj[i]) {
            if (j != par[i]) connected.insert(getroot(j - 1));
        }
        if (i > 0) connected.insert(getroot(i - 1));
        for (int j : connected) cnt -= group[j] + 1;
        ans += cnt * (cnt - 1);
    }
    return ans;
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
        cout << getans(i) << "\n";
        for (int j : adj[i]) {
            if (j == par[i]) continue;
            merge((i == 0) ? adj[i][0] - 1 : i - 1, j - 1);
        }
        group[getroot((i == 0) ? adj[i][0] - 1 : i - 1)]++;
    }
	return 0;
}
