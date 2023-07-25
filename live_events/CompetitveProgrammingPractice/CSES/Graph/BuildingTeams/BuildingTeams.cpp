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
vector<int> visited;
vector<vector<int>> adj;

bool dfs(int node, int group) {
    visited[node] = group;
    for (int i : adj[node]) {
        if (visited[i]) {
            if (visited[i] == group) return false;
        }
        else {
            if (not dfs(i, 3 ^ group)) return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    visited.resize(n);
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (visited[i] != 0) continue;
        if (not dfs(i, 1)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for (int i : visited) cout << i << " ";
    cout << "\n";
	return 0;
}
