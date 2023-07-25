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

const simps fail = {-1, -1};

int n, m;
vector<int> visited;
vector<vector<int>> adj;

simps dfs(int node, int from) {
    visited[node] = from;
    for (int i : adj[node]) {
        if (i == from) continue;
        if (visited[i] != -1) return {node, i};
        simps cur = dfs(i, node);
        if (cur != fail) return cur;
    }
    return fail;
}

int main() {
    cin >> n >> m;
    visited.resize(n, -1);
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (visited[i] != -1) continue;
        simps cur = dfs(i, n);
        if (cur == fail) continue;
        int last = -1;
        vector<int> ans1, ans2;
        for (int j = cur.first; j != n; j = visited[j]) ans1.push_back(j);
        for (int j = cur.second; j != n; j = visited[j]) ans2.push_back(j);
        while (ans1.back() == ans2.back()) {
            last = ans1.back();
            ans1.pop_back();
            ans2.pop_back();
        }
        cout << ans1.size() + ans2.size() + 2 << "\n";
        for (int i : ans1) cout << i + 1 << " ";
        cout << last + 1 << " ";
        for (int i = ans2.size() - 1; i >= 0; i--) cout << ans2[i] + 1 << " ";
        cout << ans1[0] + 1 << "\n";
        return 0;
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
