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

int n, m;
vector<int> seg;

void set(int node, int l, int r, int idx, int change) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] += change;
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, idx, change);
    set(2 * node + 1, mid + 1, r, idx, change);
    seg[node] = max(seg[2 * node], seg[2 * node + 1]);
    return;
}

int get(int node, int l, int r, int tar) {
    if (seg[node] < tar) return -1;
    if (l == r and seg[node] >= tar) return l;
    int mid = l + (r - l) / 2, cur;
    cur = get(2 * node, l, mid, tar);
    if (cur != -1) return cur;
    cur = get(2 * node + 1, mid + 1, r, tar);
    return cur;
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
        int cur, idx;
        cin >> cur;
        idx = get(1, 0, n - 1, cur);
        cout << idx + 1 << " ";
        if (idx != -1) set(1, 0, n - 1, idx, -cur);
    }
    cout << "\n";
	return 0;
}
