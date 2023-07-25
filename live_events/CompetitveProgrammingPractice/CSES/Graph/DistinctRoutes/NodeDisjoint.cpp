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

int n, m, ans = 0;
vector<int> stck;
vector<bool> visited;
vector<vector<int>> adj;
vector<vector<bool>> w;

bool dfs(int node) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n - 1) return true;
    for (int i : adj[node]) {
        if (visited[i] or not w[node][i]) continue;
        if (dfs(i)) return true;
    }
    stck.pop_back();
    return false;
}

bool dfs2(int node) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n - 1) return true;
    for (int i : adj[node]) {
        if (visited[i] or not w[i][node]) continue;
        if (dfs2(i)) return true;
    }
    stck.pop_back();
    return false;
}

int main() {
    cin >> n >> m;
    adj.resize(n + n - 2);
    w.resize(n + n - 2, vector<bool>(n + n - 2));
    for (int i = 1; i < n - 1; i++) {
        adj[i].push_back(i + n - 1);
        adj[i + n - 1].push_back(i);
        w[i][i + n - 1] = true;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (a == n - 1 or b == 0) continue;
        if (a != 0) a += n - 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
        w[a][b] = true;
    }
    while (true) {
        stck.clear();
        visited.clear(); visited.resize(n + n - 2);
        if (not dfs(0)) {
            break;
        }
        assert(stck.size() >= 2);
        for (int i = 0; i < stck.size() - 1; i++) {
            w[stck[i]][stck[i + 1]] = false;
            w[stck[i + 1]][stck[i]] = true;
        }
        ans++;
    }
    cout << ans << "\n";
    for (int i = 0; i < ans; i++) {
        vector<int> curans;
        stck.clear();
        visited.clear(); visited.resize(n + n - 2);
        assert(dfs2(0));
        for (int i = 0; i < stck.size(); i++) {
            if (i < stck.size() - 1) w[stck[i + 1]][stck[i]] = false;
            if (stck[i] >= n) continue;
            curans.push_back(stck[i] + 1);
        }
        cout << curans.size() << "\n";
        for (int j : curans) cout << j << " ";
        cout << "\n";
    }
	return 0;
}
