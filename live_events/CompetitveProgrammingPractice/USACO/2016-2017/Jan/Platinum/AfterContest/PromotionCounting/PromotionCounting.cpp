#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int n, curidx = 1;
vector<int> arr, idx, len, bit, ans;
vector<simps> ord;
vector<vector<int>> adj;

void setidx(int idx) {
    while (idx <= n) {
        bit[idx]++;
        idx += idx & (-idx);
    }
    return;
}

int getpfx(int idx) {
    int res = 0;
    while (idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int dfs(int node, int parent) {
    int count = 0;
    idx[node] = curidx;
    curidx++;
    for (int i : adj[node]) {
        if (i != parent) count += dfs(i, node);
    }
    len[node] = count;
    return count + 1;
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    cin >> n;
    arr.resize(n);
    adj.resize(n);
    idx.resize(n);
    len.resize(n);
    bit.resize(n + 1);
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ord.push_back({arr[i], i});
    }
    sort(all(ord));
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    
    dfs(0, -1);

    for (int i = n - 1; i >= 0; i--) {
        int cur = ord[i].second;
        ans[cur] = getpfx(idx[cur] + len[cur]) - getpfx(idx[cur] - 1);
        setidx(idx[cur]);
    }

    for (int i : ans) cout << i << "\n";

	return 0;
}
