#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 3e5, L = 20;
int lg[2 * N + 1];

int n, m, q, k, scnt = 0, sid[N], sz[N], indeg[N], rt, par[N], path[N], dep[N], sparse[L][2 * N], etidx[N], cntr = 0;
bool vis[N];
vector<int> adj[N], revadj[N], stck, child[N];
set<int> sadj[N];

void dfs1(int node) {
    vis[node] = true;
    for (int i : adj[node]) if (not vis[i]) dfs1(i);
    stck.pb(node);
    return;
}

void dfs2(int node) {
    sid[node] = scnt;
    sz[scnt]++;
    vis[node] = false;
    for (int i : revadj[node]) if (vis[i]) dfs2(i);
    return;
}

void dfs3(int node, int cnt, int depth) {
    cnt += sz[node];
    path[node] = cnt;
    dep[node] = depth;
    sparse[0][cntr] = node;
    etidx[node] = cntr;
    cntr++;
    for (int i : child[node]) {
        dfs3(i, cnt, depth + 1);
        sparse[0][cntr] = node;
        cntr++;
    }
    return;
}

int getlca(int u, int v) {
    if (u == -1 or v == -1) return -1;
    u = etidx[u]; v = etidx[v];
    if (u > v) swap(u, v);
    int len = lg[v - u + 1], l = sparse[len][u], r = sparse[len][v - (1 << len) + 1];
    return (dep[l] < dep[r] ? l : r);
}

void remdup(int& a, int& b) {
    if (a == -1 or b == -1) return;
    int l = getlca(a, b);
    if (a == l) b = -1;
    else if (b == l) a = -1;
    return;
}

int main() {
    lg[1] = 0;
    for (int i = 2; i <= 2 * N; i++) lg[i] = lg[i / 2] + 1;

    clr(sz, 0);
    clr(indeg, 0);
    clr(path, 0);
    clr(vis, false);

    cin >> n >> m >> q >> k;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        revadj[v].pb(u);
    }

    for (int i = 0; i < n; i++) if (not vis[i]) dfs1(i);
    while (stck.size()) {
        int node = stck.back();
        stck.bp();
        if (not vis[node]) continue;
        dfs2(node);
        scnt++;
    }

    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (sid[i] == sid[j] or sadj[sid[i]].count(sid[j])) continue;
            sadj[sid[i]].insert(sid[j]);
            indeg[sid[j]]++;
        }
    }

    for (int i = 0; i < scnt; i++) {
        if (indeg[i]) continue;
        rt = i;
        break;
    }

    queue<int> qu;
    qu.push(rt);
    par[rt] = -1;
    while (qu.size()) {
        int node = qu.front();
        qu.pop();
        for (int i : sadj[node]) {
            indeg[i]--;
            if (indeg[i]) continue;
            qu.push(i);
            child[node].pb(i);
            par[i] = node;
        }
    }

    dfs3(rt, 0, 0);

    for (int i = 1; (1 << i) <= cntr; i++) {
        for (int j = 0; j + (1 << i) <= cntr; j++) {
            int l = sparse[i - 1][j], r = sparse[i - 1][j + (1 << (i - 1))];
            if (dep[l] > dep[r]) swap(l, r);
            sparse[i][j] = l;
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v, a = -1, b = -1, c = -1, d = -1;
        cin >> u >> v;
        u--; v--;
        u = sid[u]; v = sid[v];

        if (k) {
            cin >> a >> b;
            a--; b--;
            a = sid[a]; b = sid[b];
        }
        if (k == 2) {
            cin >> c >> d;
            c--; d--;
            c = sid[c]; d = sid[d];
        }

        int s[3] = {u, -1, -1};
        if (a != -1 and getlca(u, a) == u) s[1] = b;
        if (c != -1 and (getlca(u, c) == u or (s[1] != -1 and getlca(s[1], c) == s[1]))) s[2] = d;
        if (a != -1 and (getlca(u, a) == u or (s[2] != -1 and getlca(s[2], a) == s[2]))) s[1] = b;

        for (int j = 0; j < 3; j++) remdup(s[j], s[(j + 1) % 3]);

        int p[3] = {v, -1, -1};
        if (b != -1 and getlca(v, b) == b) p[1] = a;
        if (d != -1 and (getlca(v, d) == d or (p[1] != -1 and getlca(p[1], d) == d))) p[2] = c;
        if (b != -1 and (getlca(v, b) == b or (p[2] != -1 and getlca(p[2], b) == b))) p[1] = a;

        int res = 0;
        for (int i = 1; i < 8; i++) {
            int node = -1;
            bool add = (__builtin_popcount(i) % 2 == 1);
            for (int j = 0; j < 3; j++) {
                if (not (i & (1 << j))) continue;
                if (node == -1) node = p[j];
                else node = getlca(node, p[j]);
            }
            if (node == -1) continue;
            for (int j = 0; j < 3; j++) {
                if (s[j] == -1 or getlca(s[j], node) != s[j]) continue;
                res += (add ? 1 : -1) * (path[node] - (s[j] == rt ? 0 : path[par[s[j]]]));
            }
        }
        cout << res << "\n";
    }

	return 0;
}
