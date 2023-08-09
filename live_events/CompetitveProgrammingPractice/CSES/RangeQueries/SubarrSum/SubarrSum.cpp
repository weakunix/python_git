#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<ll, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

struct SegNode {
    ll subsum = 0, lsum = 0, rsum = 0, sm = 0;
};

int n, m;
vector<SegNode> seg;

void set(int node, int l, int r, int idx, int val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node].subsum = val;
        seg[node].lsum = val;
        seg[node].rsum = val;
        seg[node].sm = val;
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, idx, val);
    set(2 * node + 1, mid + 1, r, idx, val);
    seg[node].sm = seg[2 * node].sm + seg[2 * node + 1].sm;
    seg[node].lsum = max(seg[2 * node].lsum, seg[2 * node].sm + seg[2 * node + 1].lsum);
    seg[node].rsum = max(seg[2 * node + 1].rsum, seg[2 * node + 1].sm + seg[2 * node].rsum);
    seg[node].subsum = max({seg[2 * node].subsum, seg[2 * node + 1].subsum, seg[2 * node].rsum + seg[2 * node + 1].lsum});
    return;
}

int main() {
    cin >> n >> m;
    seg.resize(4 * n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        set(1, 0, n - 1, i, cur);
    }
    for (int i = 0; i < m; i++) {
        int k, x;
        cin >> k >> x;
        k--;
        set(1, 0, n - 1, k, x);
        cout << max(seg[1].subsum, (ll) 0) << "\n";
    }
	return 0;
}
