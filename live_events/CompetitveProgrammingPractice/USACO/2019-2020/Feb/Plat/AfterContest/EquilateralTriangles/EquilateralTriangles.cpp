#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 300, M = 2 * N, C = N * N;

int n, cnt = 0, x[C], y[C], rowpfx[M][M], colpfx[M][M];
ll ans = 0, special = 0;
bool cows[M][M];
vector<int> xmp[M], ymp[M];

int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    memset(rowpfx, 0, sizeof(rowpfx));
    memset(colpfx, 0, sizeof(colpfx));
    memset(cows, false, sizeof(cows));

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == '.') continue;
            
            int curx = j - i + 300, cury = j + i + 1;
            assert(curx > 0 and curx < M);
            assert(cury > 0 and cury < M);
            x[cnt] = curx;
            y[cnt] = cury;
            xmp[curx].pb(cnt);
            ymp[cury].pb(cnt);
            cows[cury][curx] = true;

            cnt++;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 1; j < M; j++) {
            rowpfx[i][j] = rowpfx[i][j - 1] + cows[i][j];
            colpfx[i][j] = colpfx[i][j - 1] + cows[j][i];
        }
    }

    for (int i = 0; i < cnt; i++) {
        for (int j : xmp[x[i]]) {
            if (y[i] <= y[j]) continue;
            int dist = y[i] - y[j];
            if (x[i] + dist < M) ans += colpfx[x[i] + dist][y[i]] - colpfx[x[i] + dist][y[j] - 1];
            if (x[i] - dist > 0) ans += colpfx[x[i] - dist][y[i]] - colpfx[x[i] - dist][y[j] - 1];
        }
        for (int j : ymp[y[i]]) {
            if (x[i] <= x[j]) continue;
            int dist = x[i] - x[j];
            if (y[i] + dist < M) ans += rowpfx[y[i] + dist][x[i]] - rowpfx[y[i] + dist][x[j] - 1];
            if (y[i] - dist > 0) ans += rowpfx[y[i] - dist][x[i]] - rowpfx[y[i] - dist][x[j] - 1];
        }
    }

    for (int i = 0; i < cnt; i++) {
        int distcnt[M];
        memset(distcnt, 0, sizeof(distcnt));

        for (int j : xmp[x[i]]) {
            if (i != j) distcnt[abs(y[i] - y[j])]++;
        }

        for (int j : ymp[y[i]]) {
            if (i != j) special += distcnt[abs(x[i] - x[j])];
        }
    }

    cout << ans - special << "\n";
	return 0;
}
