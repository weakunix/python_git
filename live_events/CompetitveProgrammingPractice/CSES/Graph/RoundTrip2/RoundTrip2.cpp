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

int n, m, cnt = 0;
vector<int> scc, stck, ans;
vector<bool> visited;
vector<vector<int>> adj, revadj;

void dfs1(int node) {
    visited[node] = true;
    for (int i : adj[node]) {
        if (not visited[i]) dfs1(i);
    }
    stck.push_back(node);
    return;
}

int dfs2(int node) {
    int sz = 1;
    visited[node] = false;
    scc[node] = cnt;
    for (int i : revadj[node]) {
        if (visited[i]) sz += dfs2(i);
    }
    return sz;
}

bool dfs3(int node, int tar) {
    scc[node] = -1;
    ans.push_back(node);
    for (int i : adj[node]) {
        if (i == tar) {
            ans.push_back(i);
            return true;
        }
        if (scc[i] == cnt and dfs3(i, tar)) return true;
    }
    ans.pop_back();
    return false;
}

int main() {
    cin >> n >> m;
    scc.resize(n, -1);
    visited.resize(n);
    adj.resize(n);
    revadj.resize(n);
    for (int i = 0; i < n; i++) scc.push_back(i);
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
        if (not visited[stck[i]]) continue;
        if (dfs2(stck[i]) == 1) {
            cnt++;
            continue;
        }
        assert(dfs3(stck[i], stck[i]));
        cout << ans.size() << "\n";
        for (int i : ans) cout << i + 1 << " ";
        cout << "\n";
        return 0;
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
