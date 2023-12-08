#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
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

int n, m, sid[N], cnt = 0, sz[N], bestto[N], bestfrom[N], ans = 0;
bool vis[N];
vector<int> adj[N], revadj[N], stck;

void dfs1(int node) {
    vis[node] = true;
    for (int i : adj[node]) if (not vis[i]) dfs1(i);
    stck.push_back(node);
    return;
}

void dfs2(int node) {
    vis[node] = false;
    sid[node] = cnt;
    sz[cnt]++;
    for (int i : revadj[node]) if (vis[i]) dfs2(i);
    return;
}

void genbest(int (&curbest)[N], vector<int> (&curadj)[N]) {
    int indeg[N];
    queue<int> q;
    set<int> sadj[N];

    memset(indeg, 0, sizeof(indeg));
    fill(curbest, curbest + cnt, -1e9);
    curbest[sid[0]] = 0;

    for (int i = 0; i < n; i++) {
        for (int j : curadj[i]) {
            if (sid[i] != sid[j] and not sadj[sid[i]].count(sid[j])) {
                sadj[sid[i]].insert(sid[j]);
                indeg[sid[j]]++;
            }
        }
    }

    for (int i = 0; i < cnt; i++) if (not indeg[i]) q.push(i);

    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i : sadj[cur]) {
            curbest[i] = max(curbest[cur] + sz[i], curbest[i]);
            indeg[i]--;
            if (indeg[i] == 0) q.push(i);
        }
    }

    return;
}

int main() {
    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);

    memset(sz, 0, sizeof(sz));
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
        if (vis[cur]) {
            dfs2(cur);
            cnt++;
        }
    }

    genbest(bestto, adj);
    genbest(bestfrom, revadj);

    for (int i = 0; i < n; i++) for (int j : revadj[i]) ans = max(bestto[sid[i]] + bestfrom[sid[j]], ans);
    cout << ans + sz[sid[0]] << "\n";

	return 0;
}
