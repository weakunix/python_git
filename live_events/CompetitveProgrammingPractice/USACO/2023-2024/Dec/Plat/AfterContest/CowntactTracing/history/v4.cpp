#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

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

const int N = 1e5;

int n, q, k, ht[N];
bool inf[N], psbl[N], vis[N];
vector<int> adj[N], ord;

bool cmp(int a, int b) {
    return ht[a] > ht[b];
}

void dfs1(int node, int parent, int height) {
    ht[node] = height;
    ord.push_back(node);
    for (int i : adj[node]) if (i != parent) dfs1(i, node, height + 1);
    return;
}

int dfs2(int node, int parent, int trav) {
    int res = (psbl[node] ? node : -1);
    if (trav == k) return res;
    for (int i : adj[node]) {
        if (i == parent) continue;
        int cur = dfs2(i, node, trav + 1);
        if (cur == -1) continue;
        if (res == -1 or ht[cur] < ht[res]) res = cur;
    }
    return res;
}

void dfs3(int node, int parent, int trav) {
    vis[node] = false;
    if (trav == k) return;
    for (int i : adj[node]) if (i != parent) dfs3(i, node, trav + 1);
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        inf[i] = (c == '1');
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(0, -1, 0);
    sort(all(ord), cmp);

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> k;

        memset(psbl, true, sizeof(psbl));
        queue<simps> qu;
        for (int j = 0; j < n; j++) {
            if (not inf[j]) {
                qu.push({j, 0});
                psbl[j] = false;
            }
        }
        while (qu.size()) {
            int node = qu.front().first, dist = qu.front().second;
            qu.pop();
            if (dist == k) continue;
            for (int j : adj[node]) {
                if (not psbl[j]) continue;
                psbl[j] = false;
                qu.push({j, dist + 1});
            }
        }

        memset(vis, false, sizeof(vis));
        for (int j = 0; j < n; j++) {
            if (psbl[j]) {
                qu.push({j, 0});
                vis[j] = true;
            }
        }
        while (qu.size()) {
            int node = qu.front().first, dist = qu.front().second;
            qu.pop();
            if (dist == k) continue;
            for (int j : adj[node]) {
                if (vis[j]) continue;
                vis[j] = true;
                qu.push({j, dist + 1});
            }
        }

        //INEFFICIENCY STARTS HERE (O(N^2))
        
        bool works = true;
        for (int j = 0; j < n; j++) if (inf[j] != vis[j]) works = false;
        if (not works) {
            cout << "-1\n";
            continue;
        }

        int ans = 0;
        for (int j : ord) {
            if (not vis[j]) continue;
            int cur = dfs2(j, -1, 0);
            assert(cur != -1); //CATCH
            ans++;
            dfs3(cur, -1, 0);
        }

        cout << ans << "\n";
    }

	return 0;
}
