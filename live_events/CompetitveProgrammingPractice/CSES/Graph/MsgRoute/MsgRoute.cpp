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
vector<int> visited, ans;
vector<vector<int>> adj;
queue<int> q;

int main() {
    cin >> n >> m;
    visited.resize(n, -1); visited[0] = n;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    q.push(0);
    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == n - 1) {
            ans.push_back(cur);
            while (cur != 0) {
                cur = visited[cur];
                ans.push_back(cur);
            }
            cout << ans.size() << "\n";
            for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] + 1 << " ";
            cout << "\n";
            return 0;
        }
        for (int i : adj[cur]) {
            if (visited[i] != -1) continue;
            visited[i] = cur;
            q.push(i);
        }
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
