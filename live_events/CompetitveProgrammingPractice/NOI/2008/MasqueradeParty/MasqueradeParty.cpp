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

const int N = 1e5;

int n, m, val[N], ans = -1;
vector<int> adj[N], radj[N];
set<int> cnt;

void dfs1(int node, int curval) {
    if (val[node] == 1e9) val[node] = curval;
    else {
        if (val[node] != curval) {
            int cur = abs(val[node] - curval);
            if (ans == -1) ans = cur;
            ans = gcd(ans, cur);
        }
        return;
    }
    for (int i : adj[node]) dfs1(i, curval + 1);
    for (int i : radj[node]) dfs1(i, curval - 1);
    return;
}

void dfs2(int node) {
    cnt.insert(val[node]);
    val[node] = 1e9;
    for (int i : adj[node]) if (val[i] != 1e9) dfs2(i);
    for (int i : radj[node]) if (val[i] != 1e9) dfs2(i);
    return;
}

int main() {
    fill(val, val + N, 1e9);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        radj[v].pb(u);
    }

    for (int i = 0; i < n; i++) if (val[i] == 1e9) dfs1(i, 0);

    if (ans == -1) {
        ans = 0;
        for (int i = 0; i < n; i++) {
            if (val[i] == 1e9) continue;
            cnt.clear();
            dfs2(i);
            ans += cnt.size();
        }
        if (ans < 3) cout << "-1 -1\n";
        else cout << ans << " 3\n";
        return 0;
    }

    if (ans < 3) {
        cout << "-1 -1\n";
        return 0;
    }

    for (int i = 3; i <= ans; i++) {
        if (ans % i == 0) {
            cout << ans << " " << i << "\n";
            break;
        }
    }

	return 0;
}
