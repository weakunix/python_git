#include <iostream>
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

const int N = 1e4 + 5, modval = 1e9 + 7;
ll fact[N];

/*
bck: back edge
tp: top of the cycle
und: cycles under i (i.e. with i as top)

p: prob to finish at i
v: prob 1 -> i
e: prob escape subcactus of i
ec: prob escape cycle i
r: prob i -> j with prv(j) = i
b: prob of taking said bridge
c: prob of entering said cycle
*/

int t, n, m, par[N], ht[N], deg[N], bck[N], tp[N];
ll p[N], v[N], e[N], ec[N], b[N], c[N], ans[N];
vector<int> adj[N], und[N];
map<int, ll> r[N];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

void dfs1(int node, int parent, int height) {
    par[node] = parent;
    ht[node] = height;

    for (int i : adj[node]) {
        if (ht[i] == -1) {
            dfs1(i, node, height + 1);
            continue;
        }

        if (i == parent or ht[i] > height) continue;

        assert(bck[node] == -1); //ASSERT
        bck[node] = i;
        int cur = node;
        while (cur != i) {
            assert(tp[cur] == -1); //ASSERT
            tp[cur] = i;
            cur = par[cur];
        }
        und[i].pb(node);
    }
    return;
}

void dfs2(int node) {
    for (int i : adj[node]) if (ht[i] == ht[node] + 1) dfs2(i);
    if (not deg[node]) return;

    for (int i : und[node]) {
        int curnode = i;
        ec[i] = 1;
        while (curnode != node) {
            ec[i] = ec[i] * e[curnode] % modval;
            curnode = par[curnode];
        }
    }

    int cnt = und[node].size();

    for (int i = 0; i < (1 << cnt); i++) {
        int k = __builtin_popcount(i);
        ll cur = fact[k] * pw(modval + 1 - p[node], k + 1) % modval * pw(2, k) % modval;
        for (int j = 0; j <= k; j++) cur = cur * pw(deg[node] - 2 * j, modval - 2) % modval;
        for (int j = 0; j < cnt; j++) if (i & (1 << j)) cur = cur * ec[und[node][j]] % modval;

        b[node] = (b[node] + cur) % modval;
        for (int j = 0; j < cnt; j++) if (not (i & (1 << j))) c[und[node][j]] = (c[und[node][j]] + cur) % modval;
    }

    if (tp[node] != -1) e[node] = b[node];

    return;
}

void dfs3(int node) {
    if (node and tp[node] == -1) r[par[node]][node] = b[par[node]]; //if par->node is a bridge
    for (int i : und[node]) { //if node is in a cycle
        int curnode = i;
        ll curp = c[i];
        vector<int> stck;
        while (curnode != node) {
            stck.pb(curnode);
            r[node][curnode] = curp;
            curp = curp * e[curnode] % modval;
            curnode = par[curnode];
        }

        curp = c[i];
        while (stck.size()) {
            curnode = stck.back();
            stck.bp();
            r[node][curnode] = (r[node][curnode] + curp) % modval;
            curp = curp * e[curnode] % modval;
        }
    }
    for (int i : adj[node]) if (ht[i] == ht[node] + 1) dfs3(i);
    return;
}

void dfs4(int node) {
    if (node) {
        if (tp[node] == -1) v[node] = v[par[node]] * r[par[node]][node] % modval; //if par->node is a bridge
        else v[node] = v[tp[node]] * r[tp[node]][node] % modval; //if node is in a cycle
    }
    ans[node] = modval + 1 - e[node];
    for (auto& u : r[node]) ans[node] = (ans[node] + modval - u.second * (modval + 1 - e[u.first]) % modval) % modval;
    ans[node] = ans[node] * v[node] % modval;
    for (int i : adj[node]) if (ht[i] == ht[node] + 1) dfs4(i);
    return;
}

void subcase() {
    clr(par, -1);
    clr(ht, -1);
    clr(deg, -1);
    deg[0] = 0;
    clr(bck, -1);
    clr(tp, -1);
    clr(b, 0);
    clr(c, 0);
    clr(e, 0);
    v[0] = 1;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        adj[i].clear();
        und[i].clear();
        r[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        deg[a]++;
        deg[b]++;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs1(0, -1, 0); //bck, tp, und
    dfs2(0); //b, c, e, ec
    dfs3(0); //r
    dfs4(0); //v

    for (int i = 0; i < n; i++) cout << ans[i] << (i == n - 1 ? "\n" : " ");

	return;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);

    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;

	cin >> t;

	for (int i = 0; i < t; i++) subcase();

	return 0;
}
