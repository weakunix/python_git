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

const int N = 32, M = 1000, H = 16, S = 1 << H, modval = 1e9 + 7;
ll pw2[N + 1], pw3[N + 1];

int n, m, sz[M], arr[M][N];
unsigned c[S][M][4];
ll ans = 0;

int main() {
    pw2[0] = 1;
    pw3[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw2[i] = pw2[i - 1] * 2 % modval;
        pw3[i] = pw3[i - 1] * 3 % modval;
    }

    clr(sz, 0);
    for (int i = 0; i < M; i++) fill(arr[i], arr[i] + N, 2);
    clr(c, -1);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        for (char j : s) {
            if (j == 'R') {
                sz[i]++;
                if (sz[i] == n) break;
            }
            else if (j == '*') arr[i][sz[i]] ^= 1;
            else arr[i][sz[i]] = j - '0';
        }
        sz[i]++;
    }

    for (int i = 0; i < m; i++) {
        if (sz[i] > n) continue;
        clr(c[0][i], 0);
        clr(c[S >> 1][i], 0);
        for (int j = 0; j < N; j++) c[S >> 1][i][arr[i][j]] |= 1ll << (N - j - 1);
        for (int j = 1; j < min(n - sz[i] + 1, H); j++) {
            for (int k = 0; k < 4; k++) c[S >> (j + 1)][i][k] = c[S >> j][i][k] >> 1;
            c[S >> (j + 1)][i][2] |= 1ll << (N - 1);
        }
    }

    for (int i = 1; i < S; i++) {
        int lowbit = i & (-i);
        if (lowbit == i) continue;
        for (int j = 0; j < m; j++) {
            if (sz[j] > n or c[lowbit][j][0] == -1) continue;
            for (int k = 0; k < 4; k++) c[i][j][k] = c[lowbit][j][k] | c[i ^ lowbit][j][k];
        }
    }

    for (int i = 1; i < S; i++) {
        ll res = 1;
        for (int j = 0; j < m; j++) {
            if (c[i][j][0] == -1) continue;
            ll case1 = (c[i][j][0] & c[i][j][1]) | (c[i][j][2] & c[i][j][3]);
            ll case2 = (c[i][j][0] | c[i][j][1]) & (c[i][j][2] | c[i][j][3]);
            ll case3 = (1ll << N) - 1;
            case2 ^= case1 & case2;
            case3 ^= case1 | case2;
            case2 >>= N - n;
            case3 >>= N - n;
            res = res * pw2[__builtin_popcount(case2)] % modval * pw3[__builtin_popcount(case3)] % modval;
        }
        if (__builtin_popcount(i) % 2 == 0) res = (modval - res) % modval;
        ans = (ans + res) % modval;
    }

    cout << ans << "\n";

	return 0;
}
