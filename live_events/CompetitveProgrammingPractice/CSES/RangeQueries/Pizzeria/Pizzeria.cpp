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
vector<int> segl, segr;

void set(vector<int>& seg, int node, int l, int r, int idx, int val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    set(seg, 2 * node, l, mid, idx, val);
    set(seg, 2 * node + 1, mid + 1, r, idx, val);
    seg[node] = min(seg[2 * node], seg[2 * node + 1]);
    return;
}

int get(vector<int>& seg, int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 2e9;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return min(get(seg, 2 * node, l, mid, a, b), get(seg, 2 * node + 1, mid + 1, r, a, b));
}

int main() {
    cin >> n >> q;
    segl.resize(4 * n);
    segr.resize(4 * n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        set(segl, 1, 0, n - 1, i, cur - i);
        set(segr, 1, 0, n - 1, i, cur + i);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            k--;
            set(segl, 1, 0, n - 1, k, x - k);
            set(segr, 1, 0, n - 1, k, x + k);
        }
        else {
            int k;
            cin >> k;
            k--;
            cout << min(get(segl, 1, 0, n - 1, 0, k) + k, get(segr, 1, 0, n - 1, k, n - 1) - k) << "\n";
        }
    }
	return 0;
}
