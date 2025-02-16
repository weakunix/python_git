#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5000;

int n, q, dp[N][N];
string s;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> s >> q;
    n = s.size();

    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int i = 0; i < n - 1; i++) dp[i][i + 1] = (s[i] == s[i + 1]);
    for (int i = 2; i < n; i++) for (int j = 0; i + j < n; j++) dp[j][j + i] = (dp[j + 1][j + i - 1] and s[j] == s[j + i]);

    for (int i = 0; i < n - 1; i++) dp[i][i + 1] += 2;

    for (int i = 2; i < n; i++) {
        for (int j = 0; i + j < n; j++) {
            dp[j][j + i] += dp[j][j + i - 1] + dp[j + 1][j + i] - dp[j + 1][j + i - 1];
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << dp[l - 1][r - 1] << "\n";
    }

	return 0;
}
