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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 301, MX = 1e9;

int n, k;
ll w[N][N], f[5][N], g[5][N], h[3][N][N], ans[N * N];
simps ord[N * N];

int main() {
    for (int i = 0; i < 5; i++) {
        fill(f[i], f[i] + N, MX);
        fill(g[i], g[i] + N, MX);
    }
    for (int i = 0; i < 3; i++) for (int j = 0; j < N; j++) fill(h[i][j], h[i][j] + N, MX);
    fill(ans, ans + N * N, MX);

    cin >> n >> k;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> w[i][j];
    for (int i = 0; i < n * n; i++) {
        cin >> ord[i].first >> ord[i].second;
        ord[i].first--;
        ord[i].second--;
    }

    for (int i = n * n - 1; i >= 0; i--) {
        int u = ord[i].first, v = ord[i].second;
        
        setmn(h[1][u][v], w[u][v]);
        for (int j = 0; j < n; j++) {
            setmn(h[2][u][j], w[u][v] + h[1][v][j]);
            setmn(h[2][j][v], h[1][j][u] + w[u][v]);
        }

        for (int j = 0; j < n; j++) {
            setmn(f[1][j], h[1][0][j]);
            setmn(f[2][j], h[2][0][j]);

            if (u == 0) setmn(f[3][j], w[u][v] + h[2][v][j]);
            setmn(f[3][j], h[1][0][u] + w[u][v] + h[1][v][j]);
            if (v == j) setmn(f[3][j], h[2][0][u] + w[u][v]);

            if (u == 0) for (int l = 0; l < n; l++) setmn(f[4][j], w[u][v] + h[1][v][l] + h[2][l][j]);
            setmn(f[4][j], h[1][0][u] + w[u][v] + h[2][v][j]);
            setmn(f[4][j], h[2][0][u] + w[u][v] + h[1][v][j]);
            if (v == j) setmn(f[4][j], f[3][u] + w[u][v]);
        }

        for (int j = 0; j < n; j++) {
            setmn(g[1][j], h[1][j][n - 1]);
            setmn(g[2][j], h[2][j][n - 1]);

            if (u == j) setmn(g[3][j], w[u][v] + h[2][v][n - 1]);
            setmn(g[3][j], h[1][j][u] + w[u][v] + h[1][v][n - 1]);
            if (v == n - 1) setmn(g[3][j], h[2][j][u] + w[u][v]);

            if (u == j) setmn(g[4][j], w[u][v] + g[3][v]);
            setmn(g[4][j], h[1][j][u] + w[u][v] + h[2][v][n - 1]);
            setmn(g[4][j], h[2][j][u] + w[u][v] + h[1][v][n - 1]);
            if (v == n - 1) for (int l = 0; l < n; l++) setmn(g[4][j], h[1][j][l] + h[2][l][u] + w[u][v]);
        }

        int l = k / 2, r = k - l;
        for (int j = 0; j < n; j++) setmn(ans[i], f[l][j] + g[r][j]);
    }

    for (int i = 1; i <= n * n; i++) cout << (ans[i] >= MX ? -1 : ans[i]) << "\n";

	return 0;
}
