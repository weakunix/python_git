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

const int N = 5e4;

int n, dp1[N], dp2[N]; //dp1 choose, dp2 no choose
vector<int> adj[N];

void dfs(int node, int parent) {
    dp1[node] = 1;
    dp2[node] = 0;
    for (int i : adj[node]) {
        if (i == parent) continue;
        dfs(i, node);
        dp1[node] += dp2[i];
        dp2[node] += max(dp1[i], dp2[i]);
    }
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);

    cout << max(dp1[0], dp2[0]) << "\n";

	return 0;
}
