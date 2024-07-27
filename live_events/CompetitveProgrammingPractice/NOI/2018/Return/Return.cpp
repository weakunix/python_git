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

const int N = 2e5, M = 4e5, L = 18;

int t, n, m, q, k, s, dist[N], dsu[2 * N], par[2 * N][L];
simps krt[2 * N];
threesome edges[M];
vector<simps> adj[N];

void dijk() {
    clr(dist, -1);

    priority_queue<simps, vector<simps>, greater<simps>> pq;
    pq.push({0, 0});

    while (pq.size()) {
        int node = pq.top().second, curd = pq.top().first;
        pq.pop();

        if (dist[node] != -1) continue;
        dist[node] = curd;

        for (simps& s : adj[node]) {
            if (dist[s.first] != -1) continue;
            pq.push({curd + s.second, s.first});
        }
    }

    return;
}

int getdsu(int node) {
    if (dsu[node] == -1) return node;
    dsu[node] = getdsu(dsu[node]);
    return dsu[node];
}

void genkrt() {
    clr(dsu, -1);
    clr(par, -1);
    for (int i = 0; i < n; i++) krt[i] = {dist[i], 2e9};

    int cnt = n;
    for (int i = m - 1; i >= 0; i--) {
        int u = edges[i].sec, v = edges[i].third, a = edges[i].first;
        u = getdsu(u); v = getdsu(v);
        if (u == v) continue;
        dsu[u] = cnt;
        dsu[v] = cnt;
        par[u][0] = cnt;
        par[v][0] = cnt;
        krt[cnt] = {min(krt[u].first, krt[v].first), a};
        cnt++;
    }

    for (int i = 1; i < L; i++) {
        for (int j = 0; j < cnt; j++) {
            int cur = par[j][i - 1];
            if (cur != -1) cur = par[cur][i - 1];
            par[j][i] = cur;
        }
    }

    return;
}

void subcase() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) adj[i].clear();
    for (int i = 0; i < m; i++) {
        int u, v, l, a;
        cin >> u >> v >> l >> a;
        u--; v--;
        adj[u].pb({v, l});
        adj[v].pb({u, l});
        edges[i] = {a, {u, v}};
    }

    sort(edges, edges + m);
    dijk();
    genkrt();

    cin >> q >> k >> s;
    
    int ans = 0;
    for (int i = 0; i < q; i++) {
        int v, p;
        cin >> v >> p;
        v = (v + k * ans - 1) % n;
        p = (p + k * ans) % (s + 1);

        for (int i = L - 1; i >= 0; i--) {
            int nxt = par[v][i];
            if (nxt == -1 or krt[nxt].second <= p) continue;
            v = nxt;
        }
        
        ans = krt[v].first;
        cout << ans << "\n";
    }

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
