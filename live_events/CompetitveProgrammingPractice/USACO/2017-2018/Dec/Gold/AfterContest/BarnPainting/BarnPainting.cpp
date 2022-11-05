#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int modval = 1e9 + 7;
int n, k;
vector<int> color, p, ord;
vector<ll> dp1, dp2, dp3;
vector<vector<int>> adj;

void dfs(int node, int parent) {
    p[node] = parent;
    for (int i : adj[node]) {
        if (i != parent) dfs(i, node);
    }
    ord.push_back(node);
    return;
}

int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);

    cin >> n >> k;
    color.resize(n);
    p.resize(n, -1);
    dp1.resize(n);
    dp2.resize(n);
    dp3.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < k; i++) {
        int b, c;
        cin >> b >> c;
        b--;
        color[b] = c;
    }

    dfs(0, -1);

    for (int i : ord) {
        ll not1 = 1, not2 = 1, not3 = 1;
        for (int j : adj[i]) {
            if (j == p[i]) continue;
            not1 = (not1 * (dp2[j] + dp3[j])) % modval;
            not2 = (not2 * (dp1[j] + dp3[j])) % modval;
            not3 = (not3 * (dp1[j] + dp2[j])) % modval;
        }
        if (color[i] == 0 or color[i] == 1) dp1[i] = not1;
        if (color[i] == 0 or color[i] == 2) dp2[i] = not2;
        if (color[i] == 0 or color[i] == 3) dp3[i] = not3;
    }

    cout << (dp1[0] + dp2[0] + dp3[0]) % modval << "\n";

	return 0;
}
