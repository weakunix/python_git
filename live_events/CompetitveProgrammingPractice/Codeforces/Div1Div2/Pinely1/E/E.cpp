#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    int res = 1;
    visited[node] = true;
    for (int i : adj[node]) {
        if (not visited[i]) res += dfs(i, adj, visited);
    }
    return res;
}

void subcase() {
    int n;
    simps best = {1e9, 1e9};
    vector<vector<int>> adj;
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char cur;
            cin >> cur;
            if (cur == '0') continue;
            adj[i].push_back(j);
        }
    }
    vector<bool> visited(n);
    if (dfs(0, adj, visited) == n) {
        cout << "0\n";
        return;
    }
    for (int i = 0; i < n; i++) best = min({(int) adj[i].size(), i}, best);
    cout << best.first + 1 << "\n";
    for (int i : adj[best.second]) cout << i + 1 << " ";
    cout << best.second + 1 << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
