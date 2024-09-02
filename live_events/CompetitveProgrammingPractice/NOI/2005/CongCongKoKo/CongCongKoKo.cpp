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

const int N = 1000;

int n, m, stc, stm, nxt[N][N];
double dp[N][N];
vector<int> adj[N];

void getnxt(int st) {
    nxt[st][st] = st;

    vector<int> cur = {st};

    while (cur.size()) {
        vector<int> nw;
        for (int i : cur) {
            for (int j : adj[i]) {
                if (nxt[st][j] != -1) continue;
                nxt[st][j] = i;
                nw.pb(j);
            }
        }
        sort(all(nw));
        swap(cur, nw);
    }

    return;
}

double getdp(int cat, int mouse) {
    if (dp[cat][mouse] != -1) return dp[cat][mouse];
    
    if (cat == mouse) {
        dp[cat][mouse] = 0;
        return 0;
    }

    int nwcat = nxt[mouse][nxt[mouse][cat]];

    if (nwcat == mouse) {
        dp[cat][mouse] = 1;
        return 1;
    }

    dp[cat][mouse] = getdp(nwcat, mouse);
    for (int i : adj[mouse]) dp[cat][mouse] += getdp(nwcat, i);
    dp[cat][mouse] = (dp[cat][mouse] / (adj[mouse].size() + 1)) + 1;
    return dp[cat][mouse];
}

int main() {
    clr(nxt, -1);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dp[i][j] = -1;

    cin >> n >> m >> stc >> stm;
    stc--; stm--;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    for (int i = 0; i < n; i++) getnxt(i);

    cout << fixed << setprecision(3) << getdp(stc, stm) << "\n";

	return 0;
}
