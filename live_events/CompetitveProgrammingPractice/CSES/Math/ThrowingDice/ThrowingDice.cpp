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

const int modval = 1e9 + 7;

ll n;
vector<vector<ll>> ans(6, vector<ll>(6)), cur(6, vector<ll>(6));

void mul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    vector<vector<ll>> c(6, vector<ll>(6));
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j] % modval) % modval;
        }
    }
    swap(a, c);
    return;
}

int main() {
    cin >> n;
    ans[0][0] = 1;
    for (int i = 0; i < 6; i++) cur[i][0] = 1;
    for (int i = 1; i < 6; i++) cur[i - 1][i] = 1;
    while (n) {
        if (n & 1) mul(ans, cur);
        n >>= 1;
        mul(cur, cur);
    }
    cout << ans[0][0] << "\n";
	return 0;
}
