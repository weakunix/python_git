#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

const int M = 1e5 + 1;

int t, n, m, k, d, prv;
ll seg[4 * M], lz[4 * M], ans = 0;
vector<int> idx;
set<int> allvals;
map<int, int> comp;
map<int, ll> prvans;
map<int, vector<simps>> upd;

void prop(int node, int l, int r) {
    if (lz[node] == 0) return;
    if (l < r) {
        lz[2 * node] += lz[node];
        lz[2 * node + 1] += lz[node];
    }
    seg[node] += lz[node];
    lz[node] = 0;
    return;
}

void setseg(int node, int l, int r, int a, int b, ll change) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lz[node] += change;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, change);
    setseg(2 * node + 1, mid + 1, r, a, b, change);
    seg[node] = max(seg[2 * node], seg[2 * node + 1]);
    return;
}

ll getseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return max(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

void subcase() {
    prv = 0;
    ans = 0;
    memset(seg, 0, sizeof(seg));
    memset(lz, 0, sizeof(lz));
    idx.clear();
    allvals.clear();
    prvans.clear();
    comp.clear();
    upd.clear();

    cin >> n >> m >> k >> d;
    for (int i = 0; i < m; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        upd[x].push_back({x - y + 1, v});
        allvals.insert(x - y + 1);
    }

    m = allvals.size();

    for (int i : allvals) {
        comp[i] = comp.size();
        idx.push_back(i);
        setseg(1, 0, m - 1, comp[i], comp[i], (ll) (i - 1) * d);
    }

    for (auto& u : upd) {
        setseg(1, 0, m - 1, 0, m - 1, (ll) (u.first - prv) * -d);
        for (simps s : u.second) setseg(1, 0, m - 1, 0, comp[s.first], s.second);
        ll cur = getseg(1, 0, m - 1, lower_bound(all(idx), u.first - k + 1) - idx.begin(), (upper_bound(all(idx), u.first) - idx.begin()) - 1);
        auto it = prvans.lower_bound(u.first - k);
        if (it != prvans.begin()) {
            it--;
            cur += it->second;
        }
        ans = max(cur, ans);
        if (prvans.size()) {
            it = prvans.end();
            it--;
        }
        if (prvans.empty() or it->second < cur) prvans[u.first] = cur;
        prv = u.first;
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    //freopen("run.in", "r", stdin);
    //freopen("run.out", "w", stdout);

	cin >> t >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
