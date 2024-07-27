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

int n, d, m, arr[N], ans[N];
vector<int> nw;
vector<threesome> adj[N], revadj[N];

bool dfs(int node, int val) {
    if (ans[node] != -1) return ans[node] == val;
    if (arr[node] == val) return false;
    ans[node] = val;
    nw.pb(node);

    for (threesome t : adj[node]) {
        if (t.sec != val) continue;
        if (not dfs(t.first, t.third)) return false;
    }

    for (threesome t : revadj[node]) {
        if (t.third == val) continue;
        set<int> psbl = {0, 1, 2};
        psbl.erase(arr[t.first]);
        psbl.erase(t.sec);
        if (psbl.size() == 1) if (not dfs(t.first, *psbl.begin())) return false;
    }

    return true;
}

int main() {
    clr(ans, -1);

    cin >> n >> d;
    assert(not d); //FIXME
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        arr[i] = c - 'a';
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        char a, b;
        cin >> u >> a >> v >> b;
        u--; v--;
        adj[u].pb({v, {a - 'A', b - 'A'}});
        revadj[v].pb({u, {a - 'A', b - 'A'}});
    }
    
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) continue;
        for (int j = 0; j < 4; j++) {
            if (j == 3) {
                cout << "-1\n";
                return 0;
            }
            if (j == arr[i]) continue;

            nw.clear();
            if (dfs(i, j)) break;
            for (int k : nw) ans[k] = -1;
        }
    }

    for (int i = 0; i < n; i++) cout << (char) ('A' + ans[i]);
    cout << "\n";

	return 0;
}
