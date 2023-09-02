#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 100;

int n, a, b;
double dp[N][6 * N], ans = 0;
string sans;

int main() {
    cin >> n >> a >> b;
    for (int i = 0; i < 6; i++) dp[0][i] = (double) 1 / 6;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 6 * n; j++) {
            for (int k = max(j - 6, 0); k < j; k++) dp[i][j] += dp[i - 1][k];
            dp[i][j] /= 6;
        }
    }
    for (int i = a - 1; i < b; i++) ans += dp[n - 1][i];
    assert(ans >= 0 and ans <= 1);
    sans = to_string(ans);
    while (sans.size() > 8) sans.pop_back();
    while (sans.size() < 8) sans += '0';
    cout << sans << "\n";
	return 0;
}
