#include <iostream>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a);
    return;
}

const int N = 1e5, L = 17;

int n, q, k, ht[N], par[L][N], rt, centpar[N], sz[N], dist[N], nxt[N];
bool inf[N], psbl[N], vis[N];
vector<int> adj[N], centadj[N], ord;
map<int, int> best;

//==================================================CMP==================================================//

bool cmp(int a, int b) { //sort by height
    return ht[a] > ht[b];
}

//==================================================INIT + LCA==================================================//

void dfs1(int node, int parent, int height) {
    ht[node] = height;
    par[0][node] = parent;
    for (int i = 1; i < L; i++) par[i][node] = (par[i - 1][node] == -1 ? -1 : par[i - 1][par[i - 1][node]]);
    ord.push_back(node);
    for (int i : adj[node]) if (i != parent) dfs1(i, node, height + 1);
    return;
}

int getpar(int node, int p) {
    int cnt = 0;
    while (p) {
        if (p & 1) node = par[cnt][node];
        p >>= 1;
        cnt++;
    }
    return node;
}

int lca(int a, int b) {
    if (ht[a] < ht[b]) swap(a, b);
    a = getpar(a, ht[a] - ht[b]);
    if (a == b) return a;
    for (int i = L - 1; i >= 0; i--) {
        if (par[i][a] != par[i][b]) {
            a = par[i][a];
            b = par[i][b];
        }
    }
    return par[0][a];
}

int getdist(int a, int b) {
    int l = lca(a, b);
    return ht[a] + ht[b] - 2 * ht[l];
}

//==================================================CENTROID DECOMP==================================================//

int dfs2(int node, int parent) {
    sz[node] = 1;
    for (int i : adj[node]) if (not vis[i] and i != parent) sz[node] += dfs2(i, node);
    return sz[node];
}

int getcent(int node) {
    int cur = dfs2(node, -1), parent = -1;
    bool works = false;
    while (not works) {
        works = true;
        for (int i : adj[node]) {
            if (vis[i] or i == parent) continue;
            if (2 * sz[i] > cur) {
                parent = node;
                node = i;
                works = false;
                break;
            }
        }
    }
    return node;
}

void centdecomp(int node, int parent) {
    node = getcent(node);
    vis[node] = true;
    centpar[node] = parent;
    if (parent == -1) rt = node;
    else centadj[parent].push_back(node);
    
    for (int i : adj[node]) if (not vis[i]) centdecomp(i, node);

    return;
}

//==================================================OPERATION==================================================//

int setclosest(int node) {
    int cur = node;
    while (cur != -1) {
        setmn(dist[cur], getdist(node, cur));
        cur = centpar[cur];
    }
    return node;
}

int getclosest(int node) {
    int cur = node, res = 1e9;
    while (cur != -1) {
        setmn(res, getdist(node, cur) + dist[cur]);
        cur = centpar[cur];
    }
    return res;
}

//==================================================FIND DIST==================================================//


int getlb(int d) {
    auto it = best.lower_bound(d);
    if (it == best.begin()) return -1;
    it--;
    return it->first;
}

int getub(int d) {
    auto it = best.upper_bound(d);
    if (it == best.begin()) return -1;
    it--;
    return it->first;
}

void dfs3(int node, int parent, int depth) {
    if (depth > k) return;
    if (psbl[node] and (not best.count(depth) or ht[best[depth]] > ht[node])) best[depth] = node;
    for (int i : adj[node]) if (not vis[i] and i != parent) dfs3(i, node, depth + 1);
    return;
}

void dfs4(int node, int parent, int depth) {
    if (depth > k) return;
    int cur = getub(k - depth);
    if (cur != -1 and (nxt[node] == -1 or ht[best[cur]] < ht[nxt[node]])) nxt[node] = best[cur];
    for (int i : adj[node]) if (not vis[i] and i != parent) dfs4(i, node, depth + 1);
    return;
}

void dfs5(int node) {
    best.clear();
    vis[node] = true;

    if (psbl[node]) best[0] = node;
    for (int i : adj[node]) if (not vis[i]) dfs3(i, -1, 1);

    vector<int> vals;
    for (auto& u : best) vals.push_back(u.first);
    for (int i : vals) {
        int prv = getlb(i);
        if (prv != -1 and ht[best[prv]] <= ht[best[i]]) best.erase(i);
    }

    int cur = getub(k);
    if (cur != -1 and (nxt[node] == -1 or ht[best[cur]] < ht[nxt[node]])) nxt[node] = best[cur];
    for (int i : adj[node]) if (not vis[i]) dfs4(i, -1, 1);

    for (int i : centadj[node]) dfs5(i);

    return;
}

//==================================================MAIN==================================================//

int main() {
    memset(vis, false, sizeof(vis));

    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        inf[i] = (c == '1');
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(0, -1, 0);
    sort(all(ord), cmp);
    
    centdecomp(0, -1);

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> k;

        memset(psbl, true, sizeof(psbl));
        queue<simps> qu;
        for (int j = 0; j < n; j++) {
            if (not inf[j]) {
                qu.push({j, 0});
                psbl[j] = false;
            }
        }
        while (qu.size()) {
            int node = qu.front().first, d = qu.front().second;
            qu.pop();
            if (d == k) continue;
            for (int j : adj[node]) {
                if (not psbl[j]) continue;
                psbl[j] = false;
                qu.push({j, d + 1});
            }
        }

        memset(nxt, -1, sizeof(nxt));
        memset(vis, false, sizeof(vis));
        dfs5(rt);

        int ans = 0;
        fill(dist, dist + n, 1e9);
        for (int j : ord) {
            if (not inf[j] or getclosest(j) <= k) continue;
            int cur = nxt[j];
            if (cur == -1) {
                ans = -1;
                break;
            }
            ans++;
            setclosest(cur);
        }

        cout << ans << "\n";
    }

	return 0;
}
