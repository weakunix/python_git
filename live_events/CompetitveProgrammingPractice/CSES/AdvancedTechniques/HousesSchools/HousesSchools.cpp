#include <iostream>
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

const int N = 3001, K = 3001;

int n, k;
ll arr[N], pfx[N], ffx[N], bfx[N], dp[K][N], ans = 1e18;

ll lcost(int l, int r) {
    return ffx[r] - ffx[l - 1] - l * (pfx[r] - pfx[l - 1]);
}

ll rcost(int l, int r) {
    return bfx[r] - bfx[l - 1] - (n - r + 1) * (pfx[r] - pfx[l - 1]);
}

ll cost(int l, int r) {
    int mid = l + (r - l) / 2;
    return lcost(l, mid) + rcost(mid + 1, r);
}

void dnc(int l, int r, int optl, int optr, int prvdp, int curdp) {
    if (l > r) return;

    int mid = l + (r - l) / 2, opt = -1;

    for (int i = optl; i <= min(mid, optr); i++) {
        ll cur = dp[prvdp][i] + cost(i, mid);
        if (cur < dp[curdp][mid]) {
            dp[curdp][mid] = cur;
            opt = i;
        }
    }

    dnc(l, mid - 1, optl, opt, prvdp, curdp);
    dnc(mid + 1, r, opt, optr, prvdp, curdp);

    return;
}

int main() {
    for (int i = 0; i < K; i++) for (int j = 0; j < N; j++) dp[i][j] = 1e18;

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> arr[i];

    pfx[0] = 0;
    for (int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + arr[i];
    ffx[0] = 0;
    for (int i = 1; i <= n; i++) ffx[i] = ffx[i - 1] + i * arr[i];
    bfx[0] = 0;
    for (int i = 1; i <= n; i++) bfx[i] = bfx[i - 1] + (n - i + 1) * arr[i];

    for (int i = 1; i <= n; i++) dp[0][i] = rcost(1, i);
    for (int i = 1; i < k; i++) dnc(1, n, 1, n, i - 1, i);
    for (int i = k; i <= n; i++) ans = min(dp[k - 1][i] + lcost(i, n), ans);
    cout << ans << "\n";

	return 0;
}
