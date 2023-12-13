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

const int N = 1e5;

int n, m, best[N], ban[N];
vector<simps> adj[N];

int calc(int tar) {
    fill(best, best + n, 1e9);
    priority_queue<simps> pq;
    best[0] = 0;
    pq.push({0, 0});
    while (not pq.empty()) {
        int node = pq.top().second, dist = -pq.top().first;
        pq.pop();
        for (simps s : adj[node]) {
            if (s.first == tar and node == ban[s.first]) continue;
            if (dist + s.second < best[s.first]) {
                best[s.first] = dist + s.second;
                pq.push({-best[s.first], s.first});
            }
        }
    }
    return best[tar];
}

int main() {
    fill(best, best + N, 1e9);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    priority_queue<simps> pq;
    best[0] = 0;
    pq.push({0, 0});
    while (not pq.empty()) {
        int node = pq.top().second, dist = -pq.top().first;
        pq.pop();
        for (simps s : adj[node]) {
            if (dist + s.second < best[s.first]) {
                best[s.first] = dist + s.second;
                pq.push({-best[s.first], s.first});
                ban[s.first] = node;
            }
        }
    }

    for (int i = 1; i < n; i++) cout << calc(i) << "\n";

	return 0;
}
