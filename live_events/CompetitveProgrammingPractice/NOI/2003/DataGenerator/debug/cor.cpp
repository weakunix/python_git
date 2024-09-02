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
typedef pair<ll, ll> simps;
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

const int N = 100; //FIXME

int n;
ll dist[N][N], ans = 0;
vector<simps> adj[N];

void dfs(int node, int parent, int st, ll curdist) {
    dist[st][node] = curdist;
    for (simps& s : adj[node]) if (s.first != parent) dfs(s.first, node, st, curdist + s.second);
    return;
}

int main() {
    cin >> n >> n; n++;
    assert(n <= N); //FIXME
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    for (int i = 0; i < n; i++) dfs(i, -1, i, 0);

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (x == y) continue;
            for (int z = 0; z < n; z++) {
                if (z == x or z == y) continue;
                if (dist[x][y] <= dist[x][z]) {
                    setmx(ans, dist[x][y] + dist[y][z]);
                    //cout << x << " " << y << " " << z << " " << dist[x][y] + dist[y][z] << "\n";
                }
            }
        }
    }

    cout << ans << "\n";

	return 0;
}
