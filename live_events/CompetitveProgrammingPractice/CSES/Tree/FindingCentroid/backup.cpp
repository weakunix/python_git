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

int n, mx = 0;
vector<int> par, dep;
vector<vector<int>> adj;

void dfs(int node) {
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        dep[i] = dep[node] + 1;
        dfs(i);
    }
    return;
}

int main() {
    cin >> n;
    par.resize(n, -1);
    dep.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (dep[i] > dep[mx]) mx = i;
    }
    if (dep[mx] <= n / 2) {
        cout << "1\n";
        return 0;
    }
    for (int i = mx; i != 0; i = par[i]) {
        if (dep[mx] - dep[par[i]] > n / 2) {
            cout << i + 1 << "\n";
            return 0;
        }
    }
    assert(false);
	return 0;
}
