#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 101, R = 101;

int n;
ld dp[N][R], ans = 0;

int main() {
    memset(dp, 0, sizeof(dp));

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int r;
        cin >> r;
        for (int j = 1; j < R; j++) ans += dp[i - 1][j] * min(j - 1, r) / r;
        for (int j = 1; j < R; j++) dp[i][j] = dp[i - 1][j] + (j <= r ? (ld) 1e7 / r : 0);
    }
    ll ians = ans;
    if (ians % 10 > 5) ians += 5;
    else if (ians % 10 == 5) {
        ans -= ians;
        ans *= 1e12;
        if ((int) ans != 0 or ians / 10 % 10 % 2 == 1) ians += 5;
    }
    ians /= 10;
    cout << fixed << setprecision(6) << (ld) ians / 1e6 << "\n";
	return 0;
}
