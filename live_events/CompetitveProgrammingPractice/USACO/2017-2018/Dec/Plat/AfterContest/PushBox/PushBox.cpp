#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
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

const int N = 1502, M = 1502, K = N * M, dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};

int n, m, q, bcccnt = 0, ht[K], hi[K], stloc = -1, bccid[K][4];
bool grid[N][M], vis1[N][M], vis2[4 * K];
simps bes, box;
vector<int> adj[K];
vector<simps> stck;

int gethsh(int y, int x, int d = 0) {
    return n * m * d + (y - 1) * m + x - 1;
}

int getx(int hsh) {
    return hsh % m + 1;
}

int gety(int hsh) {
    return hsh / m % n + 1;
}

int getd(int hsh) {
    return hsh / (n * m);
}

ll getedge(int a, int b) {
    if (a > b) swap(a, b);
    return (ll) 1e9 * a + b;
}

int dfs1(int node, int parent, int height) {
    ht[node] = height;
    hi[node] = height;

    for (int i : adj[node]) {
        if (i == parent or ht[i] > height) continue;
        stck.push_back({node, i});
        if (ht[i] == -1) {
            hi[node] = min(dfs1(i, node, height + 1), hi[node]);
            if (hi[i] >= height) {
                while (stck.size()) {
                    int a = stck.back().first, b = stck.back().second;
                    stck.pop_back();

                    for (int j = 0; j < 4; j++) {
                        if (gety(a) + diry[j] == gety(b) and getx(a) + dirx[j] == getx(b)) {
                            bccid[a][(j + 2) % 4] = bcccnt;
                            bccid[b][j] = bcccnt;
                            break;
                        }
                    }

                    if (a == node and b == i) break;
                }
                bcccnt++;
            }
        }
        else hi[node] = min(ht[i], hi[node]);
    }

    return hi[node];
}

bool dfs2(int y, int x) {
    vis1[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int newy = y + diry[i], newx = x + dirx[i];
        if (newy == box.first and newx == box.second) {
            stloc = gethsh(newy, newx, i);
            return true;
        }
        if ((grid[newy][newx] and not vis1[newy][newx]) and dfs2(newy, newx)) return true;
    }
    return false;
}

void dfs3(int hsh) {
    int x = getx(hsh), y = gety(hsh), d = getd(hsh);
    vis2[hsh] = true;

    for (int i = 0; i < 4; i++) {
        int newy = y - diry[i], newx = x - dirx[i];
        if (not grid[newy][newx] or vis2[gethsh(y, x, i)]) continue;
        if (bccid[gethsh(y, x)][d] == bccid[gethsh(y, x)][i]) dfs3(gethsh(y, x, i));
    }

    x += dirx[d];
    y += diry[d];

    if (grid[y][x] and not vis2[gethsh(y, x, d)]) dfs3(gethsh(y, x, d));

    return;
}

int main() {
    //*
    freopen("pushabox.in", "r", stdin);
    freopen("pushabox.out", "w", stdout);
    ///

    memset(ht, -1, sizeof(ht));
    memset(grid, false, sizeof(grid));
    memset(vis1, false, sizeof(vis1));
    memset(vis2, false, sizeof(vis2));

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            grid[i][j] = (c != '#');
            if (c == 'A') bes = {i, j};
            else if (c == 'B') box = {i, j};
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (not grid[i][j]) continue;
            for (int k = 0; k < 4; k++) {
                int newy = i + diry[k], newx = j + dirx[k];
                if (grid[newy][newx]) adj[gethsh(i, j)].push_back(gethsh(newy, newx));
            }
        }
    }

    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (grid[i][j] and ht[gethsh(i, j)] == -1) dfs1(gethsh(i, j), -1, 0);

    if (dfs2(bes.first, bes.second)) dfs3(stloc);

    for (int i = 0; i < q; i++) {
        int y, x;
        bool ans = false;
        cin >> y >> x;
        for (int j = 0; j < 4; j++) if (vis2[gethsh(y, x, j)]) ans = true;
        cout << (ans or (y == box.first and x == box.second) ? "YES\n" : "NO\n");
    }

	return 0;
}
