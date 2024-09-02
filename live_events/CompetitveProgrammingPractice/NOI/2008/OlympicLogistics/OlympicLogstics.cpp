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

const int N = 61, M = 61;

int n, m, nxt[N], dist[N];
double k[N], c[N], dp[N][M][N], ans = 0;
bool cyc[N];
vector<int> adj[N];

void dfs(int node) {
    for (int i : adj[node]) {
        if (dist[i] != -1) continue;
        dist[i] = dist[node] + 1;
        dfs(i);
    }
    return;
}

void solve(int curm, int len) { //O(N)
    if (curm < 0) return;

    clr(dist, -1);
    clr(dp, 0);
    for (int i = 0; i < n; i++) adj[i].clear();

    double cycval = 0;
    vector<int> rts;
    priority_queue<simps> pq;

    for (int i = 0; i < n; i++) adj[nxt[i]].pb(i);
    dist[0] = 0;
    dfs(0);

    for (int i = 0; i < n; i++) pq.push({dist[i], i});

    while (pq.size()) { //O(N)
        int node = pq.top().second;
        pq.pop();
        if (cyc[node]) {
            cycval += k[dist[node]] * c[node];
            continue;
        }

        if (cyc[nxt[node]]) rts.pb(node);

        for (int i = 0; i <= curm; i++) { //O(M)
            for (int j = 1; j <= dist[node]; j++) { //O(N)
                vector<vector<double>> sack;

                sack.resize(adj[node].size() + 1, vector<double>(i + 1));
                sack[0].clear();
                sack[0].resize(i + 1, k[j] * c[node]);
                for (int l = 1; l <= adj[node].size(); l++) { //O(|S|)
                    for (int o = 0; o <= i; o++) { //O(M)
                        for (int p = 0; p <= o; p++) { //O(M)
                            setmx(sack[l][o], sack[l - 1][p] + dp[adj[node][l - 1]][o - p][j + 1]);
                        }
                    }
                }
                setmx(dp[node][i][j], sack.back().back());

                if (not i) continue;

                sack.clear();
                sack.resize(adj[node].size() + 1, vector<double>(i));
                sack[0].clear();
                sack[0].resize(i, k[1] * c[node]);
                for (int l = 1; l <= adj[node].size(); l++) { //O(|S|)
                    for (int o = 0; o < i; o++) { //O(M)
                        for (int p = 0; p <= o; p++) { //O(M)
                            setmx(sack[l][o], sack[l - 1][p] + dp[adj[node][l - 1]][o - p][2]);
                        }
                    }
                }
                setmx(dp[node][i][j], sack.back().back());
            }
        }
    }

    vector<vector<double>> sack(rts.size() + 1, vector<double>(curm + 1));
    sack[0].clear();
    sack[0].resize(curm + 1, cycval);
    for (int i = 1; i <= rts.size(); i++) {
        for (int j = 0; j <= curm; j++) {
            for (int l = 0; l <= j; l++) {
                setmx(sack[i][j], sack[i - 1][l] + dp[rts[i - 1]][j - l][dist[rts[i - 1]]]);
            }
        }
    }

    setmx(ans, sack.back().back() / (1 - k[len]));

    return;
}

int main() {
    clr(cyc, false);
    cyc[0] = true;

    k[0] = 1;
    cin >> n >> m >> k[1];
    for (int i = 2; i <= n; i++) k[i] = k[i - 1] * k[1];

    for (int i = 0; i < n; i++) {
        cin >> nxt[i];
        nxt[i]--;
    }

    for (int i = 0; i < n; i++) cin >> c[i];

    for (int i = nxt[0], len = 2; i != 0; i = nxt[i], len++) {
        cyc[i] = true;

        int cur = nxt[i];
        nxt[i] = 0;
        solve(m - (cur != 0), len);
        nxt[i] = cur;
    }

    cout << fixed << setprecision(2) << ans << "\n";

	return 0;
}
