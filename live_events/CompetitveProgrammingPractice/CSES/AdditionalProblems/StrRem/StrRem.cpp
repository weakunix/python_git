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

const int N = 5e5 + 1, modval = 1e9 + 7;

int n, prv[26];
ll dp[N];
string s;

int main() {
    memset(prv, -1, sizeof(prv));
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    cin >> s;
    n = s.size();
    
    for (int i = 0; i < n; i++) {
        dp[i + 1] = (2 * dp[i] - (prv[s[i] - 'a'] == -1 ? 0 : dp[prv[s[i] - 'a']])) % modval;
        prv[s[i] - 'a'] = i;
    }

    cout << (dp[n] - 1 + modval) % modval << "\n";

	return 0;
}
