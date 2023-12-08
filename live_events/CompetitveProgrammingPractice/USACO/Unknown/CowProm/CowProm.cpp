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

const int N = 1e4;

int n, m, ans = 0;
bool vis[N];
vector<int> adj[N], revadj[N], stck;

void dfs1(int node) {
    vis[node] = true;
    for (int i : adj[node]) if (not vis[i]) dfs1(i);
    stck.push_back(node);
    return;
}

int dfs2(int node) {
    int cur = 1;
    vis[node] = false;
    for (int i : revadj[node]) if (vis[i]) cur += dfs2(i);
    return cur;
}

int main() {
    memset(vis, false, sizeof(vis));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        revadj[b].push_back(a);
    }
    
    for (int i = 0; i < n; i++) if (not vis[i]) dfs1(i);
    while (stck.size()) {
        int cur = stck.back();
        stck.pop_back();
        ans += (vis[cur] and dfs2(cur) > 1);
    }
    cout << ans << "\n";

	return 0;
}
