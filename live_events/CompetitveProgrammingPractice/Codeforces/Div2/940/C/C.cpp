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

const int modval = 1e9 + 7;

int t;

void subcase() {
    int n, k, cnt;
    cin >> n >> k;
    cnt = n;
    vector<int> vis(n + 1);


    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        vis[a] = true;
        vis[b] = true;
    }
    for (int i = 1; i <= n; i++) cnt -= vis[i];

    vector<ll> dp(cnt + 1);
    dp[0] = 1;
    if (cnt) dp[1] = 1;
    for (int i = 2; i <= cnt; i++) dp[i] = (dp[i - 1] + 2 * dp[i - 2] * (i - 1) % modval) % modval;
    cout << dp[cnt] << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
