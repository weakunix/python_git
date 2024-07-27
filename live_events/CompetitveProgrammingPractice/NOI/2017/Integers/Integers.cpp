#include <iostream>
#include <cstdio>
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
#include <numeric>
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

const int N = 1e6 + 5, L = 30, MX = 1 << 30;

struct SegNode {
    int val, nocnt, mxcnt, lz;

    SegNode() : val(0), nocnt(0), mxcnt(0), lz(0) {}

    ~SegNode() {}
};

int n, t;
SegNode seg[4 * N];

void prop(int node, int l , int r) {
    if (not seg[node].lz) return;
    if (l < r) {
        seg[2 * node].lz = seg[node].lz;
        seg[2 * node + 1].lz = seg[node].lz;
    }
    if (seg[node].lz == 1) {
        seg[node].val = 0;
        seg[node].nocnt = r - l + 1;
        seg[node].mxcnt = 0;
    }
    else {
        seg[node].val = MX - 1;
        seg[node].nocnt = 0;
        seg[node].mxcnt = r - l + 1;
    }
    seg[node].lz = 0;
    return;
}

bool shiftseg(int node, int l, int r, int idx, int neg) {
    prop(node, l, r);
    if (l >= idx) {
        int cnt = (neg == 1 ? seg[node].mxcnt : seg[node].nocnt);
        if (l == r and cnt == 0) {
            seg[node].val += neg;
            seg[node].nocnt = (seg[node].val == 0);
            seg[node].mxcnt = (seg[node].val == MX - 1);
            return false;
        }
        if (cnt == r - l + 1) {
            seg[node].lz = neg;
            prop(node, l, r);
            return true;
        }
        int mid = l + (r - l) / 2;
        if (shiftseg(2 * node, l, mid, idx, neg)) shiftseg(2 * node + 1, mid + 1, r, idx, neg);
        seg[node].nocnt = seg[2 * node].nocnt + seg[2 * node + 1].nocnt;
        seg[node].mxcnt = seg[2 * node].mxcnt + seg[2 * node + 1].mxcnt;
        return false;
    }

    int mid = l + (r - l) / 2;
    bool works;
    if (idx > mid) works = shiftseg(2 * node + 1, mid + 1, r, idx, neg);
    else works = (shiftseg(2 * node, l, mid, idx, neg) and shiftseg(2 * node + 1, mid + 1, r, idx, neg));
    seg[node].nocnt = seg[2 * node].nocnt + seg[2 * node + 1].nocnt;
    seg[node].mxcnt = seg[2 * node].mxcnt + seg[2 * node + 1].mxcnt;
    return works;
}

bool setseg(int node, int l, int r, int idx, int val, int neg) {
    prop(node, l, r);
    if (l > idx or r < idx) return false;
    if (l == r) {
        bool shift = false;
        if (neg == 1) {
            seg[node].val += val;
            if (seg[node].val >= MX) {
                shift = true;
                seg[node].val -= MX;
            }
        }
        else {
            seg[node].val -= val;
            if (seg[node].val < 0) {
                shift = true;
                seg[node].val += MX;
            }
        }
        seg[node].nocnt = (seg[node].val == 0);
        seg[node].mxcnt = (seg[node].val == MX - 1);
        return shift;
    }

    int mid = l + (r - l) / 2;
    bool shift = (setseg(2 * node, l, mid, idx, val, neg) or setseg(2 * node + 1, mid + 1, r, idx, val, neg));
    seg[node].nocnt = seg[2 * node].nocnt + seg[2 * node + 1].nocnt;
    seg[node].mxcnt = seg[2 * node].mxcnt + seg[2 * node + 1].mxcnt;
    return shift;
}

bool getseg(int node, int l, int r, int idx, int k) {
    prop(node, l, r);
    if (l == r) return seg[node].val & (1 << k);
    int mid = l + (r - l) / 2;
    if (idx <= mid) return getseg(2 * node, l, mid, idx, k);
    return getseg(2 * node + 1, mid + 1, r, idx, k);
}

void buildseg(int node, int l, int r) {
    seg[node].nocnt = r - l + 1;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    buildseg(2 * node, l, mid);
    buildseg(2 * node + 1, mid + 1, r);
    return;
}

int main() {
    buildseg(1, 0, N - 1);

    cin >> n >> t >> t >> t;
    for (int i = 0; i < n; i++) {
        cin >> t;
        if (t == 1) {
            ll a, b;
            cin >> a >> b;
            
            int idx = b / L, neg = abs(a) / a;
            a = abs(a) << (b % L);

            if (setseg(1, 0, N - 1, idx, a % MX, neg)) shiftseg(1, 0, N - 1, idx + 1, neg);
            if (setseg(1, 0, N - 1, idx + 1, a / MX, neg)) shiftseg(1, 0, N - 1, idx + 2, neg);
        }
        else {
            int k;
            cin >> k;
            cout << getseg(1, 0, N - 1, k / L, k % L) << "\n";
        }
    }
	return 0;
}
