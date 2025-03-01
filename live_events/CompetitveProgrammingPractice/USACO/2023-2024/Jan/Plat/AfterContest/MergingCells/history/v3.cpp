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

int n, arr[N], pfx[N], llim[N][N], rlim[N][N];
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

    for (int i = 1; i <= n; i++) {
        int lim = 1;
        for (int j = 1; j <= i; j++) {
            while (pfx[j - 1] - pfx[lim - 1] > pfx[i] - pfx[j - 1]) lim++;
            llim[j][i] = lim;
        }
    }

    for (int i = n; i > 0; i--) {
        int lim = n;
        for (int j = n; j >= i; j--) {
            while (pfx[lim] - pfx[j] >= pfx[j] - pfx[i - 1]) lim--;
            rlim[i][j] = lim;
        }
    }

    dp[1][n] = 1;
    for (int i = n - 2; i >= 0; i--) {
        for (int l = 1, r = i + 1; r <= n; l++, r++) {
            for (int j = llim[l][r]; j < l; j++) dp[l][r] = (dp[l][r] + dp[j][r] * inv[r - j] % modval) % modval;
            for (int j = rlim[l][r]; j > r; j--) dp[l][r] = (dp[l][r] + dp[l][j] * inv[j - l] % modval) % modval;
        }
    }

    for (int i = 1; i <= n; i++) cout << dp[i][i] << "\n";

	return 0;
}
