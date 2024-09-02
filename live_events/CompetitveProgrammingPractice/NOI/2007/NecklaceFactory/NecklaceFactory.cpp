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

const int N = 5e5 + 1;

struct Treap {
    int val, lv, rv, pri, sz, cnt, lz, l, r;
    bool rev;
    
    Treap() : val(0), lv(0), rv(0), pri(rng()), sz(0), cnt(0), lz(-1), l(0), r(0), rev(false) {}

    Treap(int _val) : val(_val), lv(_val), rv(_val), pri(rng()), sz(1), cnt(1), lz(-1), l(0), r(0), rev(false) {}

    ~Treap() {}
};

int n, q, rt = 0;
Treap trp[N];

void upd(int node) {
    trp[node].lv = trp[node].val;
    trp[node].rv = trp[node].val;
    trp[node].sz = 1;
    trp[node].cnt = 1;
    
    int l = trp[node].l, r = trp[node].r;

    if (l) {
        trp[node].lv = trp[l].lv;
        trp[node].sz += trp[l].sz;
        trp[node].cnt += trp[l].cnt - (trp[l].rv == trp[node].val);
    }
    if (r) {
        trp[node].rv = trp[r].rv;
        trp[node].sz += trp[r].sz;
        trp[node].cnt += trp[r].cnt - (trp[r].lv == trp[node].val);
    }

    return;
}

void paint(int node, int val) {
    if (not node) return;
    trp[node].val = val;
    trp[node].lv = val;
    trp[node].rv = val;
    trp[node].cnt = 1;
    trp[node].lz = val;
    return;
}

void rev(int node) {
    if (not node) return;
    swap(trp[node].lv, trp[node].rv);
    swap(trp[node].l, trp[node].r);
    trp[node].rev ^= true;
    return;
}

void prop(int node) {
    if (not node) return;
    if (trp[node].rev) {
        rev(trp[node].l);
        rev(trp[node].r);
        trp[node].rev = false;
    }
    if (trp[node].lz != -1) {
        paint(trp[node].l, trp[node].lz);
        paint(trp[node].r, trp[node].lz);
        trp[node].lz = -1;
    }
    return;
}

int merge(int l, int r) {
    prop(l);
    prop(r);

    if (not l) return r;
    if (not r) return l;

    if (trp[l].pri < trp[r].pri) {
        trp[l].r = merge(trp[l].r, r);
        upd(l);
        return l;
    }
    trp[r].l = merge(l, trp[r].l);
    upd(r);
    return r;
}

void split(int node, int& l, int& r, int k) {
    prop(node);

    if (not node) {
        l = 0;
        r = 0;
        return;
    }

    if (k <= trp[trp[node].l].sz) {
        split(trp[node].l, l, trp[node].l, k);
        r = node;
    }
    else {
        split(trp[node].r, trp[node].r, r, k - trp[trp[node].l].sz - 1);
        l = node;
    }

    upd(node);

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        trp[i] = Treap(cur);
        rt = merge(rt, i);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;

        if (op == "R") {
            int k, a;
            cin >> k;
            split(rt, rt, a, n - k);
            rt = merge(a, rt);
        }
        else if (op == "F") {
            int a;
            split(rt, rt, a, 1);
            rev(a);
            rt = merge(rt, a);
        }
        else if (op == "S") {
            int x, y, a, b, c, d;
            cin >> x >> y;
            if (x > y) swap(x, y);
            split(rt, rt, d, y);
            split(rt, rt, c, y - 1);
            split(rt, rt, b, x);
            split(rt, rt, a, x - 1);
            rt = merge(rt, merge(c, (merge(b, merge(a, d)))));
        }
        else if (op == "P") {
            int x, y, z, a, b;
            cin >> x >> y >> z;
            if (x <= y) {
                split(rt, rt, b, y);
                split(rt, rt, a, x - 1);
                paint(a, z);
            }
            else {
                split(rt, rt, b, x - 1);
                split(rt, rt, a, y);
                paint(rt, z);
                paint(b, z);
            }
            rt = merge(rt, merge(a, b));
        }
        else if (op == "C") {
            cout << max(trp[rt].cnt - (trp[rt].lv == trp[rt].rv), 1) << "\n";
        }
        else {
            int x, y, a, b;
            cin >> x >> y;
            if (x <= y) {
                split(rt, rt, b, y);
                split(rt, rt, a, x - 1);
                cout << trp[a].cnt << "\n";
            }
            else {
                split(rt, rt, b, x - 1);
                split(rt, rt, a, y);
                cout << trp[rt].cnt + trp[b].cnt - (trp[rt].lv == trp[b].rv) << "\n";
            }
            rt = merge(rt, merge(a, b));
        }
    }

	return 0;
}
