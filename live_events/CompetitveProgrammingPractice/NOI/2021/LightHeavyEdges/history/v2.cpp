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

const int N = 1e5, L = 18;
int lg[2 * N + 1];

struct SegNode {
    int label, cnt, lzcnt;
    
    SegNode() : label(-1), cnt(-1), lzcnt(-1) {}

    ~SegNode() {}
};

int t, n, m, par[N], ht[N], sub[N], hv[N], tp[N], sparse[L][2 * N], etidx[N], segidx[N], timer;
vector<int> adj[N];
SegNode seg[4 * N];

void dfs1(int node, int parent, int height) {
    par[node] = parent;
    ht[node] = height;
    sub[node] = 1;
    hv[node] = -1;
    sparse[0][timer] = node;
    etidx[node] = timer;
    timer++;

    for (int i : adj[node]) {
        if (i == parent) continue;
        dfs1(i, node, height + 1);
        sub[node] += sub[i];
        if (hv[node] == -1 or sub[hv[node]] < sub[i]) hv[node] = i;
        sparse[0][timer] = node;
        timer++;
    }

    return;
}

void dfs2(int node, int top) {
    tp[node] = top;
    segidx[node] = timer;
    timer++;

    if (hv[node] == -1) return;
    dfs2(hv[node], top);
    
    for (int i : adj[node]) if (i != par[node] and i != hv[node]) dfs2(i, i);

    return;
}

int getlca(int a, int b) {
    a = etidx[a]; b = etidx[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    int x = sparse[len][a], y = sparse[len][b - (1 << len) + 1];
    if (ht[x] < ht[y]) return x;
    return y;
}

void prop(int node, int l, int r, bool proplabel) {
    if (proplabel) {
        if (seg[node].label != -1 and l < r) {
            seg[2 * node].label = seg[node].label;
            seg[2 * node + 1].label = seg[node].label;
            seg[node].label = -1;
        }
    }
    if (seg[node].lzcnt != -1) {
        if (l < r) {
            seg[2 * node].lzcnt = seg[node].lzcnt;
            seg[2 * node + 1].lzcnt = seg[node].lzcnt;
        }
        seg[node].cnt = seg[node].lzcnt * (r - l + 1);
        seg[node].lzcnt = -1;
    }
    return;
}

void setseg(int node, int l, int r, int a, int b, int label, int cnt) {
    prop(node, l, r, label != -1);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        if (label != -1) seg[node].label = label;
        if (cnt != -1) seg[node].lzcnt = cnt;
        prop(node, l, r, label != -1);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, label, cnt);
    setseg(2 * node + 1, mid + 1, r, a, b, label, cnt);
    seg[node].cnt = seg[2 * node].cnt + seg[2 * node + 1].cnt;
    return;
}

int getseglabel(int node, int l, int r, int idx) {
    if (l > idx or r < idx) return -1;
    if (seg[node].label != -1 or l == r) return seg[node].label;
    int mid = l + (r - l) / 2;
    return max(getseglabel(2 * node, l, mid, idx), getseglabel(2 * node + 1, mid + 1, r, idx));
}

int getsegcnt(int node, int l, int r, int a, int b) {
    prop(node, l, r, false);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node].cnt;
    int mid = l + (r - l) / 2;
    return getsegcnt(2 * node, l, mid, a, b) + getsegcnt(2 * node + 1, mid + 1, r, a, b);
}

void updpath(int a, int b, int label) {
    if (a == b) return;
    while (ht[tp[a]] >= ht[b]) {
        if (hv[a] != -1 and a != b) setseg(1, 0, n - 1, segidx[hv[a]], segidx[hv[a]], -1, 0);
        setseg(1, 0, n - 1, segidx[tp[a]], segidx[a], label, 1);
        a = par[tp[a]];
        if (a == -1) return;
    }
    if (ht[a] < ht[b]) return;
    if (hv[a] != -1 and a != b) setseg(1, 0, n - 1, segidx[hv[a]], segidx[hv[a]], -1, 0);
    setseg(1, 0, n - 1, segidx[b], segidx[a], label, 1);
    return;
}

int getpath(int a, int b) {
    int res = 0;
    while (ht[tp[a]] > ht[b]) {
        if (hv[tp[a]] != -1 and a != tp[a]) res += getsegcnt(1, 0, n - 1, segidx[hv[tp[a]]], segidx[a]);
        int curlabel = getseglabel(1, 0, n - 1, segidx[tp[a]]);
        if (curlabel != -1 and curlabel == getseglabel(1, 0, n - 1, segidx[par[tp[a]]])) res++;
        a = par[tp[a]];
    }
    if (hv[b] != -1 and a != b) res += getsegcnt(1, 0, n - 1, segidx[hv[b]], segidx[a]);
    return res;
}

void subcase() {
    cin >> n >> m;
    for (int i = 0; i < 4 * n; i++) {
        if (i < n) adj[i].clear();
        seg[i].label = -1;
        seg[i].cnt = 0;
        seg[i].lzcnt = -1;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    timer = 0;
    dfs1(0, -1, 0);

    for (int i = 1; (1 << i) <= timer; i++) {
        for (int j = 0; j + (1 << i) <= timer; j++) {
            int a = sparse[i - 1][j], b = sparse[i - 1][j + (1 << (i - 1))];
            if (ht[a] > ht[b]) swap(a, b);
            sparse[i][j] = a;
        }
    }

    timer = 0;
    dfs2(0, 0);

    for (int i = 0; i < m; i++) {
        int type, a, b, l;
        cin >> type >> a >> b;
        a--; b--;
        l = getlca(a, b);
        if (type == 1) {
            updpath(a, l, i);
            updpath(b, l, i);
            setseg(1, 0, n - 1, segidx[l], segidx[l], -1, 0);
            if (hv[l] and (getlca(a, hv[l]) != hv[l] and getlca(b, hv[l]) != hv[l])) setseg(1, 0, n - 1, segidx[hv[l]], segidx[hv[l]], -1, 0);
        }
        else {
            int res = getpath(a, l) + getpath(b, l);
            cout << res << "\n";
        }
    }

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    lg[1] = 0;
    for (int i = 2; i <= 2 * N; i++) lg[i] = lg[i / 2] + 1;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
