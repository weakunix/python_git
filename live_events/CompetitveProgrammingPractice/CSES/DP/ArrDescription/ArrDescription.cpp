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

const int modval = 1e9 + 7;

int n, m, ans = 0;
vector<int> info;
vector<vector<int>> dp;

int main() {
    cin >> n >> m;
    info.resize(n);
    dp.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        cin >> info[i];
        info[i]--;
    }
    for (int i = 0; i < m; i++) dp[0][i] = (info[0] == -1 or info[0] == i);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (info[i] != -1 and info[i] != j) continue;
            for (int k = j - 1; k <= j + 1; k++) {
                if (k < 0 or k >= m) continue;
                dp[i][j] = (dp[i][j] + dp[i - 1][k]) % modval;
            }
        }
    }
    for (int i = 0; i < m; i++) ans = (ans + dp[n - 1][i]) % modval;
    cout << ans << "\n";
	return 0;
}
