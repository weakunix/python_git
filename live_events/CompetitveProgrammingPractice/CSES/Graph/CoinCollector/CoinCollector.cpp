#include <iostream>
#include <cstring>
#include <vector>
#include <set>
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

int n, m, cnt = 0;
ll ans = 0;
vector<int> coin, scc, stck, ord;
vector<ll> scccoin, dp;
vector<bool> visited, sccvisited;
vector<vector<int>> adj, revadj;
vector<set<int>> sccadj;

void dfs1(int node) {
    visited[node] = true;
    for (int i : adj[node]) {
        if (not visited[i]) dfs1(i);
    }
    stck.push_back(node);
    return;
}

void dfs2(int node) {
    scc[node] = cnt;
    scccoin.back() += coin[node];
    for (int i : revadj[node]) {
        if (scc[i] == -1) dfs2(i);
    }
    return;
}

void dfs3(int node) {
    sccvisited[node] = true;
    for (int i : sccadj[node]) {
        if (not sccvisited[i]) dfs3(i);
    }
    ord.push_back(node);
    return;
}

int main() {
    cin >> n >> m;
    coin.resize(n);
    scc.resize(n, -1);
    visited.resize(n);
    adj.resize(n);
    revadj.resize(n);
    for (int& i : coin) cin >> i;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        revadj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (not visited[i]) dfs1(i);
    }
    for (int i = n - 1; i >= 0; i--) {
        int cur = stck[i];
        if (scc[cur] != -1) continue;
        scccoin.push_back(0);
        dfs2(cur);
        cnt++;
    }
    dp.resize(cnt);
    sccvisited.resize(cnt);
    sccadj.resize(cnt);
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (scc[i] != scc[j]) sccadj[scc[i]].insert(scc[j]);
        }
    }
    for (int i = 0; i < cnt; i++) {
        if (not sccvisited[i]) dfs3(i);
    }
    for (int i : ord) {
        for (int j : sccadj[i]) dp[i] = max(dp[j], dp[i]);
        dp[i] += scccoin[i];
        ans = max(dp[i], ans);
    }
    cout << ans << "\n";
	return 0;
}
