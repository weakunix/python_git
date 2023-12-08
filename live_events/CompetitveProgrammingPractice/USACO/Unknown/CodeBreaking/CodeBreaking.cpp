#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

const int N = 2e4, modval = 1234567;

int n, m, par[N];
ll ans = 1;
vector<int> adj[N];
set<int> invalid[N], psbl[N][4];
map<int, int> childidx;
map<int, ll> dp[N][5], partialdp[10][4];
map<simps, vector<int>> childst;
map<simps, vector<simps>> stadj;

ll seg[10][4 * N]; //temp, to be replaced by seg

void setseg(int segidx, int node, int l, int r, int idx, ll val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[segidx][node] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(segidx, 2 * node, l, mid, idx, val);
    setseg(segidx, 2 * node + 1, mid + 1, r, idx, val);
    seg[segidx][node] = seg[segidx][2 * node] * seg[segidx][2 * node + 1] % modval;
    return;
}

ll getseg(int segidx, int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 1;
    if (l >= a and r <= b) return seg[segidx][node];
    int mid = l + (r - l) / 2;
    return getseg(segidx, 2 * node, l, mid, a, b) * getseg(segidx, 2 * node + 1, mid + 1, r, a, b) % modval;
}

void stdfs(simps st, int node) {
    int curpw = 1;
    map<int, ll> prv[10];

    for (int i = 0; i < st.first; i++) curpw *= 10;

    for (int i = 0; i < 10; i++) {
        int curst = st.second + curpw * i, curcnt = st.first + 1;
        for (int j : childst[make_pair(curcnt, curst)]) {
            prv[i][j] = getseg(i, 1, 0, adj[node].size() - 1, childidx[j], childidx[j]);
            setseg(i, 1, 0, adj[node].size() - 1, childidx[j], dp[j][curcnt][curst]);
        }
        partialdp[i][st.first][st.second] = getseg(i, 1, 0, adj[node].size() - 1, 0, adj[node].size() - 1);
        dp[node][st.first][st.second] = (dp[node][st.first][st.second] + partialdp[i][st.first][st.second]) % modval;
    }

    for (simps s : stadj[st]) stdfs(s, node);

    for (int i = 0; i < 10; i++) {
        int curst = st.second + curpw * i, curcnt = st.first + 1;
        for (int j : childst[make_pair(curcnt, curst)]) setseg(i, 1, 0, adj[node].size() - 1, childidx[j], prv[i][j]);
    }

    return;
}

void dfs(int node) {
    psbl[node][0].insert(0);

    for (int i : adj[node]) {
        dfs(i);
        
        int curpw = 1;
        for (int j = 2; j < 5; j++) {
            curpw *= 10;
            for (auto& u : dp[i][j]) psbl[node][j - 1].insert(u.first % curpw);
        }
    }

    childidx.clear();
    childst.clear();
    for (int i : adj[node]) {
        childidx[i] = childidx.size();
        for (int j = 0; j < 5; j++) for (auto& u : dp[i][j]) childst[make_pair(j, u.first)].push_back(i);
        for (int j = 0; j < 10; j++) setseg(j, 1, 0, adj[node].size() - 1, childidx[i], dp[i][0][0]);
    }

    for (int i = 0; i < 10; i++) for (int j = 0; j < 4; j++) partialdp[i][j].clear();

    stadj.clear();
    for (int i = 1; i < 4; i++) {
        for (int j : psbl[node][i]) {
            int seq = j / 10, cnt = i - 1;
            while (not psbl[node][cnt].count(seq)) {
                seq /= 10;
                cnt--;
            }
            stadj[make_pair(cnt, seq)].push_back({i, j});
        }
    }

    stdfs({0, 0}, node);

    set<int> curinvalid;
    for (int i : invalid[node]) curinvalid.insert(i % 10000);

    for (int i : curinvalid) {
        dp[node][4][i] = 0;
        for (int j = 0; j < 10; j++) {
            if (invalid[node].count(i + 1e4 * j)) continue;
            int childseq = i / 10, cnt = 3;
            while (not partialdp[j][cnt].count(childseq)) {
                childseq /= 10;
                cnt--;
            }
            dp[node][4][i] = (dp[node][4][i] + partialdp[j][cnt][childseq]) % modval;
        }
    }

    return;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        adj[par[i]].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        invalid[a].insert(b);
    }
    
    dfs(0);

    for (int i = 0; i < n; i++) ans = ans * 10 % modval;
    cout << (ans + modval - dp[0][0][0]) % modval << "\n";

	return 0;
}
