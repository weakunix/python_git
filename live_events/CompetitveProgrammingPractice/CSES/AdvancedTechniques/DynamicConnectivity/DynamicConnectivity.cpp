#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
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

const int N = 1e5, K = 1e5 + 1;

int n, m, k, par[N], sz[N], ans;
vector<simps> seg[4 * K];
map<simps, int> edges;

void setseg(int node, int l, int r, int a, int b, simps e) {
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        seg[node].push_back(e);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, e);
    setseg(2 * node + 1, mid + 1, r, a, b, e);
    return;
}

int getpar(int node) {
    return node == par[node] ? node : getpar(par[node]);
}

void dfs(int node, int l, int r) {
    vector<simps> stck;

    for (simps s : seg[node]) {
        int a = getpar(s.first), b = getpar(s.second);
        if (a == b) continue;
        if (sz[a] > sz[b]) swap(a, b);
        par[a] = b;
        sz[b] += sz[a];
        ans--;
        stck.push_back({a, b});
    }

    if (l == r) cout << ans << " ";
    else {
        int mid = l + (r - l) / 2;
        dfs(2 * node, l, mid);
        dfs(2 * node + 1, mid + 1, r);
    }

    while (stck.size()) {
        int a = stck.back().first, b = stck.back().second;
        stck.pop_back();
        par[a] = a;
        sz[b] -= sz[a];
        ans++;
    }

    return;
}

int main() {
    for (int i = 0; i < N; i++) {
        par[i] = i;
        sz[i] = 1;
    }

    cin >> n >> m >> k;
    ans = n;
    for (int i = 0; i < m; i++) {
        simps cur;
        cin >> cur.first >> cur.second;
        cur.first--; cur.second--;
        if (cur.first > cur.second) swap(cur.first, cur.second);
        edges[cur] = 0;
    }
    for (int i = 1; i <= k; i++) {
        int t;
        simps cur;
        cin >> t >> cur.first >> cur.second;
        cur.first--; cur.second--;
        if (cur.first > cur.second) swap(cur.first, cur.second);

        if (t == 1) edges[cur] = i;
        else {
            setseg(1, 0, k, edges[cur], i - 1, cur);
            edges.erase(cur);
        }
    }
    for (auto& u : edges) setseg(1, 0, k, u.second, k, u.first);

    dfs(1, 0, k);
    cout << "\n";

	return 0;
}
