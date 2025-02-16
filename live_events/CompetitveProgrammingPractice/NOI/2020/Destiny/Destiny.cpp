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
    ll val, lzmul, lzadd;
    Seg* l;
    Seg* r;

    Seg() : val(0), lzmul(1), lzadd(0), l(nullptr), r(nullptr) {}

    Seg(ll _val) : val(_val), lzmul(1), lzadd(0), l(nullptr), r(nullptr) {}

    ~Seg() {}
};

void prop(Seg* node) {
    if (node->val == -1) {
        node->l->lzmul = node->l->lzmul * node->lzmul % modval;
        node->l->lzadd = node->l->lzadd * node->lzmul % modval;
        node->r->lzmul = node->r->lzmul * node->lzmul % modval;
        node->r->lzadd = node->r->lzadd * node->lzmul % modval;
        node->l->lzadd = (node->l->lzadd + node->lzadd) % modval;
        node->r->lzadd = (node->r->lzadd + node->lzadd) % modval;
    }
    else node->val = (node->val * node->lzmul % modval + node->lzadd) % modval;
    
    node->lzmul = 1;
    node->lzadd = 0;

    return;
}

void addchild(Seg* node) {
    node->l = new Seg(node->val);
    node->r = new Seg(node->val);
    node->val = -1;
    return;
}

void build(Seg* &node, int l, int r, int a, int b) {
    if (l > b or r < a) {
        node = new Seg(0);
        return;
    }
    if (l >= a and r <= b) {
        node = new Seg(1);
        return;
    }
    int mid = l + (r - l) / 2;
    node = new Seg(-1);
    build(node->l, l, mid, a, b);
    build(node->r, mid + 1, r, a, b);
    return;
}

ll get(Seg* node, int l, int r, int idx) {
    prop(node);
    if (node->val != -1) return node->val;
    int mid = l + (r - l) / 2;
    return (idx <= mid ? get(node->l, l, mid, idx) : get(node->r, mid + 1, r, idx));
}

void add(Seg* node, int l, int r, int a, int b, ll c) {
    prop(node);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        node->lzadd = (node->lzadd + c) % modval;
        prop(node);
        return;
    }
    int mid = l + (r - l) / 2;
    if (node->val != -1) addchild(node);
    add(node->l, l, mid, a, b, c);
    add(node->r, mid + 1, r, a, b, c);
    return;
}

void mul(Seg* node, int l, int r, int a, int b, ll c) {
    prop(node);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        node->lzmul = node->lzmul * c % modval;
        prop(node);
        return;
    }
    int mid = l + (r - l) / 2;
    if (node->val != -1) addchild(node);
    mul(node->l, l, mid, a, b, c);
    mul(node->r, mid + 1, r, a, b, c);
    return;
}

Seg* merge(Seg* node1, Seg* node2) {
    if (not node1) {
        prop(node2);
        return node2;
    }
    if (not node2) {
        prop(node1);
        return node1;
    }

    prop(node1); prop(node2);

    if (node2->val != -1) swap(node1, node2);
    if (node1->val != -1) {
        node2->lzmul = node2->lzmul * node1->val % modval;
        prop(node2);
        return node2;
    }

    node1->l = merge(node1->l, node2->l);
    node1->r = merge(node1->r, node2->r);
    return node1;
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
        ll cur = get(s, 0, n - 1, dep[node] + 1);
        add(s, 0, n - 1, 0, dep[node], cur);
        mul(s, 0, n - 1, dep[node] + 1, dep[node] + 1, 0);
        res = merge(res, s);
    }
    mul(res, 0, n - 1, 0, lim[node] - 1, 0);

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

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

    cout << get(dfs2(0, -1), 0, n - 1, 0) << "\n";

	return 0;
}
