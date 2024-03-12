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

const int N = 1002, modval = 1e9 + 7;

ll inv[N];

int n, arr[N], pfx[N], llim[N][N], rlim[N][N];
ll dpl[N][N], dpr[N][N];

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = (modval - modval / i) * inv[modval % i] % modval;

    pfx[0] = 0;
    clr(dpl, 0);
    clr(dpr, 0);

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

    dpl[n][1] = inv[n - 1];
    dpr[1][n] = inv[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        for (int l = 1, r = i + 1; r <= n; l++, r++) {
            ll cur = ((dpl[r][l - 1] + modval - dpl[r][llim[l][r] - 1]) % modval + (dpr[l][r + 1] + modval - dpr[l][rlim[l][r] + 1]) % modval) % modval;
            if (i == 0) cout << cur << "\n";
            else {
                dpl[r][l] = (dpl[r][l - 1] + cur * inv[r - l] % modval) % modval;
                dpr[l][r] = (dpr[l][r + 1] + cur * inv[r - l] % modval) % modval;
            }
        }
    }

	return 0;
}
