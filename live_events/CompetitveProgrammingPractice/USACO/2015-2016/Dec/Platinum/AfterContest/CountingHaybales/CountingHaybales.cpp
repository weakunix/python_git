#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
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

struct seg {
    ll mn, sm, lz;
};

int n, q;
vector<int> bales;
vector<seg> segtree;

void build(int node, int l, int r) {
    if (l == r) {
        segtree[node].mn = bales[l];
        segtree[node].sm = bales[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    segtree[node].mn = min(segtree[2 * node].mn, segtree[2 * node + 1].mn);
    segtree[node].sm = segtree[2 * node].sm + segtree[2 * node + 1].sm;
    return;
}

void prop(int node, int l, int r) {
    segtree[node].mn += segtree[node].lz;
    segtree[node].sm += (r - l + 1) * segtree[node].lz;
    if (l < r) {
        segtree[2 * node].lz += segtree[node].lz;
        segtree[2 * node + 1].lz += segtree[node].lz;
    }
    segtree[node].lz = 0;
    return;
}

void update(int node, int l, int r, int a, int b, int c) {
    if (l >= a and r <= b) segtree[node].lz += c;
    prop(node, l,  r);
    if ((l > b or r < a) or (l >= a and r <= b)) return;
    int mid = (l + r) / 2;
    update(2 * node, l, mid, a, b, c);
    update(2 * node + 1, mid + 1, r, a, b, c);
    segtree[node].mn = min(segtree[2 * node].mn, segtree[2 * node + 1].mn);
    segtree[node].sm = segtree[2 * node].sm + segtree[2 * node + 1].sm;
    return;
}

ll query(int node, int l, int r, int a, int b, bool smq) {
    prop(node, l, r);
    if (l > b or r < a) return (smq ? 0 : 1e18);
    if (l >= a and r <= b) return (smq ? segtree[node].sm : segtree[node].mn);
    int mid = (l + r) / 2;
    ll res1 = query(2 * node, l, mid, a, b, smq), res2 = query(2 * node + 1, mid + 1, r, a, b, smq);
    return (smq ? res1 + res2 : min(res1, res2));
}

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    cin >> n >> q;
    bales.resize(n);
    segtree.resize(4 * n);
    for (int i = 0; i < n; i++) cin >> bales[i];
    build(1, 0, n - 1);
    for (int i = 0; i < q; i++) {
        int a, b, c;
        char t;
        cin >> t >> a >> b;
        a--;
        b--;
        if (t == 'P') {
            cin >> c;
            update(1, 0, n - 1, a, b, c);
            continue;
        }
        cout << query(1, 0, n - 1, a, b, (t == 'S')) << "\n";
    }
	return 0;
}
