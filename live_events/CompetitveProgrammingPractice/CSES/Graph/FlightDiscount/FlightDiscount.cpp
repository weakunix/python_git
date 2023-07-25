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
typedef pair<ll, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, m;
ll ans = 1e18;
vector<ll> dist1, distn;
vector<threesome> edges;
vector<vector<simps>> adj, revadj;
priority_queue<simps> pq;

int main() {
    cin >> n >> m;
    dist1.resize(n, -1);
    distn.resize(n, -1);
    edges.resize(m);
    adj.resize(n);
    revadj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        edges[i] = {a, {b, c}};
        adj[a].push_back({b, c});
        revadj[b].push_back({a, c});
    }
    pq.push({0, 0});
    while (not pq.empty()) {
        int cur = pq.top().second;
        ll curdist = pq.top().first;
        pq.pop();
        if (dist1[cur] != -1) continue;
        dist1[cur] = -curdist;
        for (simps s : adj[cur]) pq.push({curdist - s.second, s.first});
    }
    pq.push({0, n - 1});
    while (not pq.empty()) {
        int cur = pq.top().second;
        ll curdist = pq.top().first;
        pq.pop();
        if (distn[cur] != -1) continue;
        distn[cur] = -curdist;
        for (simps s : revadj[cur]) pq.push({curdist - s.second, s.first});
    }
    for (threesome t : edges) {
        if (dist1[t.first] == -1 or distn[t.sec] == -1) continue;
        ans = min(dist1[t.first] + distn[t.sec] + t.third / 2, ans);
    }
    cout << ans << "\n";
	return 0;
}
