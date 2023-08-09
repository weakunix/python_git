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
vector<ll> arr, ansseg, lazy;

void prop(int node, int l, int r) {
    if (l < r) {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
    }
    ansseg[node] += lazy[node];
    lazy[node] = 0;
    return;
}

void setans(int node, int l, int r, int a, int b, ll change) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lazy[node] += change;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setans(2 * node, l, mid, a, b, change);
    setans(2 * node + 1, mid + 1, r, a, b, change);
    ansseg[node] = max(ansseg[2 * node], ansseg[2 * node + 1]);
    return;
}

ll getans(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return -1e18;
    if (l >= a and r <= b) return ansseg[node];
    int mid = l + (r - l) / 2;
    return max(getans(2 * node, l, mid, a, b), getans(2 * node + 1, mid + 1, r, a, b));
}

int main() {
    cin >> n >> q;
    arr.resize(n);
    ansseg.resize(4 * n + 4);
    lazy.resize(4 * n + 4);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        setans(1, 0, n, i + 1, n, arr[i]);
    }
    for (int i = 0; i < q; i++) {
        ll t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            setans(1, 0, n, a, n, b - arr[a - 1]);
            arr[a - 1] = b;
        }
        else cout << max(getans(1, 0, n, a, b) - getans(1, 0, n, a - 1, a - 1), (ll) 0) << "\n";
    }
	return 0;
}
