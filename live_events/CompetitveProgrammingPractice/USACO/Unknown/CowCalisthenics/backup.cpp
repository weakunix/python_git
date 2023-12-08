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

const int N = 1e5;

int n, k, par[N];
vector<int> adj[N], ord;

void dfs(int node, int parent) {
    par[node] = parent;
    for (int i : adj[node]) if (i != parent) dfs(i, node);
    ord.push_back(node);
    return;
}

bool works(int tar) {
    int cnt = 0;
    bool vis[N];

    memset(vis, false, sizeof(vis));

    for (int i : ord) {
        if (vis[i]) continue;

        if (cnt > k) return false;
    }

    return true;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);
    
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (works(mid)) r = mid;
        else l = mid + 1;
    }

    assert(l == r);
    cout << l << "\n";

	return 0;
}
