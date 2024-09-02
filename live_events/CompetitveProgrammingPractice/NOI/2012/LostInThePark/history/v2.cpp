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

int n, m, par[N], parw[N], deg[N];
double s[N], ans = 0;
vector<simps> adj[N];
map<int, double> sk[N], ak[N];

struct Tree {
    int rt, prv, nxt, prvidx, nxtidx, prvw, nxtw;

    Tree() : rt(-1), prv(-1), nxt(-1), prvidx(-1), nxtidx(-1), prvw(-1), nxtw(-1) {}

    Tree(int _rt, int _prv, int _nxt, int _prvidx, int _nxtidx, int _prvw, int _nxtw) : rt(_rt), prv(_prv), nxt(_nxt), prvidx(_prvidx), nxtidx(_nxtidx), prvw(_prvw), nxtw(_nxtw) {}

    ~Tree() {}

    void gens(int node, int parent, int nodecase) { //nodecase: {0: root && m = n - 1, 1: non-root, 2: root && m = n}
        int cnt = deg[node] - nodecase;

        if (cnt == 0) {
            s[node] = 0;
            return;
        }

        double sm = 0;
        for (simps& i : adj[node]) {
            if (i.first == parent or (i.first == prv or i .first == nxt)) continue;
            gens(i.first, node, 1);
            sm += s[i.first] + i.second;
        }

        s[node] = sm / cnt;
        for (simps& i : adj[node]) {
            if (i.first == parent or (i.first == prv or i .first == nxt)) continue;
            if (cnt == 1) sk[node][i.first] = 0;
            else sk[node][i.first] = (sm - s[i.first] - i.second) / (cnt - 1);
        }
        
        return;
    }

    void gena(int node, int parent, int w) {
        if (parent == -1) {
            if (m == n - 1) {
                ans += s[node];
                for (simps& i : adj[node]) ak[node][i.first] = sk[node][i.first];
            }
            else {
                ; //FIXME
            }
        }
        else {
            ans += s[node] * (deg[node] - 1) / deg[node] + (ak[parent][node] + w) / deg[node];
            if (deg[node] > 1) for (simps& i : adj[node]) if (i.first != parent) ak[node][i.first] = sk[node][i.first] * (deg[node] - 2) / (deg[node] - 1) + (ak[parent][node] + w) / (deg[node] - 1);
        }

        for (simps& i : adj[node]) {
            if (i.first == parent or (i.first == prv or i .first == nxt)) continue;
            gena(i.first, node, i.second);
        }

        return;
    }
};
vector<Tree> cyc;

bool dfs1(int node, int parent, int w) {
    par[node] = parent;
    parw[node] = w;
    for (simps& s : adj[node]) {
        if (s.first == parent) continue;
        if (par[s.first] == -1) {
            if (dfs1(s.first, node, s.second)) return true;
            continue;
        }

        int cur = node, prv = -1, prvw = -1;
        while (cur != par[s.first]) {
            cyc.pb(Tree(cur, prv, par[cur], cyc.size() - 1, cyc.size() + 1, prvw, parw[cur]));
            prv = cur;
            prvw = parw[cur];
            cur = par[cur];
        }
        cyc[0].prv = s.first;
        cyc[0].prvidx = cyc.size() - 1;
        cyc[0].prvw = s.second;
        cyc.back().nxt = node;
        cyc.back().nxtidx = 0;
        cyc.back().nxtw = s.second;

        return true;
    }
    return false;
}

int main() {
    clr(par, -1);
    clr(deg, 0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        deg[u]++;
        deg[v]++;
    }

    if (m == n - 1) {
        Tree rt = Tree(0, -1, -1, -1, -1, -1, -1);
        rt.gens(0, -1, 0);
        rt.gena(0, -1, -1);
        cout << ans / n << "\n";
        return 0;
    }

    dfs1(0, -1e9, -1);

    for (Tree& t : cyc) t.gens(t.rt, -1, 2);
    for (Tree& t : cyc) t.gena(t.rt, -1, -1);

    cout << ans / n << "\n";

	return 0;
}
