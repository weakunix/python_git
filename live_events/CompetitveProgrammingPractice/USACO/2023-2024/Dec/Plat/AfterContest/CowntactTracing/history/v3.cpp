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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a);
    return;
}

const int N = 1000; //BFI only

int n, q, k, dist[N];
ll dp1[N][N], dp2[N][N];
vector<int> adj[N];
queue<int> qu;

void dbg(int node) {
    cout << node << "\n";
    for (int i = 0; i <= k; i++) cout << dp1[node][i] << " ";
    cout << "\n";
    for (int i = 0; i <= k; i++) cout << dp2[node][i] << " ";
    cout << "\n";
}

void dfs(int node, int parent) {
    ll sm[N], mn[N], rtsm = 0;
    bool leaf = true;

    fill(dp1[node], dp1[node] + k + 1, 1e9); //dp1 domain: [0, k]
    fill(dp2[node], dp2[node] + k + 1, 1e9); //dp2 domain: [0, k]
    memset(sm, 0, sizeof(sm));
    fill(mn, mn + k, 1e9);

    for (int i : adj[node]) {
        if (i == parent) continue;
        leaf = false;
        dfs(i, node);
        rtsm += dp2[i][0];

        for (int j = 0; j <= k; j++) {
            sm[j] += dp1[i][j];
            if (j < k) setmn(mn[j], dp2[i][j + 1] - dp1[i][j]);
        }
    }

    if (not dist[node]) { //not infected
        if (leaf) { //base case
            dp1[node][0] = 0;
            dp2[node][0] = 0;
            return;
        }

        setmn(dp1[node][0], rtsm);
        setmn(dp2[node][0], rtsm);

        return;
    }

    //infected
    if (leaf) { //base case
        if (dist[node] != 1e9) fill(dp1[node] + 1, dp1[node] + dist[node] + 1, 0);
        else memset(dp1[node], 0, sizeof(dp1[node]));
        
        if (dist[node] > k) {
            dp1[node][0] = 1;
            dp2[node][k] = 1;
        }
        else dp1[node][0] = 1e9;

        return;
    }
    
    ll best = 1e9;
    for (int i = k; i > 0; i--) { //dp1, a > 0
        if (dist[node] < i) continue;

        setmn(dp1[node][i], sm[i - 1]);
        if (dist[node] > k) setmn(dp1[node][i], sm[k] + 1);
        setmn(dp1[node][i], best);

        if (dist[node] > i - 1) setmn(best, sm[i - 1] + mn[i - 1]);
    }

    for (int i = 0; i < k; i++) { //dp2, a < k, no root
        if (dist[node] < i) continue;
        setmn(dp2[node][i], sm[i] + mn[i]);
    }
    
    if (dist[node] > k) setmn(dp2[node][k], sm[k] + 1); //dp2, a = k, with root

    for (int i = 0; i <= k; i++) setmn(dp1[node][0], dp2[node][i]); //dp1, a = 0
    
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '0') {
            dist[i] = 0;
            qu.push(i);
        }
        else dist[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (qu.empty()) fill(dist, dist + n, 1e9);

    while (qu.size()) {
        int node = qu.front();
        qu.pop();

        for (int i : adj[node]) {
            if (dist[i] != -1) continue;
            dist[i] = dist[node] + 1;
            qu.push(i);
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> k;
        dfs(0, -1);

        ll ans = 1e9;
        for (int i = 0; i <= k; i++) setmn(ans, dp2[0][i]);
        cout << (ans == 1e9 ? -1 : ans) << "\n";
    }

	return 0;
}
