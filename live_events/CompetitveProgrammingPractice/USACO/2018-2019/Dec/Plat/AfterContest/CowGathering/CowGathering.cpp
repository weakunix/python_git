#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <map>
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

const int N = 1e5, L = 17;

int n, m, par[L][N], ht[N], indeg[N], cnt = 0, notpsbl[N], ans[N];
vector<int> adj[N], req[N];

void dfs1(int node, int parent, int height) {
    par[0][node] = parent;
    ht[node] = height;
    for (int i : adj[node]) if (i != parent) dfs1(i, node, height + 1);
    return;
}

int getpar(int node, int k) {
    int cnt = 0;
    while (k) {
        if (k & 1) node = par[cnt][node];
        k >>= 1;
        cnt++;
    }
    return node;
}

void dfs2(int node, int curcnt) {
    curcnt += notpsbl[node];
    ans[node] = (curcnt == 0 ? 1 : 0);
    for (int i : adj[node]) if (i != par[0][node]) dfs2(i, curcnt);
    return;
}

int main() {
    freopen("gathering.in", "r", stdin);
    freopen("gathering.out", "w", stdout);

    memset(indeg, 0, sizeof(indeg));
    memset(notpsbl, 0, sizeof(notpsbl));

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        req[a].push_back(b);
        indeg[b]++;
    }

    dfs1(0, -1, 0);
    for (int i = 1; i < L; i++) {
        for (int j = 0; j < n; j++) {
            int cur = par[i - 1][j];
            if (cur != -1) cur = par[i - 1][cur];
            par[i][j] = cur;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        cnt++;
        for (int i : req[cur]) {
            indeg[i]--;
            if (indeg[i] == 0) q.push(i);
        }
    }

    if (cnt != n) {
        for (int i = 0; i < n; i++) cout << "0\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j : req[i]) {
            int cur = ht[j] - ht[i];
            if (cur > 0 and getpar(j, cur) == i) {
                notpsbl[0]++;
                notpsbl[getpar(j, cur - 1)]--;
            }
            else notpsbl[i]++;
        }
    }

    dfs2(0, 0);
    for (int i = 0; i < n; i++) cout << ans[i] << "\n";

	return 0;
}
