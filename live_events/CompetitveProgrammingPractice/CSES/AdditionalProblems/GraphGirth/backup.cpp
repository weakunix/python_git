#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 2500;

int n, m, ans = 1e9;
bool vis[N];
vector<int> adj[N];

int bfs(int st) {
    memset(vis, false, sizeof(vis));
    vis[st] = true;

    queue<simps> q;
    q.push({0, st});

    while (not q.empty()) {
        int node = q.front().second, dist = q.front().first;
        q.pop();
        for (int i : adj[node]) {
            if (i == st and dist > 1) return dist + 1;
            if (not vis[i]) {
                q.push({dist + 1, i});
                vis[i] = true;
            }
        }
    }

    return 1e9;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) ans = min(bfs(i), ans);
    cout << ans << "\n";

	return 0;
}
