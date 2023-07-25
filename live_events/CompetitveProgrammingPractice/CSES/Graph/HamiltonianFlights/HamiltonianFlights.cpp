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

const int modval = 1e9 + 7;

int n, m, ans = 0;
vector<int> tolast;
vector<vector<int>> adj, dp;

int main() {
    cin >> n >> m;
    n -= 2;
    adj.resize(n);
    dp.resize(1 << n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a -= 2; b -= 2;
        if (a == b) continue;
        if (b == n) {
            if (a == -1) {
                if (n == 0) ans++;
            }
            else tolast.push_back(a);
            continue;
        }
        if (b == -1 or a == n) continue;
        if (a == -1) {
            dp[1 << b][b]++;
            continue;
        }
        adj[a].push_back(b);
    }
    if (n == 0) {
        cout << ans << "\n";
        return 0;
    }
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) == 0) continue;
            for (int k : adj[j]) {
                if (i & (1 << k)) continue;
                dp[i ^ (1 << k)][k] = (dp[i ^ (1 << k)][k] + dp[i][j]) % modval;
            }
        }
    }
    for (int i : tolast) ans = (ans + dp.back()[i]) % modval;
    cout << ans << "\n";
	return 0;
}
