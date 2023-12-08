#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
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

const int N = 2e5, M = 2e5, L = 18;

int n, m, t = 0, par[L][2 * N], tin[N], tout[N], ht[N], pfx[N];
ll ans = 0;
simps arr[M];
vector<int> adj[N];
map<simps, int> sharert;
map<threesome, int> mulcnt;

void dfs1(int node, int parent, int height) {
    par[0][node] = parent;
    ht[node] = height;
    tin[node] = t;
    t++;

    for (int i : adj[node]) if (i != parent) dfs1(i, node, height + 1);

    tout[node] = t;
    t++;

    return;
}

bool isanc(int test, int node) {
    return tin[node] > tin[test] and tout[node] < tout[test];
}

int getpar(int node, int k) {
    int cnt = 0;
    while (k) {
        if (k & 1) {
            node = par[cnt][node];
            if (node == -1) return -1;
        }
        k >>= 1;
        cnt++;
    }
    return node;
}

int getlca(int a, int b) {
    if (isanc(a, b)) return a;
    if (isanc(b, a)) return b;
    for (int i = L - 1; i >= 0; i--) if (par[i][a] != -1 and not isanc(par[i][a], b)) a = par[i][a];
    return par[0][a];
}

int dfs2(int node) {
    for (int i : adj[node]) {
        if (i != par[0][node]) pfx[node] += dfs2(i);
    }

    return pfx[node];
}

ll choose2(ll num) {
    return num * (num - 1) / 2;
}

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);

    cin >> n >> m;
    m -= n - 1;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < m; i++) {
        cin >> arr[i].first >> arr[i].second;
        arr[i].first--; arr[i].second--;
    }

    dfs1(0, -1, 0);

    for (int i = 1; (1 << i) <= n; i++) {
        for (int j = 0; j < n; j++) {
            int cur = par[i - 1][j];
            par[i][j] = cur == -1 ? -1 : par[i - 1][cur];
        }
    }

    for (int i = 0; i < m; i++) {
        int a = arr[i].first, b = arr[i].second, l = getlca(a, b), x, y;
        if (a != l) {
            x = getpar(a, ht[a] - ht[l] - 1);
            pfx[a]++;
            pfx[l]--;
            sharert[make_pair(l, x)]++;
        }
        if (b != l) {
            y = getpar(b, ht[b] - ht[l] - 1);
            pfx[b]++;
            pfx[l]--;
            sharert[make_pair(l, y)]++;
        }
        if (a != l and b != l) mulcnt[make_pair(l, make_pair(min(x, y), max(x, y)))]++;
    }

    dfs2(0);

    for (int i = 0; i < m; i++) {
        int a = arr[i].first, b = arr[i].second, l = getlca(a, b);
        if (a != l) {
            int cur = getpar(a, ht[a] - ht[l] - 1);
            ans += pfx[cur] - 1;
        }
        if (b != l) {
            int cur = getpar(b, ht[b] - ht[l] - 1);
            ans += pfx[cur] - 1;
        }
    }

    for (auto& u : sharert) ans -= choose2(u.second);
    for (auto& u : mulcnt) ans -= choose2(u.second);

    cout << ans << "\n";

	return 0;
}
