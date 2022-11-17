#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
vector<int> par, sub;
vector<vector<int>> adj, child;

int dfs(int node, int parent) {
    par[node] = parent;
    for (int i : adj[node]) {
        if (i != parent) {
            int cur = dfs(i, node);
            sub[node] += cur;
            child[node].push_back(cur);
        }
    }
    return sub[node] + 1;
}

bool works(int k) {
    if ((n - 1) % k != 0) return false;
    for (int i = 0; i < n; i++) {
        unordered_map<int, int> found;
        for (int j : child[i]) {
            if (j % k != 0) found[j % k]++;
        }
        if (sub[i] % k != 0) {
            if (found.count(sub[i] % k) == 0) return false;
            found[sub[i] % k]--;
            if (found[sub[i] % k] == 0) found.erase(sub[i] % k);
        }
        while (not found.empty()) {
            int cur = found.begin()->first;
            found[cur]--;
            if (found[cur] == 0) found.erase(cur);
            if (found.count(k - cur) == 0) return false;
            found[k - cur]--;
            if (found[k - cur] == 0) found.erase(k - cur);
        }
    }
    return true;
}

int main() {
    freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);

    cin >> n;
    par.resize(n);
    sub.resize(n);
    adj.resize(n);
    child.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);

    for (int i = 1; i < n; i++) cout << ((works(i)) ? 1 : 0);
    cout << "\n";

	return 0;
}
