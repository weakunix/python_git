#include <iostream>
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

int n, q;
vector<ll> seg, lzinc, lzset;

void prop(int node, int l, int r) {
    if (lzinc[node] == -1) return;
    if (l < r) {
        if (lzset[node] != -1) {
            lzset[2 * node] = lzset[node];
            lzset[2 * node + 1] = lzset[node];
            lzinc[2 * node] = 0;
            lzinc[2 * node + 1] = 0;
        }
        if (lzinc[2 * node] == -1) lzinc[2 * node] = 0;
        if (lzinc[2 * node + 1] == -1) lzinc[2 * node + 1] = 0;
        lzinc[2 * node] += lzinc[node];
        lzinc[2 * node + 1] += lzinc[node];
    }
    if (lzset[node] != -1) seg[node] = lzset[node] * (r - l + 1);
    seg[node] += lzinc[node] * (r - l + 1);
    lzset[node] = -1;
    lzinc[node] = -1;
    return;
}

void set(int node, int l, int r, int a, int b, int type, ll val) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        if (type == 1) lzinc[node] = val;
        else {
            lzset[node] = val;
            lzinc[node] = 0;
        }
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, a, b, type, val);
    set(2 * node + 1, mid + 1, r, a, b, type, val);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

ll get(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return get(2 * node, l, mid, a, b) + get(2 * node + 1, mid + 1, r, a, b);
}

int main() {
    cin >> n >> q;
    seg.resize(4 * n);
    lzinc.resize(4 * n, -1);
    lzset.resize(4 * n, -1);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        set(1, 0, n - 1, i, i, 2, cur);
    }
    for (int i = 0; i < q; i++) {
        int type, a, b, x;
        cin >> type >> a >> b;
        a--; b--;
        if (type == 3) {
            cout << get(1, 0, n - 1, a, b) << "\n";
            continue;
        }
        cin >> x;
        set(1, 0, n - 1, a, b, type, x);
    }
	return 0;
}
