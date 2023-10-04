#include <iostream>
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

const int N = 1000, M = 101, modval = 1e9 + 7;

int n, m;
ll ans = 1, z[M][26], dp[N][M];
string cur, s;

int main() {
    memset(z, 0, sizeof(z));
    memset(dp, 0, sizeof(dp));

    cin >> n >> s;
    m = s.size();
    z[0][s[0] - 'A'] = 1;
    for (int i = 1; i < m; i++) {
        cur += s[i - 1];
        z[i][s[i] - 'A'] = i + 1;
        for (int j = i - 1; j > 0; j--) {
            if (cur.substr(i - j, j) == s.substr(0, j) and not z[i][s[j] - 'A']) z[i][s[j] - 'A'] = j + 1;
        }
        if (not z[i][s[0] - 'A']) z[i][s[0] - 'A'] = 1;
    }
    dp[0][0] = 25;
    dp[0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 26; k++) dp[i + 1][z[j][k]] = (dp[i + 1][z[j][k]] + dp[i][j]) % modval;
        }
    }
    for (int i = 0; i < n; i++) ans = ans * 26 % modval;
    for (int j = 0; j < m; j++) ans = (ans + modval - dp[n - 1][j]) % modval;
    cout << ans << "\n";
	return 0;
}
