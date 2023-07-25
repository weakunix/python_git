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

int n, m, k, ans = 0;
vector<int> stck;
vector<bool> visited;
vector<vector<int>> adj;
vector<vector<bool>> w;

bool dfs(int node) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n + m + 1) return true;
    for (int i : adj[node]) {
        if (visited[i] or not w[node][i]) continue;
        if (dfs(i)) return true;
    }
    stck.pop_back();
    return false;
}

int main() {
    cin >> n >> m >> k;
    adj.resize(n + m + 2);
    w.resize(n + m + 2, vector<bool>(n + m + 2));
    for (int i = 1; i <= n; i++) {
        adj[0].push_back(i);
        adj[i].push_back(0);
        w[0][i] = true;
    }
    for (int i = n + 1; i <= n + m; i++) {
        adj[i].push_back(n + m + 1);
        adj[n + m + 1].push_back(i);
        w[i][n + m + 1] = true;
    }
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        b += n;
        if (w[a][b]) continue;
        adj[a].push_back(b);
        adj[b].push_back(a);
        w[a][b] = true;
    }
    while (true) {
        stck.clear();
        visited.clear(); visited.resize(n + m + 2);
        if (not dfs(0)) {
            cout << ans << "\n";
            for (int i = 1; i <= n; i++) {
                for (int j = n + 1; j <= n + m; j++) {
                    if (w[j][i]) cout << i << " " << j - n << "\n";
                }
            }
            return 0;
        }
        assert(stck.size() >= 2);
        for (int i = 0; i < stck.size() - 1; i++) {
            w[stck[i]][stck[i + 1]] = false;
            w[stck[i + 1]][stck[i]] = true;
        }
        ans++;
    }
	return 0;
}
