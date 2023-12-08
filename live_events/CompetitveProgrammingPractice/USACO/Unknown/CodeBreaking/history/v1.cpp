#include <iostream>
#include <cstring>
#include <vector>
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

const int N = 2e4, modval = 1234567;

int n, m, par[N];
ll ans = 1;
vector<int> adj[N];
set<int> invalid[N];

vector<vector<ll>> dp; //bfi

void dfs(int node) {
    for (int i : adj[node]) dfs(i);

    for (int i = 0; i < 1e4; i++) {
        for (int j = 0; j < 10; j++) {
            if (invalid[node].count(j * 1e4 + i)) continue;

            ll cnt = 1;
            for (int k : adj[node]) cnt = cnt * dp[k][1e3 * j + i / 10] % modval;
            dp[node][i] = (dp[node][i] + cnt) % modval;
        }
    }

    return;
}

int main() {
    cin >> n >> m;
    dp.resize(n, vector<ll>(1e4));
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        adj[par[i]].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        invalid[a].insert(b);
    }

    dfs(0);

    for (int i = 0; i < n; i++) ans = ans * 10 % modval;
    cout << (ans + modval - dp[0][0]) % modval << "\n";

	return 0;
}
