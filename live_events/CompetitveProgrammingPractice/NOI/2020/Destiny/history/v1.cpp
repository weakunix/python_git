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

const int N = 5e5, modval = 998244353;

struct Seg {
    ll val, lzset, lzadd;
    Seg* l;
    Seg* r;

    Seg() : val(0), lzset(-1), lzadd(0), l(nullptr), r(nullptr) {}

    Seg(ll _val) : val(_val), lzset(-1), lzadd(0), l(nullptr), r(nullptr) {}

    ~Seg() {}
};

void prop(Seg* node, int l, int r) {
    //if (node->lzset == -1 and node->lzadd == 0) return;
    if (l < r) {
        if (not node->l) node->l = new Seg(node->val);
        if (not node->r) node->r = new Seg(node->val);
        if (node->lzset != -1) {
            node->l->lzset = node->lzset;
            node->l->lzadd = 0;
            node->r->lzset = node->lzset;
            node->r->lzadd = 0;
        }
        node->l->lzadd = (node->l->lzadd + node->lzadd) % modval;
        node->r->lzadd = (node->r->lzadd + node->lzadd) % modval;
    }
    
    if (node->lzset != -1) {
        node->val = node->lzset;
        node->lzset = -1;
    }
    node->val = (node->val + node->lzadd) % modval;
    node->lzadd = 0;
    return;
}

void upd(Seg* node) {
    node->val = (node->l ? node->l->val : 0) * (node->r ? node->r->val : 0) % modval;
    return;
}

void build(Seg* &node, int l, int r, int a, int b) {
    if (l > b or r < a) {
        node = nullptr;
        return;
    }
    if (l >= a and r <= b) {
        node = new Seg(1);
        return;
    }
    int mid = l + (r - l) / 2;
    node = new Seg(0);
    build(node->l, l, mid, a, b);
    build(node->r, mid + 1, r, a, b);
    upd(node);
    return;
}

ll get(Seg* node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 1;
    if (l >= a and r <= b) return node->val;
    int mid = l + (r - l) / 2;
    return get(node->l, l, mid, a, b) * get(node->r, mid + 1, r, a, b) % modval;
}

void add(Seg* node, int l, int r, int a, int b, ll c) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        node->lzadd += c;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    add(node->l, l, mid, a, b, c);
    add(node->r, mid + 1, r, a, b, c);
    upd(node);
    return;
}

void setseg(Seg* node, int l, int r, int a, int b, ll c) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        node->lzset = c;
        node->lzadd = 0;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(node->l, l, mid, a, b, c);
    setseg(node->r, mid + 1, r, a, b, c);
    upd(node);
    return;
}

Seg* merge(Seg* node1, Seg* node2, int l, int r) {
    if (not node1 and not node2) return nullptr;
    if (not node1) {
        prop(node2, l, r);
        return node2;
    }
    if (not node2) {
        prop(node1, l, r);
        return node1;
    }
    prop(node1, l, r); prop(node2, l, r);
    if (l == r) {
        Seg* res = new Seg(node1->val * node2->val % modval);
        return res;
    }
    int mid = l + (r - l) / 2;
    Seg* res = new Seg(0);
    res->l = merge(node1->l, node2->l, l, mid);
    res->r = merge(node1->r, node2->r, mid + 1, r);
    upd(res);
    return res;
}

int n, m, dep[N], lim[N];
vector<int> adj[N];

void dfs1(int node, int parent, int depth) {
    dep[node] = depth;
    for (int i : adj[node]) if (i != parent) dfs1(i, node, depth + 1);
    return;
}

Seg* dfs2(int node, int parent) {
    Seg* res = nullptr;
    vector<Seg*> cseg;

    for (int i : adj[node]) if (i != parent) cseg.pb(dfs2(i, node));

    if (cseg.empty()) {
        build(res, 0, n - 1, lim[node], dep[node]);
        return res;
    }

    for (Seg* s : cseg) {
        ll cur = get(s, 0, n - 1, dep[node] + 1, dep[node] + 1);
        add(s, 0, n - 1, 0, dep[node], cur);
        setseg(s, 0, n - 1, dep[node] + 1, dep[node] + 1, 0);
        res = merge(res, s, 0, n - 1);
    }
    setseg(res, 0, n - 1, 0, lim[node] - 1, 0);

    return res;
}

int main() {
    clr(lim, 0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs1(0, -1, 0);

    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        setmx(lim[v], dep[u] + 1);
    }

    cout << get(dfs2(0, -1), 0, n - 1, 0, 0) << "\n";

	return 0;
}
