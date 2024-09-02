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

const int N = 5e4;

int n, q, par[N], prv[N], nxt[N], ans = 0;

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

int merge(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;

    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return b;
}

int main() {
    clr(par, -1);
    clr(prv, -1);
    clr(nxt, -1);

    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--; v--;

        if (u >= n or v >= n) {
            ans++;
            continue;
        }

        u = getpar(u); v= getpar(v);

        int a, b, c;
        if (t == 1) {
            if (u == v) continue;
            if (u == nxt[v] or u == prv[v]) {
                ans++;
                continue;
            }
            
            a = merge(prv[u], prv[v]);
            b = merge(u, v);
            c = merge(nxt[u], nxt[v]);
        }
        else {
            if (u == prv[v]) continue;
            if (u == v or u == nxt[v]) {
                ans++;
                continue;
            }

            a = merge(prv[u], nxt[v]);
            b = merge(u, prv[v]);
            c = merge(nxt[u], v);
        }

        if (a != -1) {
            prv[a] = c;
            nxt[a] = b;
        }
        if (b != -1) {
            prv[b] = a;
            nxt[b] = c;
        }
        if (c != -1) {
            prv[c] = b;
            nxt[c] = a;
        }
    }

    cout << ans << "\n";

	return 0;
}
