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
#include <iomanip>

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

const int N = 100;

int n, m, dist[N];
ll cnt[N][N];
double ans[N];
vector<simps> adj[N];

void solve(int st) {
    clr(dist, -1);
    clr(cnt, 0);

    priority_queue<threesome> pq;
    dist[st] = 0;
    cnt[st][st] = 1;
    for (simps& s : adj[st]) pq.push({-s.second, {s.first, st}});

    while (pq.size()) {
        int node = pq.top().sec, prv = pq.top().third, curd = -pq.top().first;
        pq.pop();

        if (dist[node] != -1) {
            if (curd > dist[node]) continue;
            for (int i = 0; i < n; i++) cnt[node][i] += cnt[prv][i];
            cnt[node][node] += cnt[prv][st];
            continue;
        }

        dist[node] = curd;
        for (int i = 0; i < n; i++) cnt[node][i] = cnt[prv][i];
        cnt[node][node] = cnt[prv][st];
        
        for (simps& s : adj[node]) pq.push({-(curd + s.second), {s.first, node}});
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == st or j == i) continue;
            ans[j] += (double) cnt[i][j] / cnt[i][i];
        }
    }

    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    for (int i = 0; i < n; i++) solve(i);
    for (int i = 0; i < n; i++) cout << fixed << setprecision(3) << ans[i] << "\n";

	return 0;
}
