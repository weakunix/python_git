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

const int N = 1e5 + 4, L = 18, Q = 20;

int n, q, k, ht[N], rt, centpar[N], sz[N], dist[N], nxt[N], mxdep[N], ans[Q], whenpsbl[N];
bool inf[N], psbl[N], vis[N];
simps queries[Q];
vector<int> adj[N], centadj[N], ord, setpsbl[N];

int sparse[L][2 * N], idx[N], stsz = 0, lg[2 * N];

vector<int> best[N];

//==================================================CMP==================================================//

bool cmp(int a, int b) {
    return ht[a] > ht[b];
}

//==================================================INIT + LCA==================================================//

void dfs1(int node, int parent, int height) {
    ht[node] = height;
    sparse[0][stsz] = node;
    idx[node] = stsz;
    stsz++;
    ord.push_back(node);
    for (int i : adj[node]) {
        if (i == parent) continue;
        dfs1(i, node, height + 1);
        sparse[0][stsz] = node;
        stsz++;
    }
    return;
}

int lca(int a, int b) {
    a = idx[a]; b = idx[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1], x = sparse[len][a], y = sparse[len][b - (1 << len) + 1];
    if (ht[x] < ht[y]) return x;
    return y;
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
    mxdep[node] = cur / 2;
    best[node].resize(mxdep[node] + 1, -1);
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

void setclosest(int node) {
    int cur = node;
    while (cur != -1) {
        setmn(dist[cur], getdist(node, cur));
        cur = centpar[cur];
    }
    return;
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

bool setbest(int& cur, int nw) {
    bool res = (nw != -1 and (cur == -1 or ht[nw] < ht[cur]));
    if (res) cur = nw;
    return res;
}

void setnxt(int node) {
    int cur = node;
    while (cur != -1) {
        int d = getdist(cur, node);
        setbest(best[cur][d], node);
        cur = centpar[cur];
    }
    return;
}

int getnxt(int node) {
    int cur = node, res = -1;
    while (cur != -1) {
        int d = k - getdist(cur, node);
        for (int i = 0; i <= min(d, mxdep[cur]); i++) setbest(res, best[cur][i]);
        cur = centpar[cur];
    }
    return res;
}

//==================================================MAIN==================================================//

int main() {
    memset(psbl, false, sizeof(psbl));
    memset(vis, false, sizeof(vis));
    lg[1] = 0;
    for (int i = 2; i < 2 * N; i++) lg[i] = lg[i / 2] + 1;

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
    for (int i = 1; (1 << i) <= stsz; i++) {
        for (int j = 0; j + (1 << i) <= stsz; j++) {
            int a = sparse[i - 1][j], b = sparse[i - 1][j + (1 << (i - 1))];
            if (ht[a] < ht[b]) sparse[i][j] = a;
            else sparse[i][j] = b;
        }
    }
    centdecomp(0, -1);

    queue<simps> qu;
    for (int i = 0; i < n; i++) {
        whenpsbl[i] = n + 1;
        if (inf[i]) continue;
        qu.push({i, 0});
        whenpsbl[i] = 0;
    }
    while (qu.size()) {
        int node = qu.front().first, d = qu.front().second;
        qu.pop();
        for (int i : adj[node]) {
            if (whenpsbl[i] != n + 1) continue;
            qu.push({i, d + 1});
            whenpsbl[i] = d + 1;
        }
    }
    for (int i = 0; i < n; i++) setpsbl[whenpsbl[i]].push_back(i);

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries, queries + q);

    k = n + 1;
    for (int i = q - 1; i >= 0; i--) { //big k to small k, small psbl to big psbl
        for (; k > queries[i].first; k--) {
            for (int j : setpsbl[k]) {
                psbl[j] = true;
                setnxt(j);
            }
        }

        ans[queries[i].second] = 0;
        fill(dist, dist + n, 1e9);
        for (int j : ord) {
            if (not inf[j] or getclosest(j) <= k) continue;
            int cur = getnxt(j);
            if (cur == -1) {
                ans[queries[i].second] = -1;
                break;
            }
            ans[queries[i].second]++;
            setclosest(cur);
        }
    }

    for (int i = 0; i < q; i++) cout << ans[i] << "\n";

	return 0;
}
