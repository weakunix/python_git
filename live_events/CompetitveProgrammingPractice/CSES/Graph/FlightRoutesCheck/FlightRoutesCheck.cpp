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

int n, m, prv = -1;
vector<int> stck;
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

void dfs2(int node) {
    visited[node] = false;
    for (int i : revadj[node]) {
        if (visited[i]) dfs2(i);
    }
    return;
}

int main() {
    cin >> n >> m;
    visited.resize(n);
    adj.resize(n);
    revadj.resize(n);
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
        if (not visited[cur]) continue;
        if (prv != -1) {
            cout << "NO\n" << cur + 1 << " " << prv + 1 << "\n";
            return 0;
        }
        dfs2(cur);
        prv = cur;
    }
    cout << "YES\n";
	return 0;
}
