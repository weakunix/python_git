#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
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

int n, q, k, ans;
bool inf[N];
vector<int> adj[N];

simps dfs(int node, int parent) {
    int mx = 0, reach = -1;
    for (int i : adj[node]) {
        if (i == parent) continue;
        simps cur = dfs(i, node);
        mx = max(cur.first + 1, mx);
        reach = max(cur.second - 1, reach);
    }

    if (node == 0) {
        ans += (reach < mx);
        return {0, 0};
    }

    if (reach >= mx) mx = -1;
    if (mx == k) {
        ans++;
        mx = -1;
        reach = k;
    }

    return {mx, reach};
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        inf[i] = (c == '1');
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
     }

    cin >> q;
    for (int i = 0; i < q; i++) {
        ans = 0;
        cin >> k;
        dfs(0, -1);
        cout << ans << "\n";
    }

	return 0;
}
