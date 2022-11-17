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
vector<int> par, ord;
vector<vector<int>> adj;

void dfs(int node, int parent) {
    par[node] = parent;
    for (int i : adj[node]) {
        if (i != parent) dfs(i, node);
    }
    ord.push_back(node);
    return;
}

bool works(int k) {
    if ((n - 1) % k != 0) return false;
    vector<unordered_map<int, int>> dp(n);
    for (int i : ord) {
        if (i == 0) return dp[i].empty();
        if (dp[i].size() > 1) return false;
        int cur = 1;
        if (not dp[i].empty()) {
            auto it = dp[i].begin();
            if (it->second > 1) return false;
            cur = it->first + 1;
        }
        assert(cur <= k);
        if (cur == k) continue;
        if (dp[par[i]].count(k - cur) > 0) {
            dp[par[i]][k - cur]--;
            if (dp[par[i]][k - cur] == 0) dp[par[i]].erase(k - cur);
        }
        else dp[par[i]][cur]++;
    }
    assert(false);
    return false;
}

int main() {
    freopen("deleg.in", "r", stdin);
	//freopen("deleg.out", "w", stdout);

    cin >> n;
    par.resize(n, -1);
    adj.resize(n);
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
