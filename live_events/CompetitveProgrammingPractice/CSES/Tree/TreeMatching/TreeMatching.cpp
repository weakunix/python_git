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

int n;
vector<int> dp1, dp2;
vector<vector<int>> adj;

void dfs(int node, int par) {
    for (int i : adj[node]) {
        if (i == par) continue;
        dfs(i, node);
        dp2[node] += max(dp1[i], dp2[i]);
    }
    for (int i : adj[node]) {
        if (i == par) continue;
        dp1[node] = max(dp2[node] + dp2[i] + 1 - max(dp1[i], dp2[i]), dp1[node]);
    }
    return;
}

int main() {
    cin >> n;
    dp1.resize(n);
    dp2.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    cout << max(dp1[0], dp2[0]) << "\n";
	return 0;
}
