#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_map>
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

const int N = 1500, Y = 2500, L = 12, modval = 1e9 + 7;

int n, m, x, y, k = 0, sz = 0, ht[N], rtdist[N], treeid[N], st[L][2 * N], idx[N], lg[2 * N];
ll ans, dpcnt[N][Y], dpsm[N][Y];
vector<simps> adj[N];
unordered_map<int, ll> allcnt[N], allsm[N];

void dfs(int node, int parent, int height, int dist) {
    st[0][sz] = node;
    idx[node] = sz;
    sz++;
    ht[node] = height;
    rtdist[node] = dist;
    treeid[node] = k;

    for (simps& s : adj[node]) {
        if (s.first == parent) continue;
        dfs(s.first, node, height + 1, dist + s.second);
        st[0][sz] = node;
        sz++;
    }

    return;
}

int getlca(int a, int b) {
    a = idx[a];
    b = idx[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1], l = st[len][a], r = st[len][b - (1 << len) + 1];
    return ht[l] < ht[r] ? l : r;
}

int getdist(int a, int b) {
    int l = getlca(a, b);
    return rtdist[a] + rtdist[b] - 2 * rtdist[l];
}

int main() {
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);

    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    memset(treeid, -1, sizeof(treeid));
    lg[1] = 0;
    for (int i = 2; i < 2 * N; i++) lg[i] = lg[i / 2] + 1;

    cin >> n >> m >> x >> y;
    for (int i = 0; i < m; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--; b--;
        adj[a].push_back({b, d});
        adj[b].push_back({a, d});
    }

    for (int i = 0; i < n; i++) {
        if (treeid[i] != -1) continue;
        dfs(i, -1, 0, 0);
        k++;
    }

    y = max(y - k * x, 0);

    for (int i = 1; (1 << i) <= sz; i++) {
        for (int j = 0; j + (1 << i) <= sz; j++) {
            int l = st[i - 1][j], r = st[i - 1][j + (1 << (i - 1))];
            st[i][j] = ht[l] < ht[r] ? l : r;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (treeid[i] != treeid[j]) continue;
            int cur = getdist(i, j);
            allcnt[treeid[i]][min(cur, y)]++;
            allsm[treeid[i]][min(cur, y)] = (allsm[treeid[i]][min(cur, y)] + cur) % modval;
        }
    }

    for (int i = 0; i <= y; i++) {
        dpcnt[0][i] = allcnt[0][i];
        dpsm[0][i] = allsm[0][i];
    }

    for (int i = 1; i < k; i++) {
        for (int j = 0; j <= y; j++) {
            for (auto& v : allcnt[i]) {
                int val = v.first, cur = min(j + val, y);
                dpcnt[i][cur] = (dpcnt[i][cur] + dpcnt[i - 1][j] * allcnt[i][val] % modval) % modval;
                dpsm[i][cur] = (dpsm[i][cur] + dpsm[i - 1][j] * allcnt[i][val] % modval + dpcnt[i - 1][j] * allsm[i][val]) % modval;
            }
        }
    }

    ans = (dpsm[k - 1][y] + dpcnt[k - 1][y] * k * x) % modval;
    for (int i = 1; i < k; i++) ans = ans * 2 * i % modval;
    cout << ans << "\n";

	return 0;
}
