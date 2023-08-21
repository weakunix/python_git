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

int n, ans = 0;
vector<vector<int>> adj;

int dfs(int node, int par) {
    int mx1 = 0, mx2 = 0;
    for (int i : adj[node]) {
        if (i == par) continue;
        mx2 = max(dfs(i, node), mx2);
        if (mx2 > mx1) swap(mx1, mx2);
    }
    ans = max(mx1 + mx2, ans);
    return mx1 + 1;
}

int main() {
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    cout << ans << "\n";
	return 0;
}
