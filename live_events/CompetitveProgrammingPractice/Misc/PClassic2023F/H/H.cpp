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

const int N = 1e4 + 1;

int dp[N][26][26], ans = 1e9;
char st, en;
simps pos[26];
string s;

int getdist(int a, int b) {
    return max(abs(pos[a].first - pos[b].first), abs(pos[a].second - pos[b].second));
}

int main() {
    for (int i = 0; i < 26; i++) pos[i] = {-1, -1};
    for (int i = 0; i < N; i++) for (int j = 0; j < 26; j++) for (int k = 0; k < 26; k++) dp[i][j][k] = 1e9;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            char cur;
            cin >> cur;
            pos[cur - 'a'] = {i, j};
        }
    }
    cin >> st >> en >> s;

    dp[0][st - 'a'][en - 'a'] = 0;

    for (int i = 0; i < s.size(); i++) {
        int cur = s[i] - 'a';
        for (int j = 0; j < 26; j++) {
            if (pos[j].first == -1) continue;
            for (int k = 0; k < 26; k++) {
                if (pos[k].first == -1) continue;
                
                dp[i + 1][cur][k] = min(dp[i][j][k] + getdist(j, cur) + 1, dp[i + 1][cur][k]);
                dp[i + 1][j][cur] = min(dp[i][j][k] + getdist(k, cur) + 1, dp[i + 1][j][cur]);
            }
        }
    }

    for (int i = 0; i < 26; i++) for (int j = 0; j < 26; j++) ans = min(dp[s.size()][i][j], ans);
    cout << ans << "\n";

	return 0;
}
