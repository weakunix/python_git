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

const int N = 7e4;

struct SegNode {
    vector<simps> rem;
    set<simps> nodes;

    SegNode() {}

    ~SegNode() {}
};

int n, m, w, h, ans[N];
vector<simps> loc[N];
vector<vector<int>> edges[N];
SegNode seg[4 * N];

void prop(int node, int l, int r) {
    if (l < r) {
        for (simps& s : seg[node].rem) {
            if (seg[2 * node].nodes.count(s)) seg[2 * node].rem.pb(s);
            else seg[2 * node + 1].rem.pb(s);
        }
    }
    for (simps& s : seg[node].rem) seg[node].nodes.erase(s);
    seg[node].rem.clear();
    return;
}

void getseg(int node, int l, int r, int a, int b, int p, int q, vector<simps>& curnodes) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        for (auto it = seg[node].nodes.lb({p, -1}); it != seg[node].nodes.end() and it->first <= q; it++) curnodes.pb(*it);
        return;
    }
    int mid = l + (r - l) / 2;
    getseg(2 * node, l, mid, a, b, p, q, curnodes);
    getseg(2 * node + 1, mid + 1, r, a, b, p, q, curnodes);
    return;
}

void buildseg(int node, int l, int r) {
    for (int i = l; i <= r; i++) for (simps s : loc[i]) seg[node].nodes.insert(s);
    if (l == r) return;
    int mid = l + (r - l) / 2;
    buildseg(2 * node, l, mid);
    buildseg(2 * node + 1, mid + 1, r);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n >> m >> w >> h;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (i) loc[y].pb({x, i});
    }
    for (int i = 0; i < m; i++) {
        int p, t, l, r, d, u;
        cin >> p >> t >> l >> r >> d >> u;
        p--; l--; r--; d--; u--;
        edges[p].pb({t, l, r, d, u});
    }

    buildseg(1, 0, n - 1);

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    for (vector<int> v : edges[0]) pq.push(v);

    while (pq.size()) {
        vector<int> cur = pq.top();
        pq.pop();

        vector<simps> curnodes;
        getseg(1, 0, n - 1, cur[3], cur[4], cur[1], cur[2], curnodes);
        
        for (simps& s : curnodes) {
            ans[s.second] = cur[0];
            for (vector<int> v : edges[s.second]) {
                v[0] += cur[0];
                pq.push(v);
            }
            seg[1].rem.pb(s);
        }
    }

    for (int i = 1; i < n; i++) cout << ans[i] << "\n";

	return 0;
}
