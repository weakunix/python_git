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

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 2000, M = 2000; //BFI

int n, m, q, a[N], b[M];
bool dp[N][M];
simps qx[N], qy[M];

bool ispsbl() {
    memset(dp, false, sizeof(dp));
    for (int i = 0; i < m; i++) {
        if (a[0] <= b[i]) break;
        dp[0][i] = true;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] <= b[j]) continue;
            dp[i][j] = dp[i - 1][j] or (j > 0 and dp[i][j - 1]);
        }
    }
    return dp[n - 1][m - 1];
}

void solve() {
    if (ispsbl()) {
        cout << 1;
        return;
    }
    for (int i = 0; i < n; i++) a[i] *= -1;
    for (int i = 0; i < m; i++) b[i] *= -1;
    cout << (ispsbl() ? 1 : 0);
    for (int i = 0; i < n; i++) a[i] *= -1;
    for (int i = 0; i < m; i++) b[i] *= -1;
    return;
}

int main() {
    //freopen("expand.in", "r", stdin);
    //freopen("expand.out", "w", stdout);

    cin >> n >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    solve();
    for (int i = 0; i < q; i++) {
        int kx, ky;
        cin >> kx >> ky;
        for (int j = 0; j < kx; j++) {
            cin >> qx[j].first >> qx[j].second;
            qx[j].first--;
            swap(a[qx[j].first], qx[j].second);
        }
        for (int j = 0; j < ky; j++) {
            cin >> qy[j].first >> qy[j].second;
            qy[j].first--;
            swap(b[qy[j].first], qy[j].second);
        }
        solve();
        for (int j = 0; j < kx; j++) swap(a[qx[j].first], qx[j].second);
        for (int j = 0; j < ky; j++) swap(b[qy[j].first], qy[j].second);
    }
    cout << "\n";
	return 0;
}
