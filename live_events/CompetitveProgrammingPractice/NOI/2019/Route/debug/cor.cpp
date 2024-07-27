#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 1e5, M = 2e5;

int n, m, a, b, c;
ll ans = 1e18;
vector<int> edges[M];
map<int, ll> dp[N];

int main() {
    cin >> n >> m >> a >> b >> c;
    for (int i = 0; i < m; i++) {
        int u, v, p, q;
        cin >> u >> v >> p >> q;
        edges[i] = {p, q, u - 1, v - 1};
    }
    sort(edges, edges + m);

    dp[0][0] = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i][2], v = edges[i][3], p = edges[i][0], q = edges[i][1];
        for (auto& j : dp[u]) {
            if (j.first > p) break;
            if (not dp[v].count(q)) dp[v][q] = 1e18;
            setmn(dp[v][q], j.second + a * (p - j.first) * (p - j.first) + b * (p- j.first) + c);
        }
    }

    for (auto& u : dp[n - 1]) setmn(ans, u.second + u.first);

    cout << ans << "\n";

	return 0;
}
