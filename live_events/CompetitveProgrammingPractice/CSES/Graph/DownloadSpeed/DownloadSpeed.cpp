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

int n, m;
ll mx = 0, ans = 0;
vector<vector<ll>> adj, w;

ll dfs(int node, vector<int>& stck, vector<bool>& visited) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n - 1) return 1e18;
    for (int i : adj[node]) {
        if (visited[i] or w[node][i] < mx) continue;
        ll cur = dfs(i, stck, visited);
        if (cur != -1) return min(w[node][i], cur);
    }
    stck.pop_back();
    return -1;
}

int main() {
    cin >> n >> m;
    adj.resize(n);
    w.resize(n, vector<ll>(n));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        if (w[a][b] == 0 and w[b][a] == 0) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        w[a][b] += c;
        mx = max(w[a][b], mx);
    }
    while (mx > 0) {
        while (true) {
            vector<int> stck;
            vector<bool> visited(n);
            ll bn = dfs(0, stck, visited);
            if (bn == -1) break;
            assert(stck.size() >= 2);
            for (int i = 0; i < stck.size() - 1; i++) {
                w[stck[i]][stck[i + 1]] -= bn;
                w[stck[i + 1]][stck[i]] += bn;
            }
            ans += bn;
        }
        mx /= 2;
    }
    cout << ans << "\n";
	return 0;
}
