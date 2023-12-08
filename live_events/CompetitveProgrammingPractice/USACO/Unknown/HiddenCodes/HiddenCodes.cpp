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

const int N = 100, M = 1e6 + 1, A = 52;

int n, m, dp[M];
string s, words[N];
vector<int> locs[A];
vector<simps> rng[M];

int convchr(char c) {
    return (c >= 'a' and c <= 'z') ? c - 'a' : (c - 'A') + 26;
}

int main() {
    memset(dp, 0, sizeof(dp));

    cin >> n;
    for (int i = 0; i < n; i++) cin >> words[i];
    cin >> s;
    m = s.size();

    for (int i = 0; i < m; i++) locs[convchr(s[i])].push_back(i);

    for (int i = 0; i < n; i++) {
        string& w = words[i];

        int curlen = w.size(), pos = m;

        for (int j = curlen - 1; j >= 0; j--) {
            int idx = lower_bound(all(locs[convchr(w[j])]), pos) - locs[convchr(w[j])].begin();
            if (not idx) {
                pos = -1;
                break;
            }
            pos = locs[convchr(w[j])][idx - 1];
        }

        for (int j : locs[convchr(w[0])]) {
            if (j > pos) break;

            int idx = 0;
            for (int k = j; k < min(j + 1000, m); k++) {
                if (s[k] == w[idx]) idx++;
                if (idx == curlen) {
                    rng[k + 1].push_back({j, curlen});
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        dp[i] = dp[i - 1];
        for (simps& p : rng[i]) dp[i] = max(p.second + dp[p.first], dp[i]);
    }

    cout << dp[m] << "\n";

	return 0;
}

