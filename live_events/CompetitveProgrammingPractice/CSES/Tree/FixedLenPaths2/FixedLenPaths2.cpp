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

const int N = 2e5, K = 2e5 + 1;

int n, k1, k2, sub[N];
ll ans = 0, bit[K], cnt[K], curcnt[K];
bool visited[N];
vector<int> adj[N];

void set(int idx, ll change) {
    cnt[idx] += change;
    for (; idx < k2; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll get(int idx) {
    ll res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

int dfs1(int node, int par) {
    sub[node] = 1;
    for (int i : adj[node]) {
        if (visited[i] or i == par) continue;
        sub[node] += dfs1(i, node);
    }
    return sub[node];
}

int dfs2(int node, int par, int ht) {
    ans += (ht >= k1 and ht <= k2);
    if (ht >= k2) return -1;
    int mxdep = ht;
    ans += get(k2 - ht) - get(k1 - 1 - ht);
    curcnt[ht]++;
    for (int i : adj[node]) {
        if (visited[i] or i == par) continue;
        mxdep = max(dfs2(i, node, ht + 1), mxdep);
    }
    return mxdep;
}

int findcentroid(int node, int par, int tar) {
    for (int i : adj[node]) {
        if (visited[i] or i == par) continue;
        if (sub[i] > tar) return findcentroid(i, node, tar);
    }
    return node;
}

void centroiddecomp(int rt) {
    int mxdep = 0;
    if (dfs1(rt, -1) < k1) return;
    rt = findcentroid(rt, -1, sub[rt] / 2);
    visited[rt] = true;
    for (int i : adj[rt]) {
        if (visited[i]) continue;
        mxdep = max(dfs2(i, -1, 1), mxdep);
        for (int j = 1; j <= mxdep and curcnt[j] > 0; j++) {
            set(j, curcnt[j]);
            curcnt[j] = 0;
        }
    }
    for (int i = 1; i <= mxdep; i++) set(i, -cnt[i]);
    for (int i : adj[rt]) {
        if (visited[i]) continue;
        centroiddecomp(i);
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    memset(visited, false, sizeof(visited));

    cin >> n >> k1 >> k2;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    centroiddecomp(0);
    cout << ans << "\n";
	return 0;
}
