#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

#define all(v) v.begin(), v.end()

int n;
vector<ll> ans;
vector<vector<int>> to;
vector<vector<ll>> dp;

int LargestSetBit(int n, int val) {
    for (int i = n - 1; i >= 0; i--) {
        if (1 << i & val) return i;
    }
    assert(false);
    return 0;
}

int main() {
	//freopen("test.in", "r", stdin);
    cin >> n;
    ans.resize(1 << n);
    to.resize(n);
    dp.resize(1 << n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        bool like = true;
        for (int j = 0; j < n; j++) {
            int cur;
            cin >> cur;
            cur--;
            if (not like) continue;
            to[i].push_back(cur);
            if (cur == i) like = false;
        }
        sort(all(to[i]));
    }

    ans[0] = 1;
    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
    
    for (int i = 1; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            int cyclestart = LargestSetBit(n, i);
            for (int k : to[j]) {
                if (k > cyclestart) continue;
                if (k == cyclestart) {
                    ans[i] += dp[i][j];
                    for (int l = cyclestart + 1; l < n; l++) {
                        assert(not(i & 1 << l));
                        dp[i ^ 1 << l][l] += dp[i][j];
                    }
                    continue;
                }
                dp[i ^ 1 << k][k] += dp[i][j];
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int curmask = 0;
        for (int k = 0; k < n; k++) {
            char cur;
            cin >> cur;
            curmask ^= (cur == 'H') << k;
        }
        cout << ans[curmask] * ans[(1 << n) - 1 ^ curmask] << "\n";
    }

	return 0;
}
