#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5 + 2, modval = 1e9 + 7;
ll pw[2 * N], invpw[2 * N];

struct SegTree {
    vector<int> lz;
    vector<ll> seg;

    SegTree(int sz) {
        lz.resize(4 * sz);
        seg.resize(4 * sz);
        build(1, 0, sz - 1);
        return;
    }

    ~SegTree() {}

    void build(int node, int l, int r) {
        if (l == r) {
            seg[node] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        seg[node] = (seg[2 * node] + seg[2 * node + 1]) % modval;
        return;
    }

    void prop(int node, int l, int r) {
        if (lz[node] == 0) return;
        if (l < r) {
            lz[2 * node] += lz[node];
            lz[2 * node + 1] += lz[node];
        }
        if (lz[node] > 0) seg[node] = seg[node] * pw[lz[node]] % modval;
        else seg[node] = seg[node] * invpw[-lz[node]] % modval;
        lz[node] = 0;
        return;
    }

    void set(int node, int l, int r, int a, int b, int c) {
        prop(node, l, r);
        if (l > b or r < a) return;
        if (l >= a and r <= b) {
            lz[node] += c;
            prop(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        set(2 * node, l, mid, a, b, c);
        set(2 * node + 1, mid + 1, r, a, b, c);
        seg[node] = (seg[2 * node] + seg[2 * node + 1]) % modval;
        return;
    }

    ll get(int node, int l, int r, int a, int b) {
        prop(node, l, r);
        if (l > b or r < a) return 0;
        if (l >= a and r <= b) return seg[node];
        int mid = l + (r - l) / 2;
        return (get(2 * node, l, mid, a, b) + get(2 * node + 1, mid + 1, r, a, b)) % modval;
    }
};

int n, y[N];
ll ans = 0;
simps cows[N];

void calc() {
    ll s1 = 1; //specifically, only 2^a(0) because terms cancel
    SegTree s2(n + 2), s3(n + 2); //s1: a(y), s2: a(y) + b(y), s3: a(y + 1) + b(y)
    
    for (int i = 0; i < n; i++) y[cows[i].first] = cows[i].second;
    
    for (int i = 1; i <= n; i++) {
        s2.set(1, 0, n + 1, i + 1, n + 1, 1);
        s3.set(1, 0, n + 1, i + 1, n + 1, 1);
    }

    for (int i = 1; i <= n; i++) {
        s2.set(1, 0, n + 1, y[i] + 1, n + 1, -1);
        s3.set(1, 0, n + 1, y[i] + 1, n + 1, -1);
    
        ans = (ans + modval - s2.get(1, 0, n + 1, 0, y[i])) % modval;
        ans = (ans + s1) % modval;
        ans = (ans + s3.get(1, 0, n + 1, 0, y[i] - 1)) % modval;

        s1 = 2 * s1 % modval;
        s2.set(1, 0, n + 1, 0, y[i], 1);
        s3.set(1, 0, n + 1, 0, y[i] - 1, 1);
    }

    return;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < 2 * N; i++) pw[i] = 2 * pw[i - 1] % modval;

    invpw[0] = 1;
    for (int i = 1; i < 2 * N; i++) invpw[i] = (modval + 1) / 2 * invpw[i - 1] % modval;

    cin >> n;

    for (int i = 0; i < n; i++) ans = (ans + pw[i] * (pw[n - i - 1] - 1) % modval) % modval;
    ans = 2 * ans % modval;

    for (int i = 0; i < n; i++) cin >> cows[i].first >> cows[i].second;
    calc();
    for (int i = 0; i < n; i++) cows[i] = {n + 1 - cows[i].second, cows[i].first};
    calc();

    cout << 2 * ans % modval << "\n";

	return 0;
}
