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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5 + 1, INF = 1e6;

int n, rt, par[N], dep[N], topar[N], dist[N][2], goout[N], act[N], cntnode[N], cntedge[N], pfxnode, pfxedge, dp[N][2];
bool arr[N], rem[N];
vector<int> irrel[N];
set<int> adj[N];
set<simps> allnodes;

bool dfs1(int node, int parent, int depth) {
    par[node] = parent;
    adj[node].erase(parent);
    dep[node] = depth;

    vector<int> remchild;
    for (int i : adj[node]) if (dfs1(i, node, depth + 1)) remchild.pb(i);
    for (int i : remchild) adj[node].erase(i);

    rem[node] = (not arr[node] and adj[node].empty());
    return rem[node];
}

void dfs2(int node) {
    dist[node][0] = (arr[node] ? 0 : INF);
    dist[node][1] = dist[node][0];

    for (int i : adj[node]) {
        dfs2(i);
        setmn(dist[node][1], dist[i][0] + topar[i]);
        if (dist[node][1] < dist[node][0]) swap(dist[node][0], dist[node][1]);
    }

    return;
}

void dfs3(int node, int closestout) {
    goout[node] = closestout + dist[node][0];
    for (int i : adj[node]) dfs3(i, min(closestout, (dist[i][0] + topar[i] == dist[node][0] ? dist[node][1] : dist[node][0])) + topar[i]);
    return;
}

int main() {
    fill(topar, topar + N, 1);
    clr(cntnode, 0);
    clr(cntedge, 0);
    clr(dp, 0);
    clr(rem, false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        arr[i] = (c == '1');
        if (arr[i]) rt = i;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    dfs1(rt, -1, 0); //remove leaves

    for (int i = 0; i < n; i++) { //compress paths
        if (rem[i] or arr[i] or adj[i].size() > 1) continue;
        int up = par[i], down = *adj[i].begin();
        adj[up].erase(i);
        adj[up].insert(down);
        par[down] = up;
        topar[down] += topar[i];
        rem[i] = true;
    }

    dfs2(rt); //find dist to two nearest children
    dfs3(rt, 0); //find when edge to parent is used

    for (int i = 0; i < n; i++) {
        if (rem[i]) continue;

        allnodes.insert({-dep[i], i});

        int curirrel = goout[i];
        act[i] = (arr[i] ? 0 : goout[i]);
        for (int j : adj[i]) {
            setmn(act[i], goout[j]);
            setmx(curirrel, goout[j]);
        }

        irrel[curirrel].pb(i);
        cntnode[act[i]]++;
        if (i != rt) {
            cntnode[goout[i]] += topar[i] - 1;
            cntedge[goout[i]] += topar[i];
        }
    }

    pfxnode = cntnode[0];
    pfxedge = 0;

    for (int i = 1; i <= n; i++) {
        for (int j : irrel[i]) allnodes.erase({-dep[j], j});
        pfxnode += cntnode[i];
        pfxedge += cntedge[i];

        int ans = i * (pfxnode - pfxedge) + pfxnode;

        for (simps s : allnodes) {
            int cur = s.second;

            if (act[cur] <= i) dp[cur][0] = INF;
            else dp[cur][1] += i + 1;

            if (goout[cur] <= i) ans += dp[cur][1];
            else {
                dp[par[cur]][0] += min(dp[cur][0], dp[cur][1]);
                dp[par[cur]][1] += min({dp[cur][0], dp[cur][1], dp[cur][1] - i + topar[cur] - 1});
            }

            dp[cur][0] = 0;
            dp[cur][1] = 0;
        }

        cout << ans << "\n";
    }

	return 0;
}
