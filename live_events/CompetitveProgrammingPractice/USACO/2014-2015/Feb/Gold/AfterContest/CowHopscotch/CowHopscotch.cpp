#include <iostream>
#include <cstdio>
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

const int R = 750, C = 750, modval = 1e9 + 7;

int r, c, k, grid[R][C], dp[C], curdp[C];
vector<vector<int>> bit, xvals;

void setbit(int col, int uncomppos, int add) {
    for (int idx = lower_bound(all(xvals[col]), uncomppos) - xvals[col].begin() + 1; idx < bit[col].size(); idx += idx & (-idx)) bit[col][idx] = (bit[col][idx] + add) % modval;
    return;
}

int getbit(int col, int uncomppos) {
    int res = 0;
    for (int idx = upper_bound(all(xvals[col]), uncomppos) - xvals[col].begin(); idx > 0; idx -= idx & (-idx)) res = (res + bit[col][idx]) % modval;
    return res;
}

int main() {
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);

    cin >> r >> c >> k;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
            grid[i][j]--;
        }
    }
    xvals.resize(k);
    bit.resize(k);

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            vector<int>& cur = xvals[grid[j][i]];
            if (cur.empty() or cur.back() != i) cur.push_back(i);
        }
    }

    for (int i = 0; i < k; i++) bit[i].resize(xvals[i].size() + 1);

    for (int i = 0; i < c; i++) dp[i] = 1;
    setbit(grid[0][0], 0, 1);

    for (int i = 1; i < r; i++) {
        curdp[0] = 0;
        for (int j = 1; j < c; j++) curdp[j] = (dp[j - 1] + modval - getbit(grid[i][j], j - 1)) % modval;

        int sm = 0;
        for (int j = 0; j < c; j++) {
            sm = (sm + curdp[j]) % modval;
            dp[j] = (dp[j] + sm) % modval;
            setbit(grid[i][j], j, curdp[j]);
        }
    }

    cout << curdp[c - 1] << "\n";

	return 0;
}
