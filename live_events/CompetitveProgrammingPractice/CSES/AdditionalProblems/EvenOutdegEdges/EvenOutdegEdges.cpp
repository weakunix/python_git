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

const int N = 1e5 + 1, M = 2e5;

int n, m;
bool ood[N], flip[M], vis[N];;
simps edges[M];
vector<simps> adj[N];

bool dfs(int node, int paredge) {
    bool needflip = ood[node];
    vis[node] = true;

    for (simps s : adj[node]) {
        if (vis[s.first]) continue;

        if (dfs(s.first, s.second)) needflip = not needflip;
    }

    if (needflip) flip[paredge] = not flip[paredge];

    return needflip;
}

int main() {
    memset(ood, false, sizeof(ood));
    memset(flip, false, sizeof(flip));
    memset(vis, false, sizeof(vis));

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ood[a] = not ood[a];
        edges[i] = {a, b};
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    for (int i = 1; i <= n; i++) {
        if (not vis[i]) {
            if (dfs(i, -1)) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (flip[i]) swap(edges[i].first, edges[i].second);
        cout << edges[i].first << " " << edges[i].second << "\n";
    }

	return 0;
}
