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

const int N = 1001, K = 7;

int n, k;
ll arr[2 * N], pfx1[2 * N], pfx2[2 * N], dp[K][N], ans = 1e18; //pfx1: sum(i * ai), pfx2: sum(ai)

ll cost(int l, int r) {
    assert(r > l);
    return pfx1[r - 1] - pfx1[l] - l * (pfx2[r - 1] - pfx2[l]);
}

int main() {
    cin >> n >> k;
    if (k >= n) { //exception so that k < n
        cout << "0\n";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i + n] = arr[i];
    }

    pfx1[0] = 0;
    pfx2[0] = 0;
    for (int i = 1; i <= 2 * n; i++) {
        pfx1[i] = pfx1[i - 1] + i * arr[i];
        pfx2[i] = pfx2[i - 1] + arr[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) for (int l = 1; l <= n; l++) dp[j][l] = 1e18;
        dp[0][i] = 0;

        for (int j = 1; j < k; j++) {
            for (int l = 1; l <= n; l++) {
                for (int o = 1; o < l; o++) dp[j][l] = min(dp[j - 1][o] + cost(o, l), dp[j][l]);
            }
        }

        for (int j = 1; j <= n; j++) ans = min(dp[k - 1][j] + cost(j, i + n), ans);
    }

    cout << ans << "\n";

	return 0;
}
