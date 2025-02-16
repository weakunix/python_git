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
ll c[S][4], res1[S], ans = 0;

int main() {
    pw2[0] = 1;
    pw3[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw2[i] = pw2[i - 1] * 2 % modval;
        pw3[i] = pw3[i - 1] * 3 % modval;
    }

    clr(sz, 0);
    for (int i = 0; i < M; i++) fill(arr[i], arr[i] + N, 2);
    fill(res1, res1 + S, 1);

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
        clr(c, -1);
        clr(c[0], 0);
        clr(c[S >> 1], 0);

        for (int j = 0; j < N; j++) c[S >> 1][arr[i][j]] |= 1ll << (N - j - 1);
        for (int j = 1; j < min(n - sz[i] + 1, H); j++) {
            for (int k = 0; k < 4; k++) c[S >> (j + 1)][k] = c[S >> j][k] >> 1;
            c[S >> (j + 1)][2] |= 1ll << (N - 1);
        }

        for (int j = 1; j < S; j++) {
            int lowbit = j & (-j);
            if (c[lowbit][0] == -1) continue;
            if (lowbit != j) for (int k = 0; k < 4; k++) c[j][k] = c[lowbit][k] | c[j ^ lowbit][k];

            ll case1 = (c[j][0] & c[j][1]) | (c[j][2] & c[j][3]);
            ll case2 = (c[j][0] | c[j][1]) & (c[j][2] | c[j][3]);
            ll case3 = (1ll << N) - 1;
            case2 ^= case1 & case2;
            case3 ^= case1 | case2;
            case2 >>= N - n;
            case3 >>= N - n;
            res1[j] = res1[j] * pw2[__builtin_popcount(case2)] % modval * pw3[__builtin_popcount(case3)] % modval;
        }
    }


    for (int i = 1; i < S; i++) {
        if (__builtin_popcount(i) % 2 == 0) res1[i] = (modval - res1[i]) % modval;
        ans = (ans + res1[i]) % modval;
    }

    cout << ans << "\n";

	return 0;
}
