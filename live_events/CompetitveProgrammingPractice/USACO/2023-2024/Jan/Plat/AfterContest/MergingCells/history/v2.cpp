#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 5001, modval = 1e9 + 7;

ll inv[N];

int n, arr[N], pfx[N];
ll dp[N][N];

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = (modval - modval / i) * inv[modval % i] % modval;

    pfx[0] = 0;
    clr(dp, 0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pfx[i] = pfx[i - 1] + arr[i];
    }

    dp[1][n] = 1;
    for (int i = n - 2; i >= 0; i--) {
        for (int l = 1, r = i + 1; r <= n; l++, r++) {
            for (int j = l - 1; j > 0; j--) {
                if (pfx[l - 1] - pfx[j - 1] > pfx[r] - pfx[l - 1]) break;
                dp[l][r] = (dp[l][r] + dp[j][r] * inv[r - j] % modval) % modval;
            }
            for (int j = r + 1; j <= n; j++) {
                if (pfx[j] - pfx[r] >= pfx[r] - pfx[l - 1]) break;
                dp[l][r] = (dp[l][r] + dp[l][j] * inv[j - l] % modval) % modval;
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << dp[i][i] << "\n";

	return 0;
}
