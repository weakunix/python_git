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

int n, m;
vector<int> indeg, dist, prv, ans;
vector<vector<int>> adj;
queue<int> q;

int main() {
    cin >> n >> m;
    indeg.resize(n);
    dist.resize(n, -1); dist[0] = 1;
    prv.resize(n, -1);
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        indeg[b]++;
    }
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    while (not q.empty()) {
        int node = q.front();
        q.pop();
        for (int i : adj[node]) {
            indeg[i]--;
            if (indeg[i] == 0) q.push(i);
            if (dist[node] != -1 and dist[node] + 1 > dist[i]) {
                dist[i] = dist[node] + 1;
                prv[i] = node;
            }
        }
    }
    if (dist[n - 1] == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    int cur = n - 1;
    while (cur != 0) {
        ans.push_back(cur);
        cur = prv[cur];
    }
    cout << dist[n - 1] << "\n" << "1 ";
    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] + 1 << " ";
    cout << "\n";
	return 0;
}
