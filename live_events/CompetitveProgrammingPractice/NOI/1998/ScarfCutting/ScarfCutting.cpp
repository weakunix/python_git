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

const int N = 100;

int n, m, dp[2][N][2 * N], ans = 0;
bool grid[N][2 * N];

void rot() {
    bool nwgrid[N][2 * N];

    for (int i = 0; i <= 2 * n - 2; i++) {
        if (i % 2 == 0) {
            int cur = (2 * n - i) / 2 - 1;
            for (int j = i / 2; j < n; j++) nwgrid[cur][2 * j - i] = grid[j][i];
        }
        else {
            int cur = (2 * n - i) / 2;
            for (int j = i / 2 + 1; j < n; j++) nwgrid[cur][2 * j - i] = grid[j][i];
        }
    }

    memcpy(grid, nwgrid, sizeof(nwgrid));

    return;
}

void solve() {
    for (int i = 0; i <= 2 * n - 2; i++) dp[0][n - 1][i] = (not grid[n - 1][i] and i % 2 == 0);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= 2 * i; j++) {
            if (grid[i][j] or j % 2 == 1) dp[0][i][j] = 0;
            else if (grid[i + 1][j + 1]) dp[0][i][j] = 1;
            else dp[0][i][j] = min(dp[0][i + 1][j], dp[0][i + 1][j + 2]) + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 2 * i; j++) {
            if (grid[i][j] or j % 2 == 0) dp[1][i][j] = 0;
            else if (grid[i - 1][j - 1] or j > 2 * (i - 1) or j - 2 < 0) dp[1][i][j] = 1;
            else dp[1][i][j] = min(dp[1][i - 1][j - 2], dp[1][i - 1][j]) + 1;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        int ans1 = 0, ans2 = 0;
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= 2 * j; k++) {
                if (k % 2 == 0) setmx(ans1, min(dp[0][j][k], i - j + 1));
                else setmx(ans1, dp[1][j][k]);
            }
        }
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k <= 2 * j; k++) {
                if (k % 2 == 0) setmx(ans2, dp[0][j][k]);
                else setmx(ans2, min(dp[1][j][k], j - i));
            }
        }

        if (ans1 > 0 and ans2 > 0) setmx(ans, ans1 * ans1 + ans2 * ans2);
    }

    return;
}

int main() {
    clr(grid, false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        grid[x][y] = true;
    }

    solve();
    rot();
    solve();
    rot();
    solve();

    cout << ans << "\n";

	return 0;
}
