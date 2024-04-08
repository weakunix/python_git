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

const int N = 5e5, M = 1e6 + 1, modval = 1e9 + 7;

int n, m, hi[N], ht[N], ncnt[N], bcnt = 0;
ll pw[M], dp1[N], dp2[N], ans = 0;
bool vis[N];
simps edge[M];
vector<int> adj[N], bccadj[N];

ll getpw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

void dfs1(int node, int parent, int height) {
    hi[node] = node;
    ht[node] = height;
    for (int i : adj[node]) {
        if (ht[i] != -1) {
            if (i != parent and ht[hi[node]] > ht[i]) hi[node] = i;
            continue;
        }
        dfs1(i, node, height + 1);
        if (ht[hi[node]] > ht[hi[i]]) hi[node] = hi[i];
    }
    return;
}

void dfs2(int node, int parent) {
    vis[node] = true;
    if (parent != -1 and hi[node] != node) hi[node] = hi[parent];
    ncnt[hi[node]]++;
    for (int i : adj[node]) {
        if (not vis[i]) dfs2(i, node);
    }
    return;
}

int dfs3(int node, int parent) {
    int cnt = 0;
    ll prod2 = 1, prodtot = 1;

    for (int i : bccadj[node]) {
        if (i == parent) continue;
        cnt += dfs3(i, node);
        prod2 = prod2 * dp2[i] % modval;
        prodtot = prodtot * (dp1[i] + dp2[i]) % modval;
    }

    ans = (ans + prodtot * (pw[ncnt[node]] - 1) % modval * pw[bcnt - cnt] % modval) % modval;
    ans = (ans + prodtot * pw[bcnt - cnt] % modval) % modval;
    ans = (ans + modval - prod2 * pw[bcnt - cnt] % modval) % modval;
    for (int i : bccadj[node]) if (i != parent) ans = (ans + modval - prod2 * getpw(dp2[i], modval - 2) % modval * dp1[i] % modval * pw[bcnt - cnt] % modval) % modval;

    dp1[node] = (prodtot + modval - prod2) % modval * pw[ncnt[node]] % modval;
    dp1[node] = (dp1[node] + prod2 * (pw[ncnt[node]] - 1) % modval) % modval;

    dp2[node] = pw[cnt + 1];

    return cnt + 1;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < M; i++) pw[i] = 2 * pw[i - 1] % modval;

    clr(hi, -1);
    clr(ht, -1);
    clr(ncnt, 0);
    clr(vis, false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edge[i] = {a, b};
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs1(0, -1, 0);
    dfs2(0, -1);

    for (int i = 0; i < m; i++) {
        int a = hi[edge[i].first], b = hi[edge[i].second];
        if (a != b) {
            bccadj[a].pb(b);
            bccadj[b].pb(a);
            bcnt++;
        }
    }

    dfs3(0, -1);

    cout << ans * pw[m - bcnt] % modval << "\n";

	return 0;
}
