#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

int n, k;
ll ans = 0;
vector<int> sub;
vector<ll> cnt;
vector<bool> visited;
vector<vector<int>> adj;
set<int> rem;

int dfs1(int node, int par) {
    sub[node] = 1;
    for (int i : adj[node]) {
        if (visited[i] or i == par) continue;
        sub[node] += dfs1(i, node);
    }
    return sub[node];
}

void dfs2(int node, int par, int ht) {
    if (ht == k) {
        ans++;
        return;
    }
    ans += cnt[k - ht];
    for (int i : adj[node]) {
        if (visited[i] or i == par) continue;
        dfs2(i, node, ht + 1);
    }
    return;
}

void dfs3(int node, int par, int ht) {
    if (ht == k) return;
    cnt[ht]++;
    for (int i : adj[node]) {
        if (visited[i] or i == par) continue;
        dfs3(i, node, ht + 1);
    }
    return;
}

int findcentroid(int rt) {
    int res = rt, prv = -1;
    dfs1(rt, -1);
    while (true) {
        int nxt = -1;
        for (int i : adj[res]) {
            if (visited[i] or i == prv) continue;
            if (sub[i] > sub[rt] / 2) {
                nxt = i;
                break;
            }
        }
        if (nxt == -1) return res;
        prv = res;
        res = nxt;
    }
    assert(false);
    return -1;
}

int main() {
    cin >> n >> k;
    sub.resize(n);
    cnt.resize(k);
    visited.resize(n);
    adj.resize(n);
    for (int i = 0; i < n; i++) rem.insert(i);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    while (rem.size()) {
        int rt = *rem.begin(), cur = findcentroid(rt);
        bool works = (sub[rt] >= k - 1);
        visited[cur] = true;
        rem.erase(cur);
        if (not works) continue;
        for (int i = 0; i < k; i++) cnt[i] = 0;
        for (int i : adj[cur]) {
            if (not visited[i]) dfs2(i, -1, 1);
            if (not visited[i]) dfs3(i, -1, 1);
        }
    }
    cout << ans << "\n";
	return 0;
}
