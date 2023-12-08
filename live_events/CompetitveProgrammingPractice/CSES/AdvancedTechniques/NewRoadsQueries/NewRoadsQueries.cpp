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

const int N = 2e5, L = 18;

int n, m, q, dsu[N], ht[N];
simps par[L][N];
vector<simps> adj[N];

int getdsu(int node) {
    if (dsu[node] < 0) return node;
    dsu[node] = getdsu(dsu[node]);
    return dsu[node];
}

bool merge(int a, int b) {
    a = getdsu(a); b = getdsu(b);
    if (a == b) return false;
    if (dsu[a] < dsu[b]) swap(a, b);
    dsu[b] += dsu[a];
    dsu[a] = b;
    return true;
}

void dfs(int node, int height) {
    ht[node] = height;
    for (simps s : adj[node]) {
        if (ht[s.first] != -1) continue;
        par[0][s.first] = {node, s.second};
        dfs(s.first, height + 1);
    }
    return;
}

int calc(int a, int b) {
    int res = 0;

    if (ht[a] < ht[b]) swap(a, b);

    int dist = ht[a] - ht[b], cur = 0;
    while (dist) {
        if (dist & 1) {
            res = max(par[cur][a].second, res);
            a = par[cur][a].first;
        }
        dist >>= 1;
        cur++;
    }

    if (a == b) return res;

    for (int i = L - 1; i >= 0; i--) {
        if (par[i][a].first == par[i][b].first) continue;
        res = max({par[i][a].second, par[i][b].second, res});
        a = par[i][a].first;
        b = par[i][b].first;
    }

    return max({par[0][a].second, par[0][b].second, res});
}

int main() {
    memset(dsu, -1, sizeof(dsu));
    memset(ht, -1, sizeof(ht));

    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (merge(a, b)) {
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        }
    }

    for (int i = 0; i < n; i++) {
        if (ht[i] == -1) {
            par[0][i] = {-1, 0};
            dfs(i, 0);
        }
    }

    for (int i = 1; i < L; i++) {
        for (int j = 0; j < n; j++) {
            if (par[i - 1][j].first == -1) {
                par[i][j] = {-1, 0};
                continue;
            }
            par[i][j] = {par[i - 1][par[i - 1][j].first].first, max(par[i - 1][j].second, par[i - 1][par[i - 1][j].first].second)};
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (getdsu(a) != getdsu(b) ? -1 : calc(a, b)) << "\n";
    }

	return 0;
}
