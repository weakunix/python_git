#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <deque>
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
vector<int> stck;
vector<ll> arr, pfx, seg, lz, ans;
vector<vector<simps>> queries;

void prop(int node, int l, int r) {
    if (lz[node] == 0) return;
    if (l < r) {
        lz[2 * node] = lz[node];
        lz[2 * node + 1] = lz[node];
    }
    seg[node] = lz[node] * (r - l + 1);
    lz[node] = 0;
    return;
}

void set(int node, int l, int r, int a, int b, ll val) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lz[node] = val;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, a, b, val);
    set(2 * node + 1, mid + 1, r, a, b, val);
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
    stck.push_back(n);
    arr.resize(n);
    pfx.resize(n + 1);
    seg.resize(4 * n);
    lz.resize(4 * n);
    ans.resize(q);
    queries.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pfx[i + 1] = pfx[i] + arr[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        queries[l].push_back({r, i});
    }
    for (int i = n - 1; i >= 0; i--) {
        while (stck.back() < n and arr[stck.back()] <= arr[i]) stck.pop_back();
        set(1, 0, n - 1, i, stck.back() - 1, arr[i]);
        stck.push_back(i);
        for (simps s : queries[i]) ans[s.second] = get(1, 0, n - 1, i, s.first) - pfx[s.first + 1] + pfx[i];
    }
    for (ll i : ans) cout << i << "\n";
	return 0;
}
