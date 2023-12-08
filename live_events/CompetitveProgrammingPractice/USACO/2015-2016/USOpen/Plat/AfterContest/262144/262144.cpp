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

const int N = 262144, M = 60;

int n, dp[N][M], ans = 0;

int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);

    memset(dp, -1, sizeof(dp));

    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        dp[i][cur] = i;
        ans = max(cur, ans);
        while (dp[i][cur] > 0) {
            int nw = dp[dp[i][cur] - 1][cur];
            if (nw < 0) break;
            ans = max(cur, ans);
            cur++;
            dp[i][cur] = nw;
            ans = max(cur, ans);
        }
    }
    cout << ans << "\n";
	return 0;
}
