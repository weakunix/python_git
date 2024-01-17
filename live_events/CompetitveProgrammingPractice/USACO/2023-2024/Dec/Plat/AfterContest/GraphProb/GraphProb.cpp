#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 2e5 + 1, M = 4e5 + 1, modval = 1e9 + 7;
ll pw[N];

struct Node {
    int len;
    ll val;
    
    Node(int l = 0, ll v = 0) {
        len = l;
        val = v;
        return;
    }
};

void mul(Node& a, Node b) {
    a.val = (a.val * pw[b.len] % modval + b.val) % modval;
    a.len += b.len;
    return;
}

int n, m, cnt = 0, idx[N], par[N], lidx[N], ridx[N];
bool vis[N], used[M];
simps edges[M];
Node lz[4 * N];
vector<simps> adj[N];

void prop(int node, int l, int r) {
    if (l == r or not lz[node].len) return;
    mul(lz[2 * node], lz[node]);
    mul(lz[2 * node + 1], lz[node]);
    lz[node] = Node(0, 0);
    return;
}

void setseg(int node, int l, int r, int a, int b, Node c) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        mul(lz[node], c);
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, c);
    setseg(2 * node + 1, mid + 1, r, a, b, c);
    return;
}

Node getseg(int node, int l, int r, int a) {
    prop(node, l, r);
    if (l == a and r == a) return lz[node];
    int mid = l + (r - l) / 2;
    if (a <= mid) return getseg(2 * node, l, mid, a);
    return getseg(2 * node + 1, mid + 1, r, a);
}

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b, int c) {
    Node aval = Node(1, c), bval = Node(1, c);
    mul(aval, getseg(1, 0, n - 1, idx[a]));
    mul(bval, getseg(1, 0, n - 1, idx[b]));
    a = getpar(a); b = getpar(b);
    setseg(1, 0, n - 1, lidx[a], ridx[a], bval);
    setseg(1, 0, n - 1, lidx[b], ridx[b], aval);
    
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    
    lidx[b] = min(lidx[a], lidx[b]);
    ridx[b] = max(ridx[a], ridx[b]);

    return;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = 10 * pw[i - 1] % modval;

    memset(par, -1, sizeof(par));
    memset(vis, false, sizeof(vis));
    memset(used, false, sizeof(used));

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--; edges[i].second--;
        adj[edges[i].first].push_back({-i, edges[i].second});
        adj[edges[i].second].push_back({-i, edges[i].first});
    }

    priority_queue<simps> pq;
    pq.push({0, 0});

    while (not pq.empty()) {
        int node = pq.top().second, edge = -pq.top().first;
        pq.pop();
        if (vis[node]) continue;
        vis[node] = true;
        used[edge] = true;
        lidx[node] = cnt;
        ridx[node] = cnt;
        idx[node] = cnt;
        cnt++;

        for (simps s : adj[node]) pq.push(s);
    }

    for (int i = 1; i <= m; i++) {
        if (not used[i]) continue;
        merge(edges[i].first, edges[i].second, i);
    }

    for (int i = 0; i < n; i++) cout << getseg(1, 0, n - 1, idx[i]).val << "\n";

	return 0;
}
