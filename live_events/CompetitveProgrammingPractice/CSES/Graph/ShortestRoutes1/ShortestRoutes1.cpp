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

int n, m;
vector<ll> dist;
vector<vector<simps>> adj;
priority_queue<simps> pq;

int main() {
    cin >> n >> m;
    dist.resize(n, 1e14);
    adj.resize(n);
    pq.push({0, 0});
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a - 1].push_back({b - 1, c});
    }
    while (not pq.empty()) {
        int cur = pq.top().second;
        ll curdist = pq.top().first;
        pq.pop();
        if (dist[cur] != 1e14) continue;
        dist[cur] = -curdist;
        for (simps s : adj[cur]) pq.push({curdist - s.second, s.first});
    }
    for (ll i : dist) cout << i << " ";
    cout << "\n";
	return 0;
}
