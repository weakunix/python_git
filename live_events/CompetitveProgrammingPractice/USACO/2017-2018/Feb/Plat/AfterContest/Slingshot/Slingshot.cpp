#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<ll, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 1e5, M = 1e5, K = 2e5;

int n, m, curidx = 0;
ll seg[4][4 * K], ans[M];
threesome sling[N], q[M];
set<int> allvals;
map<int, int> comp;

void setseg(int segidx, int node, int l, int r, int idx, ll val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[segidx][node] = min(val, seg[segidx][node]);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(segidx, 2 * node, l, mid, idx, val);
    setseg(segidx, 2 * node + 1, mid + 1, r, idx, val);
    seg[segidx][node] = min(seg[segidx][2 * node], seg[segidx][2 * node + 1]);
    return;
}

ll getseg(int segidx, int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 1e18;
    if (l >= a and r <= b) return seg[segidx][node];
    int mid = l + (r - l) / 2;
    return min(getseg(segidx, 2 * node, l, mid, a, b), getseg(segidx, 2 * node + 1, mid + 1, r, a, b));
}

int main() {
    freopen("slingshot.in", "r", stdin);
    freopen("slingshot.out", "w", stdout);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 * K; j++) seg[i][j] = 1e18;
    }

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> sling[i].first >> sling[i].sec >> sling[i].third;
        allvals.insert(sling[i].sec);
    }
    for (int i = 0; i < m; i++) {
        cin >> q[i].first >> q[i].sec;
        q[i].third = i;
        allvals.insert(q[i].sec);
        ans[i] = abs(q[i].first - q[i].sec);
    }

    sort(sling, sling + n);
    sort(q, q + m);

    for (int i : allvals) comp[i] = comp.size();

    for (int i = 0; i < m; i++) {
        while (curidx < n and sling[curidx].first < q[i].first) {
            setseg(0, 1, 0, comp.size() - 1, comp[sling[curidx].sec], sling[curidx].third - sling[curidx].first - sling[curidx].sec);
            setseg(1, 1, 0, comp.size() - 1, comp[sling[curidx].sec], sling[curidx].third - sling[curidx].first + sling[curidx].sec);
            curidx++;
        }
        ans[q[i].third] = min({q[i].first + q[i].sec + getseg(0, 1, 0, comp.size() - 1, 0, comp[q[i].sec]), q[i].first - q[i].sec + getseg(1, 1, 0, comp.size() - 1, comp[q[i].sec], comp.size() - 1), ans[q[i].third]});
    }

    int curidx = n - 1;
    for (int i = m - 1; i >= 0; i--) {
        while (curidx >= 0 and sling[curidx].first > q[i].first) {
            setseg(2, 1, 0, comp.size() - 1, comp[sling[curidx].sec], sling[curidx].third + sling[curidx].first - sling[curidx].sec);
            setseg(3, 1, 0, comp.size() - 1, comp[sling[curidx].sec], sling[curidx].third + sling[curidx].first + sling[curidx].sec);
            curidx--;
        }
        ans[q[i].third] = min({-q[i].first + q[i].sec + getseg(2, 1, 0, comp.size() - 1, 0, comp[q[i].sec]), -q[i].first - q[i].sec + getseg(3, 1, 0, comp.size() - 1, comp[q[i].sec], comp.size() - 1), ans[q[i].third]});
    }

    for (int i = 0; i < m; i++) cout << ans[i] << "\n";

	return 0;
}
