#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, q;
vector<int> arr;
vector<ll> seg;
vector<simps> lz;

void build(int node, int l, int r) {
    if (l == r) {
        seg[node] = arr[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

void prop(int node, int l, int r) {
    if (lz[node].first == 0 and lz[node].second == 0) return;
    if (l < r) {
        lz[2 * node].first += lz[node].first;
        lz[2 * node].second += lz[node].second;
        lz[2 * node + 1].first += lz[node].first + ((r - l) / 2 + 1) * lz[node].second;
        lz[2 * node + 1].second += lz[node].second;
    }
    seg[node] += (r - l + 1) * lz[node].first + lz[node].second * (r - l) * (r - l + 1) / 2;
    lz[node] = {0, 0};
    return;
}

void set(int node, int l, int r, int a, int b, int st) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lz[node] = {l - st + 1, 1};
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, a, b, st);
    set(2 * node + 1, mid + 1, r, a, b, st);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

ll get(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return get(2 * node, l, mid, a, b) + get(2 * node + 1, mid + 1 , r, a, b);
}

int main() {
    cin >> n >> q;
    arr.resize(n);
    seg.resize(4 * n);
    lz.resize(4 * n, {0, 0});
    for (int i = 0; i < n; i++) cin >> arr[i];
    build(1, 0, n - 1);
    for (int i = 0; i < q; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        a--; b--;
        if (t == 1) set(1, 0, n - 1, a, b, a);
        else cout << get(1, 0, n - 1, a, b) << "\n";
    }
	return 0;
}
