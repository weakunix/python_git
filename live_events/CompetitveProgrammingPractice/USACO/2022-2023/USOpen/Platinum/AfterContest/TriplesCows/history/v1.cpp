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
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 4e5;

int n, par[N], cnt[N];
vector<int> adj[N];

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    cnt[b] += cnt[a] - 1;
    return;
}

ll calc(int st) {
    int vis[N];
    ll res = 0;
    memset(vis, -1, sizeof(vis));

    for (int i = st; i < n; i++) {
        ll cur = 0;
        for (int j : adj[i]) {
            int node = getpar(j);
            if (vis[node] < i) {
                vis[node] = i;
                cur += cnt[node] - 1;
            }
        }
        res += cur * (cur - 1);
    }

    return res;
}

int main() {
    memset(par, -1, sizeof(par));
    fill(cnt, cnt + N, 2);

    cin >> n;
    for (int i = n; i < 2 * n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(i);
        adj[b].pb(i);
        adj[i].pb(a);
        adj[i].pb(b);
    }

    for (int i = 0; i < n; i++) {
        cout << calc(i) << "\n";
        cnt[getpar(adj[i][0])]--;
        for (int j : adj[i]) merge(j, adj[i][0]);
    }

	return 0;
}
