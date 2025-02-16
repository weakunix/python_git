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

const int N = 2501;

int t, n, m;
bool dp[N][N][2];
string a, rawb;
vector<pair<char, bool>> b;

void subcase() {
    clr(dp, 0);
    dp[0][0][0] = true;
    b.clear();

    cin >> a >> rawb;
    a = "$" + a;
    rawb = "$" + rawb;
    n = a.size();

    for (char c : rawb) {
        if (c == '*') b.back().second = true;
        else b.pb({c, false});
    }
    m = b.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 2; k++) {
                if (not dp[i][j][k]) continue;

                if (k and i < n - 1 and a[i + 1] == a[i]) dp[i + 1][j][1] = true;
                
                if (j < m - 1) {
                    if (b[j + 1].second) dp[i][j + 1][0] = true;
                    if (i < n - 1 and (b[j + 1].first == '.' or b[j + 1].first == a[i + 1])) dp[i + 1][j + 1][b[j + 1].second] = true;
                }
            }
        }
    }
    
    cout << (dp[n - 1][m - 1][0] or dp[n - 1][m - 1][1] ? "yes" : "no") << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
