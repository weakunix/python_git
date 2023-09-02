#include <iostream>
#include <string>
#include <cstring>
#include <vector>
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

const int N = 35, M = 1005, B = 1 << 16, modval = 1e9 + 7;

int n, m;
ll ans = 0, dp[N][B][2];
vector<int> robots[M];

void modadd(ll& a, ll& b) {
    a = (a + b) % modval;
    return;
}

void modsub(ll& a, ll& b) {
    a = (a + modval - b) % modval;
    return;
}

void modmul(ll& a, ll b) {
    a = a * b % modval;
    return;
}

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
    }
    for (int i = 0; i < n; i++) {
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = -1;
        for (int j = 0; j <= i; j++) {
            int prev = min(j, n - i), cur = min(j + 1, n - i), curmask = (1 << cur) - 1;
            for (int k = 0; k < (1 << prev); k++) {
                for (int l = 0; l < 2; l++) {
                    if (j < i) modadd(dp[j + 1][curmask & (k << 1)][l or (k << 1) > curmask], dp[j][k][l]);
                    modsub(dp[j + 1][((curmask & (k << 1))) ^ 1][l or (k << 1) > curmask], dp[j][k][l]);
                }
            }
            for (int k = 0; k < (1 << cur); k++) {
                for (int l = 0; l < 2; l++) {
                    
                    for (int x = 0; x < m; x++) {
                        if (robots[x].size() > n - i) continue;
                        vector<bool> use(4);
                        for (int y = 0; y < cur; y++) {
                            if (k & (1 << y)) {
                                if (robots[x].size() <= y) use[0] = true;
                                else use[robots[x][y]] = true;
                            }
                        }
                        if (l) use[0] = true;
                        if (j < i) use[0] = true;
                        if ((use[0] and use[1]) or (use[2] and use[3])) continue;
                        else if ((use[0] or use[1]) and (use[2] or use[3])) modmul(dp[j + 1][k][l], 2);
                        else modmul(dp[j + 1][k][l], 3);
                    }
                }
            }
        }
        int cur = min(i + 1, n - i);
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < (1 << cur); k++) {
                for (int l = 0; l < 2; l++) {
                    for (int x = 0; x < m; x++) {
                        if (robots[x].size() > n - i) continue;
                        vector<bool> use(4);
                        for (int y = 0; y < cur; y++) {
                            if (k & (1 << y)) {
                                if (robots[x].size() <= j - i + y) use[0] = true;
                                else use[robots[x][j - i + y]] = true;
                            }
                        }
                        if (l) use[0] = true;
                        if ((use[0] and use[1]) or (use[2] and use[3])) continue;
                        else if ((use[0] or use[1]) and (use[2] or use[3])) modmul(dp[i + 1][k][l], 2);
                        else modmul(dp[i + 1][k][l], 3);
                    }
                }
            }
        }
        for (int k = 0; k < (1 << cur); k++) {
            for (int l = 0; l < 2; l++) modadd(ans, dp[i + 1][k][l]);
        }
    }
    cout << ans << "\n";
	return 0;
}
