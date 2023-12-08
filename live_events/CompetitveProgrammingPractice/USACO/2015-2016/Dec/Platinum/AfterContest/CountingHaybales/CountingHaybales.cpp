#include <iostream>
#include <cstdio>
#include <cstring>
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

const int N = 2e5;

int n, q;
ll segm[4 * N], segs[4 * N], lz[4 * N];

void prop(int node, int l, int r) {
    if (lz[node] == 0) return;
    if (l < r) {
        lz[2 * node] += lz[node];
        lz[2 * node + 1] += lz[node];
    }
    segm[node] += lz[node];
    segs[node] += lz[node] * (r - l + 1);
    lz[node] = 0;
    return;
}

void setseg(int node, int l, int r, int a, int b, int c) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lz[node] += c;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, c);
    setseg(2 * node + 1, mid + 1, r, a, b, c);
    segm[node] = min(segm[2 * node], segm[2 * node + 1]);
    segs[node] = segs[2 * node] + segs[2 * node + 1];
    return;
}

ll getseg(int node, int l, int r, int a, int b, bool t) {
    prop(node, l, r);
    if (l > b or r < a) return t ? 1e18 : 0;
    if (l >= a and r <= b) return t ? segm[node] : segs[node];
    int mid = l + (r - l) / 2;
    ll res1 = getseg(2 * node, l, mid, a, b, t), res2 = getseg(2 * node + 1, mid + 1, r, a, b, t);
    return t ? min(res1, res2) : res1 + res2;
}

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    memset(segm, 0, sizeof(segm));
    memset(segs, 0, sizeof(segs));
    memset(lz, 0, sizeof(lz));

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        setseg(1, 0, n - 1, i, i, cur);
    }

    for (int i = 0; i < q; i++) {
        int a, b, c;
        char t;
        cin >> t >> a >> b;
        if (t == 'M') cout << getseg(1, 0, n - 1, a - 1, b - 1, true) << "\n";
        else if (t == 'S') cout << getseg(1, 0, n - 1, a - 1, b - 1, false) << "\n";
        else {
            cin >> c;
            setseg(1, 0, n - 1, a - 1, b - 1, c);
        }
    }
	return 0;
}
