#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<simps, simps> foursome;

#define fir first.first
#define sec first.second
#define third second.first
#define fourth second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int modval = 1e9 + 7;

int n, m;
vector<bool> visited;
vector<foursome> ans;
vector<vector<simps>> adj;
priority_queue<simps> pq;

int main() {
    cin >> n >> m;
    visited.resize(n);
    ans.resize(n, {{1e18, -1}, {-1, -1}}); ans[0] = {{0, 1}, {0, 0}};
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
        ll dist = -pq.top().first;
        pq.pop();
        if (visited[node]) continue;
        assert(ans[node].fir == dist);
        visited[node] = true;
        for (simps s : adj[node]) {
            if (dist + s.second < ans[s.first].fir) {
                ans[s.first] = {{dist + s.second, 0}, {n, 0}};
                pq.push({-ans[s.first].fir, s.first});
            }
            if (dist + s.second == ans[s.first].fir) {
                ans[s.first].sec = (ans[s.first].sec + ans[node].sec) % modval;
                ans[s.first].third = min(ans[node].third + 1, ans[s.first].third);
                ans[s.first].fourth = max(ans[node].fourth + 1, ans[s.first].fourth);
            }
        }
    }
    cout << ans[n - 1].fir << " " << ans[n - 1].sec << " " << ans[n - 1].third << " " << ans[n - 1].fourth << "\n";
	return 0;
}
