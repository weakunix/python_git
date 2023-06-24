#include <iostream>
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

const int modval = 1e9 + 7;

int n, m;
vector<vector<int>> dp, from;

bool works(int a, int b) {
    vector<bool> twos(n);
    for (int i = 0; i < n; i++) {
        if (a & (1 << i)) {
            if (b & (1 << i)) twos[i] = true;
        }
        else {
            if ((b & (1 << i)) == 0) return false;
        }
    }
    for (int i = 0; i < n; i++) {
        if (twos[i]) {
            if (i == n - 1 or not twos[i + 1]) return false;
            twos[i + 1] = false;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    dp.resize(m + 1, vector<int>(1 << n)); dp[0].back() = 1;
    from.resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (works(i, j)) from[i].push_back(j);
        }
        //assert(from[i].size() < 100);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k : from[j]) dp[i][j] = (dp[i][j] + dp[i - 1][k]) % modval;
        }
    }
    cout << dp[m].back() << "\n";
	return 0;
}
