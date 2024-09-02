#include <iostream>
#include <cstdio>
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
#include <numeric>
#include <cassert>
#include <iomanip>
#include <cmath>

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

const int N = 15, C = 9;

int n, pfx[C][C];
double mean, dp[N][C][C][C][C];

int getsm(int l, int r, int d, int u) {
    return pfx[r][u] - pfx[l - 1][u] - pfx[r][d - 1] + pfx[l - 1][d - 1];
}

double getval(int l, int r, int d, int u) {
    return (getsm(l, r, d, u) - mean) * (getsm(l, r, d, u) - mean);
}

double getdp(int k, int l, int r, int d, int u) {
    if (dp[k][l][r][d][u] >= 0) return dp[k][l][r][d][u];

    if (k == 1) {
        dp[k][l][r][d][u] = getval(l, r, d, u);
        return dp[k][l][r][d][u];
    }

    dp[k][l][r][d][u] = 1e9;

    for (int i = l; i < r; i++) {
        setmn(dp[k][l][r][d][u], getdp(k - 1, l, i, d, u) + getval(i + 1, r, d, u));
        setmn(dp[k][l][r][d][u], getdp(k - 1, i + 1, r, d, u) + getval(l, i, d, u));
    }

    for (int i = d; i < u; i++) {
        setmn(dp[k][l][r][d][u], getdp(k - 1, l, r, d, i) + getval(l, r, i + 1, u));
        setmn(dp[k][l][r][d][u], getdp(k - 1, l, r, i + 1, u) + getval(l, r, d, i));
    }

    return dp[k][l][r][d][u];
}

int main() {
    clr(pfx, 0);
    clr(dp, -1);

    cin >> n;
    for (int i = 1; i < C; i++) {
        for (int j = 1; j < C; j++) {
            cin >> pfx[i][j];
            pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
        }
    }

    mean = (double) pfx[C - 1][C - 1] / n;

    cout << fixed << setprecision(3) << sqrt(getdp(n, 1, C - 1, 1, C - 1) / n) << "\n";

	return 0;
}
