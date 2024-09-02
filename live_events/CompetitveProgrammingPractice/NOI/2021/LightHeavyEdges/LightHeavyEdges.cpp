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

const int N = 1e5;

struct Seg {
    int l, r, cnt, lz;

    Seg() : l(-1e9), r(-1e9), cnt(0), lz(-1) {}

    Seg(int _l, int _r, int _cnt) : l(_l), r(_r), cnt(_cnt), lz(-1) {}

    ~Seg() {}
};

int t, n, q, par[N], dep[N], hv[N], tp[N], idx[N], cntr;
vector<int> adj[N];
Seg seg[4 * N];

int dfs1(int node, int parent, int depth) {
    par[node] = parent;
    dep[node] = depth;

    int sz = 1, best = -1;

    for (int i : adj[node]) {
        if (i == parent) continue;
        
        int cur = dfs1(i, node, depth + 1);
        sz += cur;

        if (cur > best) {
            best = cur;
            hv[node] = i;
        }
    }

    return sz;
}

void dfs2(int node, int top) {
    tp[node] = top;
    idx[node] = cntr;
    cntr++;

    if (hv[node] != -1) dfs2(hv[node], top);

    for (int i : adj[node]) if (i != par[node] and i != hv[node]) dfs2(i, i);

    return;
}

Seg merge(Seg a, Seg b) {
    return Seg(a.l, b.r, a.cnt + b.cnt + (a.r == b.l));
}

void prop(int node, int l, int r) {
    if (seg[node].lz == -1) return;
    if (l < r) {
        seg[2 * node].lz = seg[node].lz;
        seg[2 * node + 1].lz = seg[node].lz;
    }
    seg[node] = Seg(seg[node].lz, seg[node].lz, r - l);
    return;
}

void buildseg(int node, int l, int r) {
    if (l == r) {
        seg[node] = Seg(-l, -l, 0);
        return;
    }
    int mid = l + (r - l) / 2;
    buildseg(2 * node, l, mid);
    buildseg(2 * node + 1, mid + 1, r);
    seg[node] = merge(seg[2 * node], seg[2 * node + 1]);
    return;
}

void setseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        seg[node].lz = cntr;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b);
    setseg(2 * node + 1, mid + 1, r, a, b);
    seg[node] = merge(seg[2 * node], seg[2 * node + 1]);
    return;
}

Seg getseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    if (a > mid) return getseg(2 * node + 1, mid + 1, r, a, b);
    if (b <= mid) return getseg(2 * node, l, mid, a, b);
    return merge(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

void updq(int u, int v) {
    while (tp[u] != tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
        setseg(1, 0, n - 1, idx[tp[u]], idx[u]);
        u = par[tp[u]];
    }

    if (dep[u] < dep[v]) swap(u, v);
    setseg(1, 0, n - 1, idx[v], idx[u]);

    cntr++;

    return;
}

int getq(int u, int v) {
    Seg resu, resv;

    while (tp[u] != tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) {
            swap(u, v);
            swap(resu, resv);
        }
        resu = merge(getseg(1, 0, n - 1, idx[tp[u]], idx[u]), resu);
        u = par[tp[u]];
    }

    if (dep[u] < dep[v]) {
        swap(u, v);
        swap(resu, resv);
    }
    resu = merge(getseg(1, 0, n - 1, idx[v], idx[u]), resu);
    resv = merge(getseg(1, 0, n - 1, idx[v], idx[v]), resv);

    return resu.cnt + resv.cnt;
}

void subcase() {
    clr(hv, -1);
    cntr = 0;
    for (int i = 0; i < N; i++) adj[i].clear();

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs1(0, -1, 0);
    dfs2(0, 0);

    buildseg(1, 0, n - 1);
    cntr = 1;

    for (int i = 0; i < q; i++) {
        int op, u, v;
        cin >> op >> u >> v;
        u--; v--;

        if (op == 1) updq(u, v);
        else cout << getq(u, v) << "\n";
    }

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
