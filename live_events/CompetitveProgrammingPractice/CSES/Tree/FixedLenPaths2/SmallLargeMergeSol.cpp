#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
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

int n, k1, k2;
ll ans = 0;
vector<vector<int>> adj;
vector<deque<ll>> pfx;

ll get(deque<ll>& d, int idx) {
    if (idx < 0) return d[0];
    if (idx >= d.size()) return 0;
    return d[idx];
}

void mergepfx(deque<ll>& a, deque<ll>& b) {
    if (a.size() < b.size()) swap(a, b);
    for (int i = 0; i < b.size(); i++) {
        ll cur = b[i] - (i == b.size() - 1 ? 0 : b[i + 1]);
        if (i > k2) break;
        if ((get(a, k1 - i) - get(a, k2 - i + 1)) < 0) {
            cout << "blah\n";
            cout << get(a, k1 - i) << " " << get(a, k2 - i + 1) << "\n";
            cout << k1 - i << " " << k2 - i + 1 << "\n";
            assert(false);
        }
        ans += cur * (get(a, k1 - i) - get(a, k2 - i + 1));
    }
    for (int i = 0; i < b.size(); i++) a[i] += b[i];
    return;
}

void dfs(int node, int par) {
    for (int i : adj[node]) {
        if (i == par) continue;
        dfs(i, node);
        pfx[i].push_front(pfx[i].front());
        mergepfx(pfx[node], pfx[i]);
    }
}

int main() {
    cin >> n >> k1 >> k2;
    adj.resize(n);
    pfx.resize(n, {1});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    cout << ans << "\n";
	return 0;
}
