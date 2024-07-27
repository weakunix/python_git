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

const int N = 5e4, M = 1e5, D = 8;

int n, d, m, arr[N], ans[N], any[D];
bool force[N];
vector<int> edges[M];
vector<simps> adj[N][3];

int op(int node, int cur) {
    if (arr[node] != 0 and cur != 0) return 0;
    if (arr[node] != 1 and cur != 1) return 1;
    return 2;
}

bool dfs(int node, int val, bool setfix) {
    if (arr[node] == val) val = op(node, -1);
    if (ans[node] != val and force[node]) return false;
    ans[node] = val;
    if (setfix) force[node] = true;

    for (simps& s : adj[node][val]) {
        int nxt = s.first, nxtval = s.second;
        if (ans[nxt] == -1) {
            if (not dfs(nxt, nxtval, false)) return false;
            if (ans[node] != val) return true;
            continue;
        }
        if (ans[nxt] == nxtval) continue;
        if (not dfs(nxt, op(nxt, ans[nxt]), true)) return false;
        if (ans[node] != val) return true;
    }
    return true;
}

bool solve() {
    clr(ans, -1);
    clr(force, false);
    for (int i = 0; i < n; i++) for (int j = 0; j < 3; j++) adj[i][j].clear();

    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1], a = edges[i][2], b = edges[i][3];
        adj[u][a].pb({v, b});
        if (a != arr[u]) for (int j = 0; j < 3; j++) if (j != b) adj[v][j].pb({u, op(u, a)});
    }

    for (int i = 0; i < n; i++) if (ans[i] == -1 and not dfs(i, op(i, -1), false)) return false;

    return true;
}

int main() {
    cin >> n >> d;
    for (int i = 0, j = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'x') {
            any[j] = i;
            j++;
        }
        else arr[i] = c - 'a';
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        char a, b;
        cin >> u >> a >> v >> b;
        u--; v--;
        edges[i] = {u, v, a - 'A', b - 'A'};
    }

    for (int i = 0; i < (1 << d); i++) {
        for (int j = 0; j < d; j++) arr[any[j]] = (i & (1 << j) ? 1 : 0);
        if (solve()) {
            for (int i = 0; i < n; i++) cout << (char) ('A' + ans[i]);
            cout << "\n";
            return 0;
        }
    }

    cout << "-1\n";
    
	return 0;
}
