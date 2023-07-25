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
vector<simps> edges;
vector<vector<int>> adj, w;

int dfs(int node) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n - 1) return 1e9;
    for (int i : adj[node]) {
        if (visited[i] or w[node][i] == 0) continue;
        int cur = dfs(i);
        if (cur != -1) return min(w[node][i], cur);
    }
    stck.pop_back();
    return -1;
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    adj.resize(n);
    w.resize(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
        w[a][b]++;
        w[b][a]++;
    }
    while (true) {
        stck.clear();
        visited.clear(); visited.resize(n);
        int bn = dfs(0);
        if (bn == -1) {
            cout << ans << "\n";
            for (simps s : edges) {
                if (visited[s.first] xor visited[s.second]) cout << s.first + 1 << " " << s.second + 1 << "\n";
            }
            return 0;
        }
        assert(stck.size() >= 2);
        for (int i = 0; i < stck.size() - 1; i++) {
            w[stck[i]][stck[i + 1]] -= bn;
            w[stck[i + 1]][stck[i]] += bn;
        }
        ans += bn;
    }
	return 0;
}
