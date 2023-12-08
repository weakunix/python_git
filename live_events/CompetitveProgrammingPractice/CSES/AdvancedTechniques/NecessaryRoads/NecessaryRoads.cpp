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

const int N = 1e5;

int n, m, ht[N], hi[N];
vector<int> adj[N];
vector<simps> ans;

int dfs(int node, int parent, int height) {
    ht[node] = height;
    hi[node] = height;

    for (int i : adj[node]) {
        if (ht[i] == -1) {
            hi[node] = min(dfs(i, node, height + 1), hi[node]);
            if (hi[i] > height) ans.push_back({node, i});
        }
        else if (i != parent) hi[node] = min(ht[i], hi[node]);
    }

    return hi[node];
}

int main() {
    memset(ht, -1, sizeof(ht));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1, 0);

    cout << ans.size() << "\n";
    for (simps& s : ans) cout << s.first + 1 << " " << s.second + 1 << "\n";

	return 0;
}
