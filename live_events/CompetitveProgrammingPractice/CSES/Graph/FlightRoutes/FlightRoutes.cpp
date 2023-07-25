#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, m, k;
vector<vector<ll>> ans;
vector<vector<simps>> adj;
priority_queue<simps> pq;

int main() {
    cin >> n >> m >> k;
    ans.resize(n);
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
    }
    pq.push({0, 0});
    while (not pq.empty()) {
        int node = pq.top().second;
        ll dist = pq.top().first;
        pq.pop();
        if (ans[node].size() == k) continue;
        ans[node].push_back(-dist);
        for (simps s : adj[node]) pq.push({dist - s.second, s.first});
    }
    assert(ans[n - 1].size() == k);
    for (ll i : ans[n - 1]) cout << i << " ";
    cout << "\n";
	return 0;
}
