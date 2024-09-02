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

struct Treap {
    int val, lv, rv, pri, sz, cnt, lz;
    bool rev;
    Treap* l;
    Treap* r;
    
    Treap() : val(0), lv(0), rv(0), pri(rng()), sz(1), cnt(1), lz(-1), rev(false), l(nullptr), r(nullptr) {}

    Treap(int _val) : val(_val), lv(_val), rv(_val), pri(rng()), sz(1), cnt(1), lz(-1), rev(false), l(nullptr), r(nullptr) {}

    ~Treap() {}
};

void prop(Treap* node) {
    if (not node) return;
    if (node->rev) {
        if (node->l) node->l->rev ^= true;
        if (node->r) node->r->rev ^= true;
        swap(node->l, node->r);
        swap(node->lv, node->rv);
        node->rev = false;
    }
    if (node->lz != -1) {
        if (node->l) node->l->lz = node->lz;
        if (node->r) node->r->lz = node->lz;
        node->val = node->lz;
        node->lv = node->lz;
        node->rv = node->lz;
        node->cnt = 1;
        node->lz = -1;
    }
    return;
}

int getlv(Treap* node) {
    prop(node);
    return (node ? node->lv : -1);
}

int getrv(Treap* node) {
    prop(node);
    return (node ? node->rv : -1);
}

int getsz(Treap* node) {
    prop(node);
    return (node ? node->sz : 0);
}

int getcnt(Treap* node) {
    prop(node);
    return (node ? node->cnt : 0);
}

void merge(Treap* &node, Treap* l, Treap* r) {
    prop(l); prop(r);
    if (not l) {
        node = r;
        return;
    }
    if (not r) {
        node = l;
        return;
    }
    if (l->pri > r->pri) {
        merge(l->r, l->r, r);
        node = l;
    }
    else {
        merge(r->l, l, r->l);
        node = r;
    }
    node->lv = (node->l ? getlv(node->l) : node->val);
    node->rv = (node->r ? getrv(node->r) : node->val);
    node->sz = getsz(node->l) + getsz(node->r) + 1;
    node->cnt = getcnt(node->l) + getcnt(node->r) + 1 - (getrv(node->l) == node->val) - (getlv(node->r) == node->val);
    return;
}

void split(Treap* node, Treap* &l, Treap* &r, int lsz) {
    prop(node);
    if (not node) {
        l = nullptr;
        r = nullptr;
        return;
    }
    if (lsz <= getsz(node->l)) {
        split(node->l, l, node->l, lsz);
        r = node;
    }
    else {
        split(node->r, node->r, r, lsz - getsz(node->l) - 1);
        l = node;
    }
    node->lv = (node->l ? getlv(node->l) : node->val);
    node->rv = (node->r ? getrv(node->r) : node->val);
    node->sz = getsz(node->l) + getsz(node->r) + 1;
    node->cnt = getcnt(node->l) + getcnt(node->r) + 1 - (getrv(node->l) == node->val) - (getlv(node->r) == node->val);
    return;
}

int n, q;
Treap* rt = nullptr;

void paint(int x, int y, int z) {
    Treap* a;
    Treap* b;
    split(rt, rt, a, x - 1);
    split(a, a, b, y - x + 1);
    a->lz = z;
    merge(rt, rt, a);
    merge(rt, rt, b);
}

int get(int x, int y) {
    int res;
    Treap* a;
    Treap* b;
    split(rt, rt, a, x - 1);
    split(a, a, b, y - x + 1);
    res = a->cnt;
    merge(rt, rt, a);
    merge(rt, rt, b);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        merge(rt, rt, new Treap(cur));
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;

        if (op == "R") {
            int k;
            Treap* a;
            cin >> k;
            split(rt, rt, a, n - k);
            merge(rt, a, rt);
        }
        else if (op == "F") {
            Treap* a;
            split(rt, rt, a, 1);
            if (a) a->rev ^= true;
            merge(rt, rt, a);
        }
        else if (op == "S") {
            int x, y;
            Treap* a;
            Treap* b;
            Treap* c;
            Treap* d;
            cin >> x >> y;
            if (x == y) continue;
            if (x > y) swap(x, y);
            split(rt, rt, a, x - 1);
            split(a, a, b, 1);
            split(b, b, c, y - x - 1);
            split(c, c, d, 1);
            merge(rt, rt, c);
            merge(rt, rt, b);
            merge(rt, rt, a);
            merge(rt, rt, d);
        }
        else if (op == "P") {
            int x, y, z;
            cin >> x >> y >> z;
            if (x <= y) paint(x, y, z);
            else {
                paint(x, n, z);
                paint(1, y, z);
            }
        }
        else if (op == "C") {
            cout << max(getcnt(rt)- (rt->lv == rt->rv), 1) << "\n";
        }
        else {
            int x, y;
            cin >> x >> y;
            if (x <= y) cout << get(x, y) << "\n";
            else cout << get(x, n) + get(1, y) - (rt->lv == rt->rv) << "\n";
        }
    }

	return 0;
}
