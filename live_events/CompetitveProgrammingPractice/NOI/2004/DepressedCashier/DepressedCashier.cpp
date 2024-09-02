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

const int S = 3e5 + 1;

int n, mn, zero = 1e5, seg[4 * S], lzset[4 * S], lzadd[4 * S], ans = 0;

void prop(int node, int l, int r) {
    if (lzset[node] != -1) {
        if (l < r) {
            lzset[2 * node] = lzset[node];
            lzadd[2 * node] = 0;
            lzset[2 * node + 1] = lzset[node];
            lzadd[2 * node + 1] = 0;
        }
        seg[node] = (r - l + 1) * lzset[node];
        lzset[node] = -1;
    }
    if (lzadd[node]) {
        if (l < r) {
            lzadd[2 * node] += lzadd[node];
            lzadd[2 * node + 1] += lzadd[node];
        }
        seg[node] += (r - l + 1) * lzadd[node];
        lzadd[node] = 0;
    }
    return;
}

void addseg(int node, int l, int r, int idx) {
    prop(node, l, r);
    if (l > idx or r < idx) return;
    if (l == r) {
        lzadd[node]++;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    addseg(2 * node, l, mid, idx);
    addseg(2 * node + 1, mid + 1, r, idx);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

int clrseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) {
        int res = seg[node];
        lzset[node] = 0;
        prop(node, l, r);
        return res;
    }
    int mid = l + (r - l) / 2;
    int res = clrseg(2 * node, l, mid, a, b) + clrseg(2 * node + 1, mid + 1, r, a, b);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return res;
}

int findseg(int node, int l, int r, int tar, int& cur) {
    prop(node, l, r);
    if (cur + seg[node] < tar) {
        cur += seg[node];
        return -1;
    }
    if (l == r) return l - zero;
    int mid = l + (r - l) / 2;
    int res = findseg(2 * node + 1, mid + 1, r, tar, cur);
    if (res != -1) return res;
    res = findseg(2 * node, l, mid, tar, cur);
    return res;
}

int main() {
    clr(seg, 0);
    clr(lzset, -1);
    clr(lzadd, 0);

    cin >> n >> mn;
    for (int i = 0; i < n; i++) {
        int k;
        char t;
        cin >> t >> k;

        if (t == 'I') {
            if (k < mn) continue;
            addseg(1, 0, S - 1, zero + k);
        }
        else if (t == 'A') {
            zero -= k;
        }
        else if (t == 'S') {
            zero += k;
            ans += clrseg(1, 0, S - 1, 0, zero + mn - 1);
        }
        else {
            int cur = 0;
            cout << findseg(1, 0, S - 1, k, cur) << "\n";
        }
    }
    cout << ans << "\n";

	return 0;
}
