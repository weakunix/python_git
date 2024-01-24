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
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 4e5;

int n, par[N], dsu[N];
ll cnt[N][3], ans = 0;
vector<int> adj[N];

void dfs(int node, int parent) {
    par[node] = parent;
    for (int i : adj[node]) {
        if (i == parent) continue;
        dfs(i, node);
        cnt[node][0]++;
        cnt[node][1] += cnt[i][0];
        cnt[node][2] += cnt[i][1];
    }

    if (node < n) {
        for (int i : adj[node]) {
            if (i == parent) continue;
            ans += (cnt[node][1] - cnt[i][0]) * cnt[i][0];
        }
    }
    else {
        ans += (cnt[node][0] + 1) * cnt[node][0] * (cnt[node][0] - 1);
        ans += 2 * cnt[node][2] * cnt[node][0];
    }

    return;
}

int getdsu(int node) {
    if (node < 0 or dsu[node] < 0) return node;
    dsu[node] = getdsu(dsu[node]);
    return dsu[node];
}

void merge(int a, int b) {
    a = getdsu(a); b = getdsu(b);
    if (a == b) return;
    dsu[b] += dsu[a];
    dsu[a] = b;
    return;
}

int main() {
    clr(dsu, -1);
    clr(cnt, 0);

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

    dfs(n - 1, -1);

    for (int i = 0; i < n; i++) {
        cout << ans << "\n";

        int node = getdsu(par[i]), p1 = par[node], p2 = getdsu(par[p1]);

        if (p2 != -1) ans -= 2 * cnt[p2][2] * cnt[p2][0];
        ans -= 2 * (cnt[p1][1] - cnt[node][0]) * cnt[node][0];
        ans -= (cnt[node][0] + 1) * cnt[node][0] * (cnt[node][0] - 1);
        ans -= 2 * cnt[node][2] * cnt[node][0];
        
        if (p2 != -1) cnt[p2][2] -= cnt[p1][1];
        cnt[p1][1] -= cnt[node][0];
        cnt[node][0]--;

        for (int j : adj[i]) {
            int cur = getdsu(j);

            if (cur == node) continue;
            merge(cur, node);

            ans -= (cnt[i][1] - cnt[cur][0]) * cnt[cur][0];
            ans -= (cnt[cur][0] + 1) * cnt[cur][0] * (cnt[cur][0] - 1);
            ans -= 2 * cnt[cur][2] * cnt[cur][0];

            cnt[node][0] += cnt[cur][0];
            cnt[node][2] -= cnt[cur][0];
            cnt[node][2] += cnt[cur][2];
        }

        cnt[p1][1] += cnt[node][0];
        if (p2 != -1) cnt[p2][2] += cnt[p1][1];

        if (p2 != -1) ans += 2 * cnt[p2][2] * cnt[p2][0];
        ans += 2 * (cnt[p1][1] - cnt[node][0]) * cnt[node][0];
        ans += (cnt[node][0] + 1) * cnt[node][0] * (cnt[node][0] - 1);
        ans += 2 * cnt[node][2] * cnt[node][0];
    }


	return 0;
}
