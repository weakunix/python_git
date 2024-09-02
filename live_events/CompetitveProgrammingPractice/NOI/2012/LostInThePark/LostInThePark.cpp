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

const int N = 1e5, C = 20;

int n, m, par[N], parw[N], deg[N];
double s[N], ans = 0, p[C][C];
vector<simps> adj[N];
map<int, double> sk[N], ak[N];

struct Tree {
    int rt, prvw, nxtw;
    Tree* prv;
    Tree* nxt;

    Tree() : rt(-1), prvw(-1), nxtw(-1), prv(nullptr), nxt(nullptr) {}

    Tree(int _rt, int _prvw, int _nxtw, Tree* _prv, Tree* _nxt) : rt(_rt), prvw(_prvw), nxtw(_nxtw), prv(_prv), nxt(_nxt) {}

    ~Tree() {}

    bool badadj(int node) {
        return (prv != nullptr and prv->rt == node) or (nxt != nullptr and nxt->rt == node);
    }

    void gens(int node, int parent, int nodecase) { //nodecase: {0: root && m = n - 1, 1: non-root, 2: root && m = n}
        int cnt = deg[node] - nodecase;

        if (cnt == 0) {
            s[node] = 0;
            return;
        }

        double sm = 0;
        for (simps& i : adj[node]) {
            if (i.first == parent or badadj(i.first)) continue;
            gens(i.first, node, 1);
            sm += s[i.first] + i.second;
        }

        s[node] = sm / cnt;
        for (simps& i : adj[node]) {
            if (i.first == parent or badadj(i.first)) continue;
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
                int l = nxtw;
                double c1 = 0, c2 = 0, p = 1;

                for (Tree* i = nxt; i->rt != rt; i = i->nxt) {
                    int cur = i->rt;
                    if (i->nxt->rt == node) c1 += p * (s[cur] + l);
                    else c1 += p * (s[cur] + l) * (deg[cur] - 2) / (deg[cur] - 1);
                    p = p / (deg[cur] - 1);
                    l += i->nxtw;
                }

                p = 1;
                l = prvw;
                for (Tree* i = prv; i->rt != rt; i = i->prv) {
                    int cur = i->rt;
                    if (i->prv->rt == node) c2 += p * (s[cur] + l);
                    else c2 += p * (s[cur] + l) * (deg[cur] - 2) / (deg[cur] - 1);
                    p = p / (deg[cur] - 1);
                    l += i->prvw;
                }

                ans += s[node] * (deg[node] - 2) / deg[node] + (c1 + c2) / deg[node];
                for (simps& i : adj[node]) {
                    if (badadj(i.first)) continue;
                    ak[node][i.first] = sk[node][i.first] * (deg[node] - 3) / (deg[node] - 1) + (c1 + c2) / (deg[node] - 1);
                }
            }
        }
        else {
            ans += s[node] * (deg[node] - 1) / deg[node] + (ak[parent][node] + w) / deg[node];
            if (deg[node] > 1) for (simps& i : adj[node]) if (i.first != parent) ak[node][i.first] = sk[node][i.first] * (deg[node] - 2) / (deg[node] - 1) + (ak[parent][node] + w) / (deg[node] - 1);
        }

        for (simps& i : adj[node]) {
            if (i.first == parent or badadj(i.first)) continue;
            gena(i.first, node, i.second);
        }

        return;
    }
};
vector<Tree*> cyc;

bool dfs1(int node, int parent, int w) {
    par[node] = parent;
    parw[node] = w;
    for (simps& i : adj[node]) {
        if (i.first == parent) continue;
        if (par[i.first] == -1) {
            if (dfs1(i.first, node, i.second)) return true;
            continue;
        }

        int prvw = -1;
        while (node != par[i.first]) {
            cyc.pb(new Tree(node, prvw, parw[node], nullptr, nullptr));
            prvw = parw[node];
            node = par[node];
        }
        cyc[0]->prvw = i.second;
        cyc.back()->nxtw = i.second;

        for (int i = 0; i < cyc.size(); i++) {
            cyc[i]->prv = cyc[(i + cyc.size() - 1) % cyc.size()];
            cyc[i]->nxt = cyc[(i + 1) % cyc.size()];
        }

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
        Tree rt = Tree(0, -1, -1, nullptr, nullptr);
        rt.gens(0, -1, 0);
        rt.gena(0, -1, -1);
        cout << ans / n << "\n";
        return 0;
    }

    dfs1(0, -1e9, -1);

    for (Tree* t : cyc) t->gens(t->rt, -1, 2);
    for (Tree* t : cyc) t->gena(t->rt, -1, -1);

    cout << ans / n << "\n";

	return 0;
}
