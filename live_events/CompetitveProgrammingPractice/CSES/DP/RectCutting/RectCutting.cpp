#include <iostream>
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

int a, b;
vector<vector<int>> dp(501, vector<int>(501, 1e9));

int getdp(int x, int y) {
    if (x > y) swap(x, y);
    return dp[x][y];
}

int main() {
    cin >> a >> b;
    if (a == b) {
        cout << "0\n";
        return 0;
    }
    if (a > b) swap(a, b);
    for (int i = 1; i <= 500; i++) {
        dp[i][i] = 0;
        for (int j = i + 1; j <= 500; j++) {
            for (int k = 1; k <= j / 2; k++) dp[i][j] = min(getdp(i, k) + getdp(i, j - k) + 1, dp[i][j]);
            for (int k = 1; k <= i / 2; k++) dp[i][j] = min(getdp(j, k) + getdp(j, i - k) + 1, dp[i][j]);
            if (i == a and j == b) {
                cout << dp[a][b] << "\n";
                return 0;
            }
        }
    }
    assert(false);
	return 0;
}
