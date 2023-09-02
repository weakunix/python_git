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
ll ans = 0, dp[M][S][2], rmask[N][4];
vector<int> robots[M];

int main() {
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
        for (int j = 0; j < robots[i].size(); j++) rmask[robots[i].size()][robots[i][j]] |= 1 << j;
    }
    for (int i = 0; i < n; i++) {
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = -1;
        for (int j = 0; j <= i; j++) {
            int prev = min(j, n - i), cur = min(j + 1, n - i), curmask = (1 << cur) - 1;
            for (int k = 0; k < (1 << prev); k++) {
                for (int l = 0; l < 2; l++) {
                    if (j < i) dp[j + 1][(k << 1) & curmask][l or (k << 1) > curmask] = (dp[j + 1][(k << 1) & curmask][l or (k << 1) > curmask] + dp[j][k][l]) % modval; //don't choose
                    dp[j + 1][((k << 1) | 1) & curmask][l or (k << 1) > curmask] = (dp[j + 1][((k << 1) | 1) & curmask][l or (k << 1) > curmask] + modval - dp[j][k][l]) % modval; //choose
                }
            }
            for (int k = 0; k < (1 << cur); k++) {
                for (int l = 0; l < 2; l++) {
                
                    ll curans = 1;
                    bitset<M> use[4];
                    for (int y = 0; y < cur; y++) {
                        for (int x = 0; x < m; x++) {
                            if (i + robots[x].size() > n) continue;
                            if (k & (1 << y)) {
                                if (y < robots[x].size()) use[robots[x][y]][x] = 1;
                                else use[0][x] = 1;
                            }
                            if (l) use[0][x] = 1;
                            if (j < i) use[0][x] = 1;
                        }
                    }
                    for (int x = 0; x < m; x++) {
                        if ((use[0][x] and use[1][x]) or (use[2][x] and use[3][x])) continue;
                        else if ((use[0][x] or use[1][x]) and (use[2][x] or use[3][x])) curans = (curans * 2) % modval;
                        else if ((use[0][x] or use[1][x]) or (use[2][x] or use[3][x])) curans = (curans * 3) % modval;
                    }
                    dp[j + 1][k][l] = (dp[j + 1][k][l] * curans) % modval;

                    /*
                    ll curans = 1;
                    vector<vector<bool>> use(4, vector<bool>(m));
                    for (int y = 0; y < cur; y++) {
                        for (int x = 0; x < m; x++) {
                            if (i + robots[x].size() > n) continue;
                            if (k & (1 << y)) {
                                if (y < robots[x].size()) use[robots[x][y]][x] = true;
                                else use[0][x] = true;
                            }
                            if (l) use[0][x] = true;
                            if (j < i) use[0][x] = true;
                        }
                    }
                    for (int x = 0; x < m; x++) {
                        if ((use[0][x] and use[1][x]) or (use[2][x] and use[3][x])) continue;
                        else if ((use[0][x] or use[1][x]) and (use[2][x] or use[3][x])) curans = (curans * 2) % modval;
                        else if ((use[0][x] or use[1][x]) or (use[2][x] or use[3][x])) curans = (curans * 3) % modval;
                    }
                    dp[j + 1][k][l] = (dp[j + 1][k][l] * curans) % modval;
                    */
                }
            }
        }
        int cur = min(i + 1, n - i);
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < (1 << cur); k++) {
                for (int l = 0; l < 2; l++) {
                    ll curans = 1;
                    for (int x = 0; x < m; x++) {
                        if (i + robots[x].size() > n) continue;
                        vector<bool> use(4);
                        for (int y = 0; y < cur; y++) {
                            if (k & (1 << y)) {
                                if (j < i - y + robots[x].size()) use[robots[x][j - i + y]] = true;
                                else use[0] = true;
                            }
                        }
                        if (l) use[0] = true;
                        
                        if ((use[0] and use[1]) or (use[2] and use[3])) continue;
                        else if ((use[0] or use[1]) and (use[2] or use[3])) curans = (curans * 2) % modval;
                        else curans = (curans * 3) % modval;
                    }
                    dp[i + 1][k][l] = (dp[i + 1][k][l] * curans) % modval;
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
