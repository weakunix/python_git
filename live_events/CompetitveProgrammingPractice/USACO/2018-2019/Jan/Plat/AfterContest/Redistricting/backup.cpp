#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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
vector<int> idx[2 * N];
set<simps> mn;

int main() {
    pfx[0] = 0;
    dp[0] = 0;
    idx[N].push_back(0);
    mn.insert({0, 0});

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        pfx[i] = pfx[i - 1];
        if (c == 'H') pfx[i]++;
        else pfx[i]--;
        idx[pfx[i] + N].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        while (mn.begin()->second < i - k) mn.erase(mn.begin());
        assert(mn.size());
        dp[i] = mn.begin()->first + 1;

        int cur = lower_bound(all(idx[pfx[i] + N - 1]), i) - idx[pfx[i] + N - 1].begin();
        if (cur != 0) {
            cur = idx[pfx[i] + N - 1][cur - 1];
            if (cur >= i - k) dp[i] = min(dp[cur], dp[i]);
        }

        mn.insert({dp[i], i});
    }

    cout << dp[n] << "\n";

	return 0;
}
