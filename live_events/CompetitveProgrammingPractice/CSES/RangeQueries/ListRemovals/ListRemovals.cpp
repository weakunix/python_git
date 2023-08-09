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

int n;
vector<int> arr, seg;

void set(int node, int l, int r, int idx, int change) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] += change;
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, idx, change);
    set(2 * node + 1, mid + 1, r, idx, change);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

int get(int node, int l, int r, int tar) {
    if (seg[node] < tar) return -1;
    if (l == r) return l;
    int mid = l + (r - l) / 2, cur = get(2 * node, l, mid, tar);
    if (cur != -1) return cur;
    cur = get(2 * node + 1, mid + 1, r, tar - seg[2 * node]);
    assert(cur != -1);
    return cur;
}

int main() {
    cin >> n;
    arr.resize(n);
    seg.resize(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        set(1, 0, n - 1, i, 1);
    }
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cur = get(1, 0, n - 1, cur);
        cout << arr[cur] << " ";
        set(1, 0, n - 1, cur, -1);
    }
    cout << "\n";
	return 0;
}
