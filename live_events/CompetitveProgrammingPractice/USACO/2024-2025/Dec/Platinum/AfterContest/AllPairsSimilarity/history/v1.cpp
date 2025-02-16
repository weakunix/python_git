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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5, K = 21, M = 1 << 15, modval = 1e9 + 7;

int n, k, arr[M];
ll curdp[M][K][2], nxtdp[M][K][2];

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
    clr(curdp, 0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        curdp[arr[i]][0][0]++;
    }

    for (int i = 1; i <= k; i++) {
        int cur = 1 << (i - 1);
        clr(nxtdp, 0);

        for (int msk = 0; msk < (1 << k); msk++) {
            for (int j = 0; j <= i; j++) {
                if (msk & cur) {
                    if (j > 0) nxtdp[msk][j][0] += curdp[msk][j - 1][0];
                    if (j > 0) nxtdp[msk][j][0] += curdp[msk ^ cur][j - 1][0];
                    nxtdp[msk][j][0] %= modval;

                    if (j > 0) nxtdp[msk][j][1] += curdp[msk][j - 1][1] + curdp[msk][j - 1][0];
                    if (j > 0) nxtdp[msk][j][1] += curdp[msk ^ cur][j - 1][1];
                    nxtdp[msk][j][1] %= modval;
                }
                else {
                    nxtdp[msk][j][0] += curdp[msk][j][0];
                    if (j > 0) nxtdp[msk][j][0] += curdp[msk ^ cur][j - 1][0];
                    nxtdp[msk][j][0] %= modval;
                    
                    nxtdp[msk][j][1] += curdp[msk][j][1];
                    if (j > 0) nxtdp[msk][j][1] += curdp[msk ^ cur][j - 1][1];
                    nxtdp[msk][j][1] %= modval;
                }
            }
        }

        memcpy(curdp, nxtdp, sizeof(curdp));
    }

    for (int i = 0; i < n; i++) {
        ll ans = 0;
        for (int j = 0; j <= k; j++) {
            ans = (ans + curdp[arr[i]][j][1] * pw(j, modval - 2) % modval) % modval;
        }
        cout << ans << "\n";
    }

	return 0;
}
