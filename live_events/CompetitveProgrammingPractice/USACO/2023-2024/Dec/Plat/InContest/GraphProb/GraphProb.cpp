#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 2e5, modval = 1e9 + 7;

int n, m, par[N];
bool vis[N];
vector<simps> adj[N];

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

bool merge(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    if (a == b) return false;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return true;
}

ll calc(int st) {
    memset(vis, false, sizeof(vis));
    vis[st] = true;

    ll ans = 0;
    priority_queue<simps> pq;

    for (simps s : adj[st]) pq.push(s);

    while (not pq.empty()) {
        int node = pq.top().second, w = -pq.top().first;
        pq.pop();
        if (vis[node]) continue;
        vis[node] = true;
        ans = (10 * ans + w) % modval;
        for (simps s : adj[node]) if (not vis[s.second]) pq.push(s);
    }

    return ans;
}

int main() {
    memset(par, -1, sizeof(par));

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (merge(a, b)) {
            adj[a].push_back({-i, b});
            adj[b].push_back({-i, a});
        }
    }

    for (int i = 0; i < n; i++) cout << calc(i) << "\n";

	return 0;
}
