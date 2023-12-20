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

const int N = 501, K = 125001, modval = 1e9 + 7;

int n, k;
ll dp[N][K];

int main() {
    cin >> n >> k;
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        int prv = (i - 1) * (i - 2) / 2;

        for (int j = 0; j <= min(k, i * (i - 1) / 2); j++) {
            dp[i][j] = dp[i - 1][min(j, prv)];
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % modval;
            if (j >= i) dp[i][j] = (dp[i][j] + modval - dp[i - 1][min(j - i, prv)]) % modval;
        }
    }

    cout << (dp[n][k] + modval - (k == 0 ? 0 : dp[n][k - 1])) % modval << "\n";
    
	return 0;
}
