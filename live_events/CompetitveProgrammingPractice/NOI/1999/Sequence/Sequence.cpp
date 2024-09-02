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

const int N = 1001;

int n, a0, b0, l0, a1, b1, l1, dist[N], cnt[N];
bool vis[N];
vector<simps> adj[N];

void addedge(int u, int v, int w) {
    adj[u].pb({v, w});
    return;
}

bool spfa() {
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    vis[0] = true;

    while (q.size()) {
        int node = q.front();
        q.pop();
        vis[node] = false;

        for (simps& s : adj[node]) {
            int nxt = s.first, w = s.second;
            
            if (dist[nxt] <= dist[node] + w) continue;

            dist[nxt] = dist[node] + w;
            if (vis[nxt]) continue;

            q.push(nxt);
            vis[nxt] = true;
            cnt[nxt]++;
            if (cnt[nxt] > n + 1) return false;
        }
    }

    return true;
}

int main() {
    fill(dist, dist + N, 1e9);
    clr(cnt, 0);
    clr(vis, false);

    cin >> n >> a0 >> b0 >> l0 >> a1 >> b1 >> l1;

    for (int i = 1; i <= n; i++) {
        addedge(i - 1, i, 1);
        addedge(i, i - 1, 0);
    }

    for (int i = l0; i <= n; i++) {
        addedge(i - l0, i, l0 - a0);
        addedge(i, i - l0, b0 - l0);
    }

    for (int i = l1; i <= n; i++) {
        addedge(i, i - l1, -a1);
        addedge(i - l1, i, b1);
    }

    if (not spfa()) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 1; i <= n; i++) cout << dist[i] - dist[i - 1];
    cout << "\n";

	return 0;
}
