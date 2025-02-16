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

const int L = 20, S = 400, Z = 200;

int lim[L];
ll r, k, dp[L][S][10][10][10][2], ans = 0;

int main() {
    clr(dp, 0);
    dp[0][Z][0][0][0][0] = 1;

    cin >> r >> k;
    
    for (int i = 1; i < L; i++) {
        lim[i] = r % 10;
        r /= 10;
    }

    for (int i = 0; i < L - 1; i++) {
        for (int j = 0; j < S; j++) {
            for (int a = 0; a <= 9; a++) {
                for (int b = 0; b <= 9; b++) {
                    for (int c = 0; c <= 9; c++) {
                        for (int bound = 0; bound <= 1; bound++) {
                            if (dp[i][j][a][b][c][bound] == 0) continue;
                            for (int d = 0; d <= 9; d++) {
                                int nxt = k * d + 100 * a + 10 * b + c, p, q, r, s;
                                s = nxt % 10;
                                nxt /= 10;
                                r = nxt % 10;
                                nxt /= 10;
                                q = nxt % 10;
                                nxt /= 10;
                                p = nxt;

                                bool nwbound;
                                if (d < lim[i + 1]) nwbound = false;
                                else if (d > lim[i + 1]) nwbound = true;
                                else nwbound = bound;

                                dp[i + 1][j + d - s][p][q][r][nwbound] += dp[i][j][a][b][c][bound];
                            }
                        }
                    }
                }
            }
        }
    }

    for (int j = 0; j < S; j++) {
        for (int a = 0; a <= 9; a++) {
            for (int b = 0; b <= 9; b++) {
                for (int c = 0; c <= 9; c++) {
                    if (j - a - b - c == Z) ans += dp[L - 1][j][a][b][c][0];
                }
            }
        }
    }

    cout << ans - 1 << "\n";

	return 0;
}
