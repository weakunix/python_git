#include <iostream>
#include <iomanip>
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

const int N = 101, K = 101;

int n, k;
double dp[N][K], ans = 0;

int main() {
    memset(dp, 0, sizeof(dp)); dp[0][0] = 1;

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int l = 0; l < j; l++) dp[i][j] += dp[i - 1][l] / k;
            dp[i][j] += dp[i - 1][j] * j / k;
        }
    }
    for (int i = 1; i <= k; i++) ans += dp[n][i] * i;
    cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}
