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
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;
typedef pair<simps, simps> foursome;

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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 1, N2 = 1000;
const simps fail2 = {1e9, -1};
const foursome fail4 = {fail2, fail2};

int t, m, n, lpos[N], rpos[N], upos[N], dpos[N];
bool vis[N];
foursome seg[8 * N];
vector<int> adj[N2], radj[N2];
set<simps> leaves[8 * N];

void updleaf(int node) {
    auto it = leaves[node].begin();
    if (it == leaves[node].end()) {
        seg[node] = fail4;
        return;
    }
    seg[node].first = *it;
    it++;
    if (it == leaves[node].end()) seg[node].second = fail2;
    else seg[node].second = *it;
    return;
}

foursome merge4(foursome a, foursome b) {
    foursome res;
    if (a.first > b.first) swap(a, b);
    res.first = a.first;
    res.second = min(a.second, b.first);
    return res;
}

void setseg(int node, int l, int r, int idx, bool add) { //idx = index of block
    int segidx = lpos[idx];
    if (l > segidx or r < segidx) return;
    if (l == r) {
        if (add) leaves[node].insert({dpos[idx], idx});
        else leaves[node].erase({dpos[idx], idx});
        updleaf(node);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, idx, add);
    setseg(2 * node + 1, mid + 1, r, idx, add);
    seg[node] = merge4(seg[2 * node], seg[2 * node + 1]);
    return;
}

foursome getseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return fail4;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return merge4(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

void solve1(int cur) {
    while (true) {
        foursome res4 = getseg(1, 0, 2 * n, 0, rpos[cur] - 1);
        simps res2 = (res4.first.second == cur ? res4.second : res4.first);

        if (res2.first >= upos[cur]) {
            cout << cur + 1 << " ";
            vis[cur] = true;
            setseg(1, 0, 2 * n, cur, false);
            return;
        }
        solve1(res2.second);
    }

    assert(false);
    return;
}

void subcase() {
    clr(vis, false);
    fill(seg, seg + 8 * N, fail4);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> lpos[i] >> dpos[i] >> rpos[i] >> upos[i];
    
    if (m == 1) {
        for (int i = 0; i < n; i++) setseg(1, 0, 2 * n, i, true);

        for (int i = 0; i < n; i++) if (not vis[i]) solve1(i);

        cout << "\n";
        return;
    }
    else {
        for (int i = 0; i < n; i++) setseg(1, 0, 2 * n, i, true);
        for (int i = 0; i < n; i++) {
            foursome res4 = getseg(1, 0, 2 * n, 0, rpos[i] - 1);
            simps res2 = (res4.first.second == i ? res4.second : res4.first);
            cout << (res2.first >= upos[i]);
            setseg(1, 0, 2 * n, i, false);
        }
        cout << "\n";
    }

    return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> m;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
