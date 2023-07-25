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

int n, m;
vector<ll> dist;
vector<bool> visited, cycle;
vector<threesome> edges;
vector<vector<int>> revadj;

void dfs(int node) {
    visited[node] = true;
    for (int i : revadj[node]) {
        if (not visited[i]) dfs(i);
    }
    return;
}

int main() {
    cin >> n >> m;
    dist.resize(n, -1e18); dist[0] = 0;
    visited.resize(n);
    cycle.resize(n);
    edges.resize(m);
    revadj.resize(n);
    for (threesome& t : edges) {
        cin >> t.first >> t.sec >> t.third;
        t.first--;
        t.sec--;
        revadj[t.sec].push_back(t.first);
    }
    dfs(n - 1);
    for (int i = 0; i < n - 1; i++) {
        for (threesome& t : edges) {
            if (dist[t.first] == -1e18) continue;
            dist[t.sec] = max(dist[t.first] + t.third, dist[t.sec]);
        }
    }
    for (threesome& t : edges) {
        if (dist[t.first] == -1e18) continue;
        if (dist[t.first] + t.third > dist[t.sec]) cycle[t.sec] = true;
    }
    for (int i = 0; i < n; i++) {
        if (visited[i] and cycle[i]) {
            cout << "-1\n";
            return 0;
        }
    }
    cout << dist[n - 1] << "\n";
	return 0;
}
