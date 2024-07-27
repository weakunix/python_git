#include <cstdio>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <array>
#include <algorithm>
#include <queue>
#include <vector>
#include <bitset>
#include <ctime>
#include <cstdlib>
#include <random>
#include <set>
#include <ctime>
#include <map>
#include <stack>
#include <unordered_map>



using namespace std;
using ll = long long;
const int N = 262150, mod = 998244353;
int n, m, sz[N];
ll dis[N], a[N], d[N][2], Sz[N][2], sum[N], ans;
bool vis[N];
vector<pair<int, ll>>mp[N];
vector<int>mp1[N];
struct node {
    int id;
    ll d;
    bool operator<(const node &b)const {
        return d > b.d;
    }
} tmp;
priority_queue<node>pq;
void add(int x, int y, ll z) {
    if (x == y)
        return;

    mp[x].emplace_back(y, z);
    int l = lower_bound(mp1[x << 1].begin(), mp1[x << 1].end(), y) - mp1[x << 1].begin();

    if (l != mp1[x << 1].size() && mp1[x << 1][l] == y)
        add(x << 1, y, z + a[x << 1]);
    else
        add(x << 1 | 1, y, z + a[x << 1 | 1]);
}
void reset(int x) {
    dis[x] = 1e18, vis[x] = 0;

    if (x * 2 <= n)
        reset(x * 2);

    if (x * 2 + 1 <= n)
        reset(x * 2 + 1);
}
void calc(int x, int y, int z) {
    if (x > n)
        return;

    if (dis[x] != 1e18)
        d[y][z] = (d[y][z] + dis[x]) % mod, Sz[y][z]++;

    if (x * 2 <= n)
        calc(x * 2, y, z);

    if (x * 2 + 1 <= n)
        calc(x * 2 + 1, y, z);
}
void dijkstra(int x) {
    reset(x), dis[x] = 0, pq.emplace((node) {
        x, 0
    });

    while (!pq.empty()) {
        tmp = pq.top(), pq.pop();
        int s = tmp.id;

        if (vis[s])
            continue;

        vis[s] = 1;

        if (s != x && !vis[s / 2] && dis[s] + a[s] < dis[s / 2]) {
            dis[s / 2] = dis[s] + a[s];
            pq.emplace((node) {
                s / 2, dis[s / 2]
            });
        }

        for (auto i : mp[s])
            if (!vis[i.first] && dis[s] + i.second < dis[i.first]) {
                dis[i.first] = dis[s] + i.second;
                pq.emplace((node) {
                    i.first, dis[i.first]
                });
            }
    }

    calc(x * 2, x, 0), calc(x * 2 + 1, x, 1);
}
void dfs1(int x) {
    sz[x] = 1, dijkstra(x);

    if (x * 2 <= n)
        dfs1(x * 2), sz[x] += sz[x * 2];

    if (x * 2 + 1 <= n)
        dfs1(x * 2 + 1), sz[x] += sz[x * 2 + 1];
}
void dfs2(int x) {
    ll val;

    if (x * 2 <= n) {
        dfs2(x * 2), val = (sum[x << 1] + 1ll * a[x << 1] * sz[x << 1]) % mod;
        ans = (ans + val * (Sz[x][1] + 1) % mod + d[x][1] * (sz[x << 1] + 1) % mod) % mod;
        sum[x] += val;
    }

    if (x * 2 + 1 <= n) {
        dfs2(x * 2 + 1), val = (sum[x << 1 | 1] + 1ll * a[x << 1 | 1] * sz[x << 1 | 1]) % mod;
        ans = (ans + val * (Sz[x][0] + 1) % mod + d[x][0] * (sz[x << 1 | 1] + 1) % mod) % mod;
        sum[x] += val;
    }

    sum[x] %= mod;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m, n = (1 << n) - 1;

    for (int i = 2; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        int pos = i;

        while (pos)
            mp1[pos].emplace_back(i), pos /= 2;
    }

    for (int i = 1; i <= n; i++)
        sort(mp1[i].begin(), mp1[i].end());

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
    }

    dfs1(1), dfs2(1), cout << ans << "\n";
    return 0;
}
