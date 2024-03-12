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

int n, arr[N], pfx[N];
ll dp[N][N];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

int main() {
    pfx[0] = 0;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pfx[i] = pfx[i - 1] + arr[i];
    }
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
        for (int j = 1; j < n; j++) {
            for (int k = max(i - j, 1); k <= min(i, n - j); k++) {
                dp[k][k + j] = 0;
                for (int l = k; l < i; l++) {
                    if (pfx[l] - pfx[k - 1] > pfx[k + j] - pfx[l]) break;
                    dp[k][k + j] = (dp[k][k + j] + dp[l + 1][k + j]) % modval;
                }
                for (int r = k + j; r > i; r--) {
                    if (pfx[k + j] - pfx[r - 1] >= pfx[r - 1] - pfx[k - 1]) break;
                    dp[k][k + j] = (dp[k][k + j] + dp[k][r - 1]) % modval;
                }
                dp[k][k + j] = dp[k][k + j] * pw(j, modval - 2) % modval;
            }
        }
        cout << dp[1][n] << "\n";
    }
	return 0;
}
