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

const int N = 2e5, modval = 1e9 + 7;

int n, m, cnt = 0, ans = 1;
bool vis[N];
vector<int> adj[N];

void dfs(int node) {
    vis[node] = true;
    for (int i : adj[node]) if (not vis[i]) dfs(i);
    return;
}

int main() {
    memset(vis, false, sizeof(vis));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (not vis[i]) {
            dfs(i);
            cnt++;
        }
    }

    for (int i = 0; i < m - n + cnt; i++) ans = 2 * ans % modval;
    cout << ans << "\n";

	return 0;
}
