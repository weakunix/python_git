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
vector<int> stck, id, ans;
vector<bool> visited;
vector<vector<int>> adj, revadj, scc;

void dfs1(int node) {
    visited[node] = true;
    for (int i : adj[node]) {
        if (not visited[i]) dfs1(i);
    }
    stck.push_back(node);
    return;
}

void dfs2(int node) {
    id[node] = scc.size();
    scc.back().push_back(node);
    for (int i : revadj[node]) {
        if (not id[i]) dfs2(i);
    }
    return;
}

int main() {
    cin >> n >> m;
    id.resize(2 * m);
    ans.resize(m, -1);
    visited.resize(2 * m);
    adj.resize(2 * m);
    revadj.resize(2 * m);
    for (int i = 0; i < n; i++) {
        int a, b, shifta, shiftb;
        char ta, tb;
        cin >> ta >> a >> tb >> b;
        a--; b--;
        if (ta == '-') a += m;
        if (tb == '-') b += m;
        shifta = (a + m) % (2 * m); shiftb = (b + m) % (2 * m);
        adj[shifta].push_back(b);
        adj[shiftb].push_back(a);
        revadj[a].push_back(shiftb);
        revadj[b].push_back(shifta);
    }
    for (int i = 0; i < 2 * m; i++) {
        if (not visited[i]) dfs1(i);
    }
    for (int i = 2 * m - 1; i >= 0; i--) {
        int cur = stck[i];
        if (id[cur]) continue;
        scc.push_back({});
        dfs2(cur);
    }
    for (int i = 0; i < m; i++) {
        if (id[i] == id[i + m]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for (int i = scc.size() - 1; i >= 0; i--) {
        for (int j : scc[i]) {
            int cur = j % m;
            bool selected = (j < m);
            if (ans[cur] == -1) ans[cur] = selected;
        }
    }
    for (int i : ans) cout << (i ? '+' : '-') << " ";
    cout << "\n";
    return 0;
}
