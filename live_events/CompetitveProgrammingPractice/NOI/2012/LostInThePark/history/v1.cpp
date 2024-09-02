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

const int N = 1e5;

int n, m, deg[N];
double s[N], ans = 0;
vector<simps> adj[N];
map<int, double> sk[N], ak[N];

double dfs1(int node, int parent) {
    int cnt = deg[node] - (parent != -1);

    if (cnt == 0) {
        s[node] = 0;
        return 0;
    }

    double sm = 0;
    for (simps& i : adj[node]) {
        if (i.first == parent) continue;
        sm += dfs1(i.first, node) + i.second;
    }

    s[node] = sm / cnt;
    for (simps& i : adj[node]) {
        if (i.first == parent) continue;
        if (cnt == 1) sk[node][i.first] = 0;
        else sk[node][i.first] = (sm - s[i.first] - i.second) / (cnt - 1);
    }

    return s[node];
}

void dfs2(int node, int parent, int w) {
    if (parent == -1) {
        ans += s[node];
        for (simps& i : adj[node]) ak[node][i.first] = sk[node][i.first];
    }
    else {
        ans += s[node] * (deg[node] - 1) / deg[node] + (ak[parent][node] + w) / deg[node];
        if (deg[node] > 1) for (simps& i : adj[node]) ak[node][i.first] = sk[node][i.first] * (deg[node] - 2) / (deg[node] - 1) + (ak[parent][node] + w) / (deg[node] - 1);
    }

    for (simps& i : adj[node]) if (i.first != parent) dfs2(i.first, node, i.second);

    return;
}

int main() {
    clr(deg, 0);

    cin >> n >> m;
    assert(m == n - 1); //FIXME
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        deg[u]++;
        deg[v]++;
    }

    dfs1(0, -1);
    dfs2(0, -1, -1);

    cout << ans / n << "\n";

	return 0;
}
