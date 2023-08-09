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

void prop(int node, int l, int r) {
    if (l == r) return;
    seg[2 * node] += seg[node];
    seg[2 * node + 1] += seg[node];
    seg[node] = 0;
    return;
}

void set(int node, int l, int r, int a, int b, int val) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        seg[node] += val;
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, a, b, val);
    set(2 * node + 1, mid + 1, r, a, b, val);
    return;
}

ll get(int node, int l, int r, int idx) {
    prop(node, l, r);
    if (l > idx or r < idx) return -1;
    if (l == idx and r == idx) return seg[node];
    int mid = l + (r - l) / 2;
    return max(get(2 * node, l, mid, idx), get(2 * node + 1, mid + 1, r, idx));
}

int main() {
    cin >> n >> q;
    seg.resize(4 * n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        set(1, 0, n - 1, i, i, cur);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            set(1, 0, n - 1, a - 1, b - 1, c);
        }
        else {
            int k;
            cin >> k;
            cout << get(1, 0, n - 1, k - 1) << "\n";
        }
    }
	return 0;
}
