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

const int N = 5e4, M = 1e5, D = 8;

int n, d, m, arr[N], any[D], ans[N], scccnt = 0, sccid[2 * N];
bool vis[2 * N];
vector<int> edges[M], adj[2 * N], revadj[2 * N], stck;

bool getbool(int node, int val) {
    for (int i = 0; i < 3; i++) {
        if (i == arr[node]) continue;
        if (i == val) return false;
        return true;
    }
    assert(false);
    return false;
}

int getint(int node, int cond) {
    for (int i = 0; i < 3; i++) {
        if (i == arr[node]) continue;
        if (not cond) return i;
        cond = false;
    }
    assert(false);
    return -1;
}

int getnode(int node, bool cond) {
    return node + cond * n;
}

int getflip(int node, int notval) {
    for (int i = 0; i < 3; i++) if (i != arr[node] and i != notval) return i;
    assert(false);
    return -1;
}

void dfs1(int node) {
    vis[node] = true;
    for (int i : adj[node]) if (ans[i % n] == -1 and not vis[i]) dfs1(i);
    stck.pb(node);
    return;
}

void dfs2(int node) {
    vis[node] = false;
    sccid[node] = scccnt;
    for (int i : revadj[node]) if (ans[i % n] == -1 and vis[i]) dfs2(i);
    return;
}


bool solve() {
    clr(ans, -1);
    clr(vis, false);
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        revadj[i].clear();
    }
    
    queue<int> q;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1], a = edges[i][2], b = edges[i][3];
        if (a == arr[u]) continue;
        if (b == arr[v]) {
            int cur = getflip(u, a);
            if (ans[u] != -1) {
                if (ans[u] != cur) return false;
                continue;
            }
            ans[u] = cur;
            q.push(u);
            continue;
        }
        adj[getnode(u, getbool(u, a))].pb(getnode(v, getbool(v, b)));
        adj[getnode(v, not getbool(v, b))].pb(getnode(u, not getbool(u, a)));
        revadj[getnode(v, getbool(v, b))].pb(getnode(u, getbool(u, a)));
        revadj[getnode(u, not getbool(u, a))].pb(getnode(v, not getbool(v, b)));
    }

    while (q.size()) {
        int node = q.front(), val = ans[node];
        q.pop();
        for (int i : adj[getnode(node, getbool(node, val))]) {
            int nxt = i % n, nxtval = getint(nxt, i >= n);
            if (ans[nxt] != -1) {
                if (ans[nxt] != nxtval) return false;
                continue;
            }
            ans[nxt] = nxtval;
            q.push(nxt);
        }
    }

    for (int i = 0; i < 2 * n; i++) if (ans[i % n] == -1 and not vis[i]) dfs1(i);
    while (stck.size()) {
        int node = stck.back();
        stck.bp();
        if (ans[node % n] == -1 and vis[node]) {
            dfs2(node);
            scccnt++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (ans[i % n] != -1) continue;
        if (sccid[i] == sccid[n + i]) return false;
        ans[i] = getint(i, sccid[i] < sccid[n + i]);
    }

    return true;
}

int main() {
    cin >> n >> d;
    for (int i = 0, j = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'x') {
            any[j] = i;
            j++;
        }
        else arr[i] = c - 'a';
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        char a, b;
        cin >> u >> a >> v >> b;
        u--; v--;
        edges[i] = {u, v, a - 'A', b - 'A'};
    }

    for (int i = 0; i < (1 << d); i++) {
        for (int j = 0; j < d; j++) arr[any[j]] = (i & (1 << j) ? 1 : 0);
        if (solve()) {
            for (int i = 0; i < n; i++) cout << (char) ('A' + ans[i]);
            cout << "\n";
            return 0;
        }
    }

    cout << "-1\n";

	return 0;
}
