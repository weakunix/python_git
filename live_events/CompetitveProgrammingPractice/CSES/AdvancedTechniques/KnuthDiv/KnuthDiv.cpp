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

const int N = 5001;

int n;
ll pfx[N], dp[N][N], opt[N][N];

int main() {
    pfx[0] = 0;
    for (int i = 0; i < N; i++) fill(dp[i], dp[i] + N, 1e18);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pfx[i];
        pfx[i] += pfx[i - 1];
    }
    
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j + i <= n; j++) {
            for (int k = opt[j][j + i - 1]; k <= opt[j + 1][j + i]; k++) {
                if (dp[j][k] + dp[k + 1][j + i] < dp[j][j + i]) {
                    dp[j][j + i] = dp[j][k] + dp[k + 1][j + i];
                    opt[j][j + i] = k;
                }
            }
            dp[j][j + i] += pfx[j + i] - pfx[j - 1];
        }
    }
    
    cout << dp[1][n] << "\n";

	return 0;
}
