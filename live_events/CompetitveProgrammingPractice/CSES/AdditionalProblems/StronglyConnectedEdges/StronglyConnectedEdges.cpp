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

const int N = 1e5 + 1, M = 2e5;

int n, m, par[N];
bool vis[N], used[M];
vector<simps> adj[N], ans;

void dfs(int node, int parent) {
    par[node] = parent;
    vis[node] = true;

    for (simps s : adj[node]) {
        if (not used[s.second] and not vis[s.first]) {
            ans.push_back({s.first, node});
            used[s.second] = true;
            dfs(s.first, node);
        }
    }

    return;
}

int main() {
    memset(vis, false, sizeof(vis));
    memset(used, false, sizeof(used));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
    
    dfs(1, -1);

    for (int i = 1; i <= n; i++) {
        if (not vis[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    queue<int> q;
    q.push(1);
    vis[1] = false;

    while (not q.empty()) {
        int node = q.front();
        q.pop();
        for (simps s : adj[node]) {
            if (not used[s.second]) {
                ans.push_back({node, s.first});
                used[s.second] = true;
                int cur = s.first;
                while (vis[cur]) {
                    vis[cur] = false;
                    q.push(cur);
                    cur = par[cur];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (simps s : ans) cout << s.first << " " << s.second << "\n";

	return 0;
}
