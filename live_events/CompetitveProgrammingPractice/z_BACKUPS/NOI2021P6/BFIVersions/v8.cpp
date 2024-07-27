#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <bitset>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 35, M = 1005, S = 1 << 16, modval = 1e9 + 7;

int n, m;
ll ans = 0, dp[M][S][2], pw2[M], pw3[M];
vector<int> robots[M];
bitset<M> rmask[N][N][4], prevmask[N][4], allr[N], prevallr, use[S][4];

int main() {
    pw2[0] = 1;
    pw3[0] = 1;
    for (int i = 1; i < M; i++) {
        pw2[i] = (2 * pw2[i - 1]) % modval;
        pw3[i] = (3 * pw3[i - 1]) % modval;
    }

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        robots[i].push_back(0);
        for (char c : s) {
            if (c == 'R') robots[i].push_back(0);
            else if (c == '0') robots[i].back() = 2;
            else if (c == '1') robots[i].back() = 3;
            else robots[i].back() ^= 1;
        }
        if (robots[i].size() > n) continue;
        for (int j = 0; j < robots[i].size(); j++) rmask[robots[i].size()][j][robots[i][j]][i] = 1;
        for (int j = robots[i].size(); j < n; j++) rmask[robots[i].size()][j][0][i] = 1;
        allr[robots[i].size()][i] = 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = -1;
        for (int y = 0; y < n; y++) {
            for (int z = 0; z < 4; z++) prevmask[y][z] |= rmask[n - i][y][z];
        }
        prevallr |= allr[n - i];
        for (int j = 0; j <= i; j++) {
            int prev = min(j, n - i), cur = min(j + 1, n - i), curmask = (1 << cur) - 1;
            assert(cur <= 16);
            for (int k = 0; k < (1 << prev); k++) {
                for (int l = 0; l < 2; l++) {
                    if (j < i) dp[j + 1][(k << 1) & curmask][l or (k << 1) > curmask] = (dp[j + 1][(k << 1) & curmask][l or (k << 1) > curmask] + dp[j][k][l]) % modval; //don't choose
                    dp[j + 1][((k << 1) | 1) & curmask][l or (k << 1) > curmask] = (dp[j + 1][((k << 1) | 1) & curmask][l or (k << 1) > curmask] + modval - dp[j][k][l]) % modval; //choose
                }
            }
                        
            for (int l = 0; l < 2; l++) {
                for (int k = 0; k < (1 << cur); k++) {
                    for (int z = 0; z < 4; z++) use[k][z].reset();
                    for (int y = 0; y < cur; y++) {
                        if (k & (1 << y)) {
                            for (int z = 0; z < 4; z++) use[k][z] |= prevmask[y][z];
                        }
                    }
                    if (l) use[k][0] |= prevallr;
                    if (j < i) use[k][0] |= prevallr;
                }
                for (int k = 0; k < (1 << cur); k++) {
                    bitset<M> cnt1 = (use[k][0] & use[k][1]) | (use[k][2] & use[k][3]);
                    bitset<M> cnt2 = (use[k][0] | use[k][1]) & (use[k][2] | use[k][3]); cnt2 ^= (cnt2 & cnt1);
                    bitset<M> cnt3 = (use[k][0] | use[k][1]) | (use[k][2] | use[k][3]); cnt3 ^= (cnt3 & (cnt2 | cnt1));
                    dp[j + 1][k][l] = dp[j + 1][k][l] * pw2[cnt2.count()] % modval * pw3[cnt3.count()] % modval;
                }
            }
        }
        int cur = min(i + 1, n - i);
        assert(cur <= 16);
        for (int j = i + 1; j < n; j++) {
            for (int l = 0; l < 2; l++) {
                for (int k = 0; k < (1 << cur); k++) {
                    for (int z = 0; z < 4; z++) use[k][z].reset();
                    for (int y = 0; y < cur; y++) {
                        if (k & (1 << y)) {
                            for (int z = 0; z < 4; z++) use[k][z] |= prevmask[j - i + y][z];
                        }
                    }
                    if (l) use[k][0] |= prevallr;
                }
                for (int k = 0; k < (1 << cur); k++) {
                    bitset<M> cnt1 = (use[k][0] & use[k][1]) | (use[k][2] & use[k][3]);
                    bitset<M> cnt2 = (use[k][0] | use[k][1]) & (use[k][2] | use[k][3]); cnt2 ^= (cnt2 & cnt1);
                    bitset<M> cnt3 = (use[k][0] | use[k][1]) | (use[k][2] | use[k][3]); cnt3 ^= (cnt3 & (cnt2 | cnt1));
                    dp[i + 1][k][l] = dp[i + 1][k][l] * pw2[cnt2.count()] % modval * pw3[cnt3.count()] % modval;
                }
            }
        }
        for (int k = 0; k < (1 << cur); k++) {
            for (int l = 0; l < 2; l++) ans = (ans + dp[i + 1][k][l]) % modval;
        }
    }
    cout << ans << "\n";
	return 0;
}
