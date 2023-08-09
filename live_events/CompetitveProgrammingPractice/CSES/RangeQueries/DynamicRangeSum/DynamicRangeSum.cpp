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
vector<ll> seg;

void set(int node, int l, int r, int idx, ll val) {
    if (idx < l or idx > r) return;
    if (l == idx and r == idx) {
        seg[node] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, idx, val);
    set(2 * node + 1, mid + 1, r, idx, val);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

ll get(int node, int l, int r, int a, int b) {
    if (b < l or a > r) return 0;
    if (a <= l and b >= r) return seg[node];
    int mid = l + (r - l) / 2;
    return get(2 * node, l, mid, a, b) + get(2 * node + 1, mid + 1, r, a, b);
}

int main() {
    cin >> n >> q;
    seg.resize(4 * n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        set(1, 0, n - 1, i, cur);
    }
    for (int i = 0; i < q; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) set(1, 0, n - 1, a - 1, b);
        else cout << get(1, 0, n - 1, a - 1, b - 1) << "\n";
    }
	return 0;
}
