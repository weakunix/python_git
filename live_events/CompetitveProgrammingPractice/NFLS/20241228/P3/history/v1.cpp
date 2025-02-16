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

const int N = 17;
int pw3[N];

int h, w, a, b;
ll dp[N][1 << N][N]; // row, blocked, cnt

int main() {
    pw3[0] = 1;
    for (int i = 1; i < N; i++) pw3[i] = 3 * pw3[i - 1];

    clr(dp, 0);

    cin >> h >> w >> a >> b;

    dp[0][0][0] = 1;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < (1 << w); j++) {
            bool blocked[N];
            for (int k = 0; k < w; k++) blocked[k] = (j & (1 << k));

            for (int k = 0; k <= a; k++) {
                if (not dp[i][j][k]) continue;

                for (int l = 0; l < pw3[w]; l++) {
                    int grid[N];
                    for (int o = 0, p = l; o < w; o++, p /= 3) grid[o] = p % 3;

                    bool works = true;
                    for (int o = 0; o < w; o++) {
                        if (grid[o] and blocked[o]) works = false;
                        if (grid[o] == 2 and (o == w - 1 or grid[o + 1] or blocked[o + 1])) works = false;
                        if (not works) break;
                    }
                    if (not works) continue;

                    int newj = 0, newk = k;
                    for (int o = 0; o < w; o++) {
                        if (grid[o]) newk++;
                        if (grid[o] == 1) newj |= (1 << o);
                    }
                    if (newk <= a) dp[i + 1][newj][newk] += dp[i][j][k];
                }
            }
        }
    }

    cout << dp[h][0][a] << "\n";

	return 0;
}
