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

const int N = 32, M = 1000, H = N / 2, S = 1 << H, modval = 1e9 + 7;
ll pw2[N + 1], pw3[N + 1];

int n, m, sz[M], arr[M][N];
ll c[S][4], f[S][2][H + 1], res1[S], dp[N][S][2], ans = 0;
vector<int> ord[N + 1];

void process(int cur) {
    clr(c, -1);
    clr(c[0], 0);
    clr(c[S >> 1], 0);

    if (sz[cur] <= H) {
        f[0][0][sz[cur]] = f[0][0][sz[cur]] * 3 % modval;
        f[0][1][sz[cur]] = f[0][1][sz[cur]] * 3 % modval;
    }

    for (int i = 0; i < N; i++) c[S >> 1][arr[cur][i]] |= 1ll << (N - i - 1);
    for (int i = 1; i < min(n - sz[cur] + 1, H); i++) {
        for (int j = 0; j < 4; j++) c[S >> (i + 1)][j] = c[S >> i][j] >> 1;
        c[S >> (i + 1)][2] |= 1ll << (N - 1);
    }

    for (int i = 1; i < S; i++) {
        int lowbit = i & (-i);
        if (c[lowbit][0] == -1) continue;
        if (lowbit != i) for (int j = 0; j < 4; j++) c[i][j] = c[lowbit][j] | c[i ^ lowbit][j];

        ll case1 = (c[i][0] & c[i][1]) | (c[i][2] & c[i][3]);
        ll case2 = (c[i][0] | c[i][1]) & (c[i][2] | c[i][3]);
        ll case3 = (1ll << N) - 1;
        case2 ^= case1 & case2;
        case3 ^= case1 | case2;
        case2 >>= N - n;
        case3 >>= N - n;
        res1[i] = res1[i] * pw2[__builtin_popcount(case2)] % modval * pw3[__builtin_popcount(case3)] % modval;

        if (sz[cur] <= H) {
            int curmul;
            bool seen[4];
            for (int j = 0; j < 4; j++) seen[j] = c[i][j] & (1 << H);

            if ((seen[0] and seen[1]) or (seen[2] and seen[3])) curmul = 1;
            else if ((seen[0] or seen[1]) and (seen[2] or seen[3])) curmul = 2;
            else curmul = 3;
            f[i][0][sz[cur]] = f[i][0][sz[cur]] * curmul % modval;

            seen[2] = true;

            if ((seen[0] and seen[1]) or (seen[2] and seen[3])) curmul = 1;
            else if ((seen[0] or seen[1]) and (seen[2] or seen[3])) curmul = 2;
            else curmul = 3;
            f[i][1][sz[cur]] = f[i][1][sz[cur]] * curmul % modval;
        }
    }

    return;
}

int main() {
    pw2[0] = 1;
    pw3[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw2[i] = pw2[i - 1] * 2 % modval;
        pw3[i] = pw3[i - 1] * 3 % modval;
    }

    clr(sz, 0);
    for (int i = 0; i < M; i++) fill(arr[i], arr[i] + N, 2);
    for (int i = 0; i < S; i++) for (int j = 0; j < 2; j++) fill(f[i][j], f[i][j] + H, 1);
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
        if (sz[i] <= n) ord[sz[i]].pb(i);
    }

    for (int i = 1; i <= n; i++) {
       if (i <= H) for (int j = 0; j < S; j++) for (int k = 0; k < 2; k++) f[j][k][i] = f[j][k][i - 1];
        for (int j : ord[i]) process(j);
    }

    for (int i = 1; i < S; i++) {
        if (__builtin_popcount(i) % 2 == 0) res1[i] = (modval - res1[i]) % modval;
        ans = (ans + res1[i]) % modval;
    }

    for (int i = H; i < n; i++) {
        int mx = n - i;
        clr(dp, 0);
        dp[0][0][0] = (modval - f[0][1][mx]) % modval;
        dp[0][1][0] = f[1][1][mx];

        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < S; k++) {
                for (int l = 0; l < 2; l++) {
                    ll nxtmsk = k << 1;
                    bool nxtbefore = (l or (nxtmsk & S));
                    if (nxtmsk & S) nxtmsk ^= S;

                    if (j + 1 != i) dp[j + 1][nxtmsk][nxtbefore] = (dp[j + 1][nxtmsk][nxtbefore] + dp[j][k][l] * f[nxtmsk][nxtbefore or j + 1 < i][mx] % modval) % modval;
                    nxtmsk |= 1;
                    if (j + 1 <= i) dp[j + 1][nxtmsk][nxtbefore] = (dp[j + 1][nxtmsk][nxtbefore] + modval - dp[j][k][l] * f[nxtmsk][nxtbefore or j + 1 < i][mx] % modval) % modval;
                }
            }
        }

        for (int j = 0; j < S; j++) for (int k = 0; k < 2; k++) ans = (ans + dp[n - 1][j][k]) % modval;
    }

    cout << ans << "\n";

	return 0;
}
