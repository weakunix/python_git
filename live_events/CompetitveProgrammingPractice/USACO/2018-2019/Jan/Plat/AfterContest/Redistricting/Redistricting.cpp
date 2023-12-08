#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

const int N = 3e5 + 1;

int n, k, pfx[N], dp[N];
set<simps> mn;
map<int, set<simps>> idx;

int main() {
    freopen("redistricting.in", "r", stdin);
    freopen("redistricting.out", "w", stdout);

    pfx[0] = 0;
    dp[0] = 0;
    idx[0].insert({0, 0});
    mn.insert({0, 0});

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        pfx[i] = pfx[i - 1];
        if (c == 'H') pfx[i]++;
        else pfx[i]--;
    }

    for (int i = 1; i <= n; i++) {
        while (mn.begin()->second < i - k) mn.erase(mn.begin());
        assert(mn.size());
        dp[i] = mn.begin()->first + 1;

        while (idx[pfx[i] - 1].size()) {
            if (idx[pfx[i] - 1].begin()->second < i - k) {
                idx[pfx[i] - 1].erase(idx[pfx[i] - 1].begin());
                continue;
            }
            dp[i] = min(idx[pfx[i] - 1].begin()->first, dp[i]);
            break;
        }

        mn.insert({dp[i], i});
        idx[pfx[i]].insert({dp[i], i});
    }

    cout << dp[n] << "\n";

	return 0;
}
