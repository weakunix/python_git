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
vector<vector<int>> ogadj, adj, w;

int dfs(int node) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n - 1) return 2;
    for (int i : adj[node]) {
        if (visited[i] or w[node][i] == 0) continue;
        int cur = dfs(i);
        if (cur != -1) return min(w[node][i], cur);
    }
    stck.pop_back();
    return -1;
}

bool dfs2(int node) {
    stck.push_back(node);
    visited[node] = true;
    if (node == n - 1) return true;
    for (int i : ogadj[node]) {
        if (visited[i] or w[node][i] != 0) continue;
        if (dfs2(i)) return true;
    }
    stck.pop_back();
    return false;
}

int main() {
    cin >> n >> m;
    ogadj.resize(n);
    adj.resize(n);
    w.resize(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ogadj[a].push_back(b);
        if (w[a][b] == 0 and w[b][a] == 0) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        w[a][b] = 1;
    }
    while (true) {
        stck.clear();
        visited.clear(); visited.resize(n);
        int bn = dfs(0);
        if (bn == -1) break;
        for (int i = 0; i < stck.size() - 1; i++) {
            w[stck[i]][stck[i + 1]] -= bn;
            w[stck[i + 1]][stck[i]] += bn;
        }
        ans++;
    }
    cout << ans << "\n";
    for (int i = 0; i < ans; i++) {
        stck.clear();
        visited.clear(); visited.resize(n);
        assert(dfs2(0));
        cout << stck.size() << "\n";
        for (int i = 0; i < stck.size() - 1; i++) {
            w[stck[i]][stck[i + 1]] = -1;
            cout << stck[i] + 1 << " ";
        }
        cout << stck.back() + 1 << "\n";
    }
	return 0;
}
