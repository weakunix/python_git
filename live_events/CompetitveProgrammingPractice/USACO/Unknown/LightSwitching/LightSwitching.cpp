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

const int N = 1e5;

int n, q, seg[4 * N];
bool lz[4 * N];

void prop(int node, int l, int r) {
    if (not lz[node]) return;

    if (l < r) {
        lz[2 * node] = not lz[2 * node];
        lz[2 * node + 1] = not lz[2 * node + 1];
    }

    seg[node] = r - l + 1 - seg[node];
    lz[node] = false;

    return;
}

void setseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        assert(not lz[node]);
        lz[node] = true;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b);
    setseg(2 * node + 1, mid + 1, r, a, b);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

int getseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return getseg(2 * node, l, mid, a, b) + getseg(2 * node + 1, mid + 1, r, a, b);
}

int main() {
    memset(seg, 0, sizeof(seg));
    memset(lz, false, sizeof(lz));

    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        a--; b--;
        if (t == 0) setseg(1, 0, n - 1, a, b);
        else cout << getseg(1, 0, n - 1, a, b) << "\n";
    }

	return 0;
}
