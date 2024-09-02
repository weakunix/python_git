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

const int N = 3e4, Q = 5e5;

int n = N, q, segidx[N], lidx[N], ridx[N], curidx = 0, par[N], seg[4 * N], lz[4 * N];
threesome arr[Q];
vector<simps> adj[N];

void prim(int st) {
    priority_queue<simps> pq;
    segidx[st] = curidx;
    lidx[st] = curidx;
    ridx[st] = curidx;
    curidx++;
    for (simps& s : adj[st]) pq.push(s);

    while (pq.size()) {
        int node = pq.top().second;
        pq.pop();
        if (segidx[node] != -1) continue;

        segidx[node] = curidx;
        lidx[node] = curidx;
        ridx[node] = curidx;
        curidx++;

        for (simps& s : adj[node]) pq.push(s);
    }

    return;
}

void prop(int node, int l, int r) {
    if (l < r) {
        lz[2 * node] += lz[node];
        lz[2 * node + 1] += lz[node];
    }
    seg[node] += (r - l + 1) * lz[node];
    lz[node] = 0;
    return;
}

void setseg(int node, int l, int r, int a, int b, int c) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lz[node] = c;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, c);
    setseg(2 * node + 1, mid + 1, r, a, b, c);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

int getseg(int node, int l, int r, int idx) {
    prop(node, l, r);
    if (l > idx or r < idx) return 0;
    if (l == r) return seg[node];
    int mid = l + (r - l) / 2;
    return getseg(2 * node, l, mid, idx) + getseg(2 * node + 1, mid + 1, r, idx);
}

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    setseg(1, 0, n - 1, lidx[a], ridx[a], -par[b]);
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    setmn(lidx[b], lidx[a]);
    setmx(ridx[b], ridx[a]);
    return;
}

int main() {
    clr(segidx, -1);
    clr(lidx, -1);
    clr(ridx, -1);
    clr(par, -1);
    clr(seg, 0);
    clr(lz, 0);

    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        char t;
        cin >> t >> u >> v;
        u--; v--;
        arr[i] = {t == 'C', {u, v}};
        if (t == 'M') {
            adj[u].pb({-i, v});
            adj[v].pb({-i, u});
        }
    }

    for (int i = 0; i < n; i++) if (segidx[i] == -1) prim(i);

    for (int i = 0; i < q; i++) {
        int a = arr[i].sec, b = arr[i].third;
        if (arr[i].first) {
            if (getpar(a) != getpar(b)) {
                cout << "-1\n";
                continue;
            }
            cout << abs(getseg(1, 0, n - 1, segidx[a]) - getseg(1, 0, n - 1, segidx[b])) - 1 << "\n";
        }
        else merge(a, b);
    }

	return 0;
}
